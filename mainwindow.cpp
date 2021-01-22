#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PROGRAM_NAME "AGAT-Scanner"
#define VERSION_NAME "v.0.97"
#define PROG_DATE __DATE__
#define PROG_TIME  __TIME__

#define TIMER_LOOP 100  // таймаут времени опроса (по умолчанию 1000 мс)
#define MAX_BLOCK_COUNT 0   // максимальное кол-во строк при выводе данных. Если 0 - то, бесконечно много

QVector<cAgatSetting *> agat_list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap imageAgat(":/images/Agat_big_grey.png");
    ui->pbLoad->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->pbSave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->pbLoad->setEnabled(false); ui->pbLoad->setVisible(false);
    ui->pbSave->setEnabled(false); ui->pbSave->setVisible(false);
//    ui->pbScan->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    ui->pbScan->setIcon(QIcon(":/images/search.ico")); ui->pbScan->setFixedSize(125,25);
    ui->pbStart->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pbStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    imageAgat.setMask(imageAgat.createMaskFromColor(QColor(128,128,128),Qt::MaskInColor));
    ui->label->setPixmap(imageAgat.scaled(ui->label->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QLabel * L = new QLabel();
    L->setFixedSize(25,10);
    L->setStatusTip("mailto: chosen_i@inbox.ru");
    QPixmap imageJK(":/images/jk.png");
    setWindowTitle(windowTitle() + " " + VERSION_NAME);
    imageJK.setMask(imageJK.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor));
    L->setPixmap(imageJK.scaled(L->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    ui->statusBar->insertPermanentWidget(0, L);

    ui->teInputData->document()->setMaximumBlockCount(0); // максимальное кол-во строк в логе

// сформировать контейнер для списка расходомеров
    QWidget * tempContainer = new QWidget();    // требуется дополнительная обёртка, иначе
    tempContainer->setLayout(ui->vLayout);
    ui->scrollArea->setWidget(tempContainer);   // иначе слой в scrollArea не добавляется

// добавить полосу сплиттера на форму
    QSplitter* sp = new QSplitter(Qt::Vertical, this);
//    sp->setGeometry(this->rect());
    sp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sp->addWidget(ui->groupBoxKorals);
    sp->addWidget(ui->groupBox);
    ui->vCentralLayout->addWidget(sp);

    //ui->pbClear->setIcon(style()->standardIcon(QStyle::SP_LineEditClearButton));
    ui->pbClear->setText("");
    ui->pbClear->setParent(ui->teInputData);
    QHBoxLayout *hblInputData = new QHBoxLayout();  //ui->teInputData);
    QVBoxLayout *vblInputData = new QVBoxLayout();  //ui->teInputData);
    QSpacerItem * spacerh = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem * spacerv = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    hblInputData->setMargin(0); vblInputData->setMargin(0);
    ui->teInputData->setLayout(hblInputData->layout());
    hblInputData->addItem(spacerh); hblInputData->addItem(vblInputData);
    vblInputData->addWidget(ui->pbClear); vblInputData->addItem(spacerv);


    ui->statusBar->showMessage("Начало программы", 2000);       // вывод сообещения
    ui->cbPort->addItems(SgComPort::getComList());              // получить список доступных COM-портов

    timer.setInterval(TIMER_LOOP);
    // создать подключение (но не подключиться)
    this->initSerial();
    // начальная инициализация (режим ожидания сканирования)
    loop_mode = false; send_user_pack = false;
    ui->groupBoxKorals->setEnabled(false);
    // привязать таймер к процедуре опроса
    connect(&timer, SIGNAL(timeout()), this, SLOT(sending()));
    // если данные получены, обработать
    connect(com, &SgComPort::packRecieved, this, &MainWindow::serialReceive);
    // если посылку поменяли (нажатие Enter), пересчитать индексы
    connect(ui->leOutputData, SIGNAL(returnPressed()),this, SLOT(on_pbCalcCRC_clicked()));
    // вызов контекстного меню
    connect(ui->leOutputData, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSerial()
{
    com = new SgComPort();
}

void MainWindow::on_pbSave_clicked()
{

}

void MainWindow::on_pbLoad_clicked()
{

}

void MainWindow::on_pbScan_clicked()
{
    foreach (cAgatSetting * koralset, agat_list)
    {
        delete koralset;
    }
    agat_list.clear();
    scanningCount = 0;
    timer.start();
    ui->groupBoxKorals->setEnabled(false);
    ui->cbCommonLoop->setChecked(true);
    ui->pbScan->setEnabled(false);
}

void MainWindow::on_pbStart_clicked()
{
    loop_mode = true;                           // включить опрос
    scanningCount = 0;                          // с начала цикла
    timer.start();                              // начать опрос
    ui->pbScan->setEnabled(false);
    ui->pbSend->setEnabled(false);
}

void MainWindow::on_pbStop_clicked()
{
    loop_mode = false;                          // остановка опроса
    scanningCount = agatConst::maxAgatNum + 1; // остановка сканирования
}

void MainWindow::sending()
{
    QString logOutStr;
    ui->pbScan->setEnabled(false);
    if(!(com->isOpened()))
    {
        if(com->open(ui->cbPort->currentText(), 57600))
        {
            qDebug() << "Open port " << com->com_name;
            if(ui->groupBox->isChecked()) ui->teInputData->append("<font color=""black"">Открыт порт: " + com->com_name + ", скорость: 57600 bps</font>");
            ui->statusBar->showMessage("Открыт порт: " + com->com_name + ", скорость: 57600 bps.", 2000);
        }
        else
        {
            qDebug() << "Error to open port!";
            if(ui->groupBox->isChecked()) ui->teInputData->append("<font color=""black"">Ошибка открытия порта</font>");    //ui->teInputData->insertPlainText("\nОшибка открытия порта\n");
            ui->statusBar->showMessage("Ошибка открытия порта", 2000);
            timer.stop();
            ui->pbScan->setEnabled(true);
            ui->pbSend->setEnabled(true);
            ui->groupBoxKorals->setEnabled(false);
            return;
        }
    }

    QByteArray request;
    if(loop_mode)
    {
// проверка на опрашиваемые Кораллы
        if (agat_list.length() == 0) {
            if(ui->groupBox->isChecked())
                ui->teInputData->append("<font color=""red"">Датчики не обнаружены. Попробуйте сканировать сеть заново</font>");
            scanningCount = agatConst::maxAgatNum;
            loop_mode = false;
            return;
        }
        // определить список датчиков для опроса (с порядковыми номерами датчиков для опроса)
        QByteArray loopList;
        for(unsigned char i=0; i < agat_list.length(); i++)
            if(agat_list.at(i)->getLoop()) loopList.append(i);
        // если не выделено ни одного датчика или список датчиков пуст, выйти
        if ( (!(ui->cbCommonLoop->isChecked())) || (loopList.length() == 0) ) {
            ui->teInputData->append("<font color=""red"">Список опроса пуст. Выделите датчики для циклического опроса и попробуйте снова</font>");
            scanningCount = agatConst::maxAgatNum;
            loop_mode = false;
            return;
        }
        // обеспечить зацикленность опроса датчиков
        if(scanningCount >= loopList.length()) scanningCount = 0;
// формировать пакет запроса
        request.append(agat_list.at(loopList.at(scanningCount))->getAddr()).append(0x33).append(0x24);
// проверка на Кораллы с Вибро-1 (Корралл+). Их опрашивать по команде 6.
        request.append(agat_list.at(loopList.at(scanningCount))->getCommand());
//дополнить запрос заголовком, окончанием и двойными и символами
        AvroraSensor::combineAnswer(request);
        MainWindow::serialSend(request);
        logOutStr += QString("%1 - <font color = ""grey"">%2 </font><font color = ""green"">[Запрос датчика №%3]</font>")
                .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                .arg(static_cast<QString>(request.toHex()).toUpper())
                .arg(QString::number(scanningCount+1).toUpper());
        if(ui->groupBox->isChecked()) ui->teInputData->append(logOutStr);
        ++scanningCount;
    }
    else if(send_user_pack) {
        send_user_pack = false;
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QByteArray str = codec->fromUnicode(ui->leOutputData->placeholderText());
        if (str.length() == 0) str = codec->fromUnicode(ui->leOutputData->text());
    // для БСК/Коралла/Кру работает на скорости 57600, 8N1.
        QByteArray hex = QByteArray::fromHex(str);
        QString logOutStr =  hex.toHex().toUpper();
        ui->statusBar->showMessage("Отправка пакета: " + logOutStr, 1000);
        if(ui->groupBox->isChecked()) {
            if(logOutStr.length() >= 10) {
                logOutStr = QString("%1 - <font color = ""green"">Отправка: %2 <b>%3</b> %4</font>")
                                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz "))
                                        .arg(logOutStr.left(2))
                                        .arg(logOutStr.mid(2, logOutStr.length() - 10))
                                        .arg(logOutStr.right(8));

            } else {
                logOutStr = QString("%1 - <font color = ""green"">Отправка: %2 </font>")
                                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz "))
                                        .arg(logOutStr);
            }
            ui->teInputData->append(logOutStr);
        }
        MainWindow::serialSend(hex);
        timer.singleShot(ui->spinBox->value(), Qt::PreciseTimer, this, SLOT(sending()));
//        MainWindow::sending();
    }
    else if (++scanningCount <= agatConst::maxAgatNum) {
        request.append(scanningCount).append(0x33).append(0x24).append(0x01);
        AvroraSensor::combineAnswer(request);
        MainWindow::serialSend(request);
        logOutStr += QString("%1 - <font color = ""grey"">%2 </font><font color = ""green"">[Запрос датчика %3]</font>")
                .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                .arg(static_cast<QString>(request.toHex()).toUpper())
                .arg(QString::number(scanningCount).toUpper());
        if (ui->groupBox->isChecked()) ui->teInputData->append(logOutStr);
        ui->statusBar->showMessage(QString("Сканирование %1 / %2 ").arg(scanningCount).arg((uint)agatConst::maxAgatNum), 1000);
        } else {
            if(com->isOpened()) {
                com->close();
                if(ui->groupBox->isChecked()) ui->teInputData->append("<font color=""black"">Порт закрыт</font>");
                ui->statusBar->showMessage("Порт закрыт", 2000);
                qDebug() << "Close port";
                if(agat_list.length()) {
                    ui->groupBoxKorals->setEnabled(true);
                    ui->pbScan->setEnabled(true);
                    ui->pbSend->setEnabled(true);
                }
            }
            timer.stop();
            ui->pbScan->setEnabled(true);
            ui->pbSend->setEnabled(true);
        }
}


// это слот для сигнала от потока приходящих даннных, где пакет уже парсится
void MainWindow::serialReceive(QByteArray pck)
{
    static QByteArray pack;
    QString logOutStr;
// добавить данные в буфер пришёдших байт
    pack += pck;
//    qDebug() << "receive:" << pack.toHex();
// если нашли символ конца сообщения, тогда продолжить
    if(pack.contains(agatConst::STT))
    {
        // вывод в окно, если разрешён
        if(ui->groupBox->isChecked())
        {
            logOutStr = QString("%1 - %2 ").arg(QTime::currentTime().toString("HH:mm:ss.zzz")).arg(static_cast<QString>(pack.toHex()).toUpper());
        }
        // получить первую команду из буфера (возможны в буфере несколько команд подряд), вырезав до символа конца сообщения
        QByteArray onePack = pack.left(pack.indexOf(agatConst::STT) + 1);
        // уменьшить буфер
        pack = pack.right(pack.length() - pack.indexOf(agatConst::STT) - 1);
        // попытаться расшифровать
        AvroraSensor koralpack;
        // до тех пор пока не получится расшифровать правильно
        while(!koralpack.updateCMDPack(onePack)){
            // добавить ещё хвост пакета до символа конца (вдруг STT попался в середине пакета)
            if(pack.contains(agatConst::STT))
            {
                onePack.append(pack.left(pack.indexOf(agatConst::STT) + 1));
                pack = pack.right(pack.length() - pack.indexOf(agatConst::STT) - 1);
            }
            else
            {
             // если добавлять нечего, это ошибка (или пакет пришёл не полностью, но с байтом STT в середине)
                if(ui->groupBox->isChecked())
                {
                    logOutStr += QString("- <font color = ""red"">Error #<b>%1</b>: %2</font>").arg(koralpack.getErrorCode()).arg(QString(koralpack.getErrorMsg(koralpack.getErrorCode())));
                    if(koralpack.getErrorCode() == (int)ERR_CODE::ERR_WRONG_CRC)
                        logOutStr += QString("<font color = ""red"">. Calculated: <b>%1</b></font>").arg(QString::number(((koralpack.getCRC()&0xFF)<<8) | (koralpack.getCRC()>>8), 16).toUpper());
                    ui->teInputData->append(logOutStr);
                }
                pack = onePack + pack;
                if (pack.length() > 255) pack.clear();  // очистить буфер (включая возможные неразобранные пакеты) при превышении буфера (FIX IT!)
                return;
            }
        };
        pack.clear();  // очисить буфер (включая возможные неразоранные пакеты)
        ui->statusBar->showMessage(onePack.toHex().toUpper(), 1000);

// проверка на опрашиваемые Кораллы
        quint8 src = koralpack.getSrc();
        int koral_in_list = -1; // номер Коралла в списке заданных
        for(int i = 0; i < agat_list.length(); ++i)
            if(agat_list.at(i)->getAddr() == src) {
                koral_in_list = i;
                break;
            }
        // проверка датчика, парсер (дописать анализ типа датчика, парсер по данным)
        onePack = onePack.mid(agatConst::posDAT, onePack.length() - agatConst::posDAT + agatConst::posEndDat);
        logOutStr += QString(" - <font color = ""green"">[%1 Байт; Адрес: %2; Данные: %3]</font>")
                .arg(onePack.length())
                .arg(QString::number(static_cast<uint>(koralpack.getSrc() & 0x0FF), 16).toUpper())
                .arg(static_cast<QString>(onePack.toHex()).toUpper());
        // если датчик не в списке
        if (koral_in_list == -1)
        {
            koral_in_list = agat_list.length();
            agat_list.append(new cAgatSetting(agat_list.length()+1, tSensorType::KorallType, src));
            logOutStr += QString(" - ЗАПИСЬ: <b>%1</b>").arg(QString::number(agat_list.length()));
            ui->vLayout->addWidget(agat_list.last());
            connect(agat_list.last(), SIGNAL(loopChanged(bool)), this, SLOT(cbCommonLoop_toChange(bool)));
        }
        // индикация посылки (светло-зелёный цвет)
        agat_list.at(koral_in_list)->blink(100, QColor(230, 255, 240));
        agat_list.at(koral_in_list)->setData(onePack);
        if(ui->groupBox->isChecked()) ui->teInputData->append(logOutStr);
    };
}

void MainWindow::serialSend(QByteArray snd)
{
    com->write(snd);        // посылка готового пакета
}

void MainWindow::on_pbClear_clicked()
{
    ui->teInputData->clear();
}

void MainWindow::cbCommonLoop_toChange(bool loop)
{
    bool temp = loop;
    foreach (cAgatSetting * koralset, agat_list)
    {
        if (koralset->getLoop() != temp)
        {
            ui->cbCommonLoop->setCheckState(Qt::PartiallyChecked);
            return;
        }
    }
    if(temp){ui->cbCommonLoop->setCheckState(Qt::Checked);} else {ui->cbCommonLoop->setCheckState(Qt::Unchecked);}
}

void MainWindow::on_cbCommonLoop_released()
{
    if(ui->cbCommonLoop->checkState() == Qt::PartiallyChecked) ui->cbCommonLoop->setCheckState(Qt::Checked);
    foreach (cAgatSetting * koralset, agat_list)
    {
        if(ui->cbCommonLoop->checkState() == Qt::Checked)
            koralset->setLoop(true);
        else koralset->setLoop(false);
    }
}

void MainWindow::on_spinBox_valueChanged(int val)
{
    timer.setInterval(val);
}

void MainWindow::on_leOutputData_textEdited(const QString &arg1)
{
    ui->leOutputData->setPlaceholderText("");
    if(arg1 == "")
    {
        ui->pbCalcCRC->setEnabled(false);
    }
    else
    {
        ui->pbCalcCRC->setEnabled(true);
    }
}

void MainWindow::on_pbCalcCRC_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QByteArray pck = codec->fromUnicode(ui->leOutputData->text());
    pck = QByteArray::fromHex(pck);

    AvroraSensor::combineAnswer(pck);

    QString strholder = pck.toHex().toUpper();
    for (int i = strholder.length()-2; i > 1; i-=2)
        strholder.insert(i, ' ');
    ui->leOutputData->setPlaceholderText(strholder);
    ui->leOutputData->setText("");
    ui->pbCalcCRC->setEnabled(false);
}

void MainWindow::on_pbSend_clicked()
{
    send_user_pack = true;
    MainWindow::sending();
}

void MainWindow::contextMenuRequested(QPoint point)
{
    // объявление и инициализация конеткстного меню
    QMenu * menu = ui->leOutputData->createStandardContextMenu(); //new QMenu(ui->leOutputData->window());
    // создание нового действия
    QAction * act_copy = new QAction(QIcon(":/images/copy.png"), tr("Копировать"), menu->parent());
    // описание сочетания клавиш (только лишь?)
    act_copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    // соединение действия с функцией копирования в буфер обмена
    connect (act_copy, SIGNAL(triggered()), this, SLOT(copyFromOutputData()));
    // удалить "Cut"
    menu->removeAction(menu->actions().at(3));
    // удалить "Copy"
    menu->removeAction(menu->actions().at(3));
    // добавить действие в меню
    menu->insertAction(menu->actions().at(3), act_copy);
    // с учётом того, есть ли данные для копирования или нет
    if((ui->leOutputData->text() == "") && (ui->leOutputData->placeholderText() == ""))
    {
        act_copy->setEnabled(false);
    }
    else
    {
        act_copy->setEnabled(true);
    }
    // вывести контекстное меню
    menu->popup(ui->leOutputData->mapToGlobal(point));
}

void MainWindow::copyFromOutputData()
{
    QClipboard * clipboard = QApplication::clipboard();
    if(ui->leOutputData->text() == "")
    {
        if(ui->leOutputData->placeholderText() != "")
        {
            clipboard->setText(ui->leOutputData->placeholderText());
            ui->statusBar->showMessage("Скопировано в буфер обмена: " + clipboard->text(), 1000);
        }
    }
    else
    {
        clipboard->setText(ui->leOutputData->text());
            ui->statusBar->showMessage("Скопировано в буфер обмена: " + clipboard->text(), 1000);
    }
}
