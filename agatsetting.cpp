#include "agatsetting.h"

cAgatSetting::cAgatSetting(QWidget *parent) : QWidget(parent)
{
    verLayout = new QVBoxLayout(this);
    verLayout->setSpacing(0);
    verLayout->setObjectName(QStringLiteral("verLayout"));
    verLayout->setContentsMargins(0, 0, 0, 0);

    backwidget = new QWidget();
    backwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    backwidget->setContentsMargins(0,2,0,2);

    horLayout = new QHBoxLayout(backwidget);
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setSpacing(6);
    lNum = new QLabel(this);
    lNum->setFixedSize(QSize(15, 20));
    lNum->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    horLayout->addWidget(lNum);

    comboBoxType = new QComboBox(backwidget);
    comboBoxType->setFixedSize(80, 20);
    comboBoxType->setMaxCount(SensorsCount);
    for (int i = 0; i < tSensorType::NumOfTypes; ++i)
        comboBoxType->addItem(SensorsName[i]);
//    делает пунки меню недоступными
//    QStandardItemModel* model = (QStandardItemModel*) comboBoxType->model();
//    model->item(tSensorType::KRUType)->setEnabled(false);
//    model->item(tSensorType::VibroType)->setEnabled(false);
//    model->item(tSensorType::UnknownType)->setEnabled(false);
    comboBoxType->setCurrentIndex(tSensorType::KorallType);
    horLayout->addWidget(comboBoxType);

    lAddress = new QLabel(backwidget);
    lAddress->setMaximumSize(QSize(50, 20));
    lAddress->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    horLayout->addWidget(lAddress);

    spinBoxAddress = new QSpinBox(backwidget);
    spinBoxAddress->setFixedSize(QSize(40, 20));
    spinBoxAddress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    spinBoxAddress->setMaximum(31);
    horLayout->addWidget(spinBoxAddress);

    checkBoxInLoop = new QCheckBox(backwidget);
    checkBoxInLoop->setFixedSize(QSize(30, 20));
    checkBoxInLoop->setCheckState(Qt::Checked);
    checkBoxInLoop->setLayoutDirection(Qt::RightToLeft);
    checkBoxInLoop->setText("");
    horLayout->addWidget(checkBoxInLoop);

    leData = new QLineEdit(backwidget);
    leData->setBaseSize(QSize(200, 20));
    leData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leData->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    leData->setLayoutDirection(Qt::LeftToRight);
    leData->setText("");
    leData->setReadOnly(true);
    horLayout->addWidget(leData);

    lValues = new QLabel(backwidget);
    lValues->setMinimumSize(QSize(80, 20));
    lValues->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    horLayout->addWidget(lValues);

    for (int i = 0; i < MAX_NUM_OF_VALUES; i++) {
        leValues[i] = new QLineEdit(backwidget);
        leValues[i]->setFixedSize(QSize(25, 20));
        leValues[i]->setText("");
        leValues[i]->setReadOnly(true);
        leValues[i]->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        horLayout->addWidget(leValues[i]);
        // connect(leValues[i], SIGNAL(textChanged(QString)), new QWindow(this->windowHandle()), SLOT(show()));
        connect(leValues[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_CustomContextMenuRequested(QPoint)));
    }

    horSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    horLayout->addItem(horSpacer);

    verLayout->addWidget(backwidget);

    lNum->setText(tr("1:"));
    lAddress->setText(tr("Адрес"));
    lValues->setText(tr("Параметры: "));

    comboBoxType->setStatusTip("Тип датчика. Для 'Коралла-8' с поключённым 'Вибро-1' использовать тип 'Коралл+', '+ массметр', '+ Вибро' с одинаковыми адресами" );
    spinBoxAddress->setStatusTip("Адрес датчика (0..31)");
    checkBoxInLoop->setStatusTip("Флаг включения датчика в цикл опроса");
    leData->setStatusTip("сырые данные от датчика");

    connect(comboBoxType, SIGNAL(currentIndexChanged(int)), this, SLOT(setType(int)));
    connect(spinBoxAddress, SIGNAL(valueChanged(int)),this, SLOT(setAddr(int)));
//    connect(checkBoxInLoop, SIGNAL(toggled(bool)),this, SLOT(setLoop(bool)));
    connect(checkBoxInLoop, SIGNAL(released()),this, SLOT(setLoop()));

    this->setMouseTracking(true);
}

void cAgatSetting::blink(int interval, QColor col)
{
    QPalette pal = leData->palette();
    pal.setColor(QPalette::Base, col);
    leData->setPalette(pal);
    QTimer::singleShot(interval, this, SLOT(restorFromBlink()));
}

void cAgatSetting::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
//    QPalette pal = spinBoxStat->palette();
//    if((event->pos().y() > (this->size().height() - 20) / 2) && (event->pos().y() < (this->size().height() + 20) / 2))
//        pal.setColor(QPalette::Base, QColor(255,0,0));
//    spinBoxErr->setPalette(pal);
}

void cAgatSetting::setType(int type)
{
    _type = static_cast<tSensorType>(type);
    comboBoxType->setCurrentIndex(static_cast<int>(_type));
    int i, visibleValues = 0;
    switch (_type) {
    case KRUType:
        visibleValues = 2;
        leValues[0]->setFixedWidth(30);
        leValues[1]->setFixedWidth(60);
//        comboBoxType->setEnabled(false);
        break;
    case VibroType:
        visibleValues = 5;
        leValues[0]->setFixedWidth(30);
        leValues[1]->setFixedWidth(30);
        leValues[2]->setFixedWidth(60);
        leValues[3]->setFixedWidth(60);
        leValues[4]->setFixedWidth(60);
//        comboBoxType->setEnabled(false);
        break;
    case KorallType:
        visibleValues = 6;
        leValues[0]->setFixedWidth(60);
        leValues[1]->setFixedWidth(60);
        leValues[2]->setFixedWidth(60);
        leValues[3]->setFixedWidth(30);
        leValues[4]->setFixedWidth(30);
        leValues[5]->setFixedWidth(30);
        break;
    case KorallPlusType:
        visibleValues = 9;
        leValues[0]->setFixedWidth(60);
        leValues[1]->setFixedWidth(60);
        leValues[2]->setFixedWidth(60);
        leValues[3]->setFixedWidth(60);
        leValues[4]->setFixedWidth(60);
        leValues[5]->setFixedWidth(60);
        leValues[6]->setFixedWidth(30);
        leValues[7]->setFixedWidth(30);
        leValues[8]->setFixedWidth(30);
        break;
    case BKSType:
        visibleValues = 14;
        leValues[0]->setFixedWidth(30);
        leValues[1]->setFixedWidth(30);
        leValues[2]->setFixedWidth(30);
        leValues[3]->setFixedWidth(30);
        leValues[4]->setFixedWidth(60);
        leValues[5]->setFixedWidth(60);
        leValues[6]->setFixedWidth(60);
        leValues[7]->setFixedWidth(60);
        leValues[8]->setFixedWidth(60);
        leValues[9]->setFixedWidth(60);
        break;
    default:
        for (i = 0; i < 4; i++)
            leValues[i]->setFixedWidth(30);
        visibleValues = 4;
        break;
    }
    for(i = 0; i < visibleValues; i++) {
        // восстановить шрифт
        leValues[i]->setFont(leData->font());
        // подсказку из таблицы
        leValues[i]->setToolTip(SensorHint[_type][i]);
        // сделать видимой окошко
        leValues[i]->setVisible(true);
        // удалить окна графика, если есть
        if(graphWindows[i] != NULL) {graphWindows[i]->deleteLater(); graphWindows[i]=NULL;}
    }
    for(i = visibleValues; i < MAX_NUM_OF_VALUES; i++){
        // спрятать неиспользуемые окошки
        leValues[i]->setVisible(false);
        // удалить окна графика, если есть
        if(graphWindows[i] != NULL) {graphWindows[i]->deleteLater(); graphWindows[i]=NULL;}
    }
}

void cAgatSetting::setTypeWithLen(int type, int num)
{
    _type = static_cast<tSensorType>(type);
    comboBoxType->setCurrentIndex(static_cast<int>(_type));
    int i, visibleValues;
    if (num > MAX_NUM_OF_VALUES) visibleValues = MAX_NUM_OF_VALUES;
    else visibleValues = num;
    switch (_type) {
    case BKSType:
        leValues[0]->setFixedWidth(30);
        leValues[1]->setFixedWidth(30);
        leValues[2]->setFixedWidth(30);
        leValues[3]->setFixedWidth(30);
        for (i = 4; i < visibleValues; i++) {
            leValues[i]->setFixedWidth(60);
        }
        break;
    case UnknownType:
        for (i = 0; i < visibleValues; i++)
            leValues[i]->setFixedWidth(30);
        break;
    case KRUType:
    case VibroType:
    case KorallType:
    case KorallPlusType:
        setType(type);      // для фиксированных датчиков количество параметров фиксировано
        return;
        break;
    default:
        for (i = 0; i < MAX_NUM_OF_VALUES; i++)
            leValues[i]->setFixedWidth(30);
        visibleValues = MAX_NUM_OF_VALUES;
        break;
    }
    for(i = 0; i < visibleValues; i++) {
        // восстановить шрифт
        leValues[i]->setFont(leData->font());
        // подсказку из таблицы
        leValues[i]->setToolTip(SensorHint[_type][i]);
        // сделать видимой окошко
        leValues[i]->setVisible(true);
        // удалить окна графика, если есть
        if(graphWindows[i] != NULL) {graphWindows[i]->deleteLater(); graphWindows[i]=NULL;}
    }
    for(i = visibleValues; i < MAX_NUM_OF_VALUES; i++){
        // спрятать неиспользуемые окошки
        leValues[i]->setVisible(false);
        // удалить окна графика, если есть
        if(graphWindows[i] != NULL) {graphWindows[i]->deleteLater(); graphWindows[i]=NULL;}
    }
}

void cAgatSetting::setAddr(int adr)
{
    _addr = static_cast<quint8>(adr);
    spinBoxAddress->setValue(_addr);
    spinBoxAddress->setToolTip("0x" + QString::number(_addr, 16).toUpper());
}

void cAgatSetting::setData(QByteArray &data)
{
    leData->setText(static_cast<QString>(data.toHex()).toUpper());
    leData->setToolTip(static_cast<QString>(data.toHex()).toUpper());
    if (data.length() == 5) //КРУ-1
    {
        if(_type != KRUType) setType(KRUType);
        _values[0] = "0x" + QString::number(data[0] & 0xFF, 16).toUpper();   // Это статус
        agatChannel param;
        param.array[0] = data[4]; param.array[1] = data[3];
        param.array[2] = data[2]; param.array[3] = data[1];
        _values[1] = QString::number(param.fdata, 'f', 3);
    }
    else if (data.length() == 14) //Вибро-1
    {
        if(_type != VibroType) setType(VibroType);
        _values[0] = "0x" + QString::number(data[0] & 0xFF, 16).toUpper();   // Это байт ошибки
        _values[1] = "0x" + QString::number(data[1] & 0xFF, 16).toUpper();   // Это байт статуса
        agatChannel param;
        param.array[3] = data[2]; param.array[2] = data[3];
        param.array[1] = data[4]; param.array[0] = data[5];
        _values[2] = QString::number(param.fdata, 'f', 3);  // значение плотности
        param.array[3] = data[6]; param.array[2] = data[7];
        param.array[1] = data[8]; param.array[0] = data[9];
        _values[3] = QString::number(param.fdata, 'f', 3);  // значение температуры
        param.array[3] = data[10]; param.array[2] = data[11];
        param.array[1] = data[12]; param.array[0] = data[13];
        _values[4] = QString::number(param.fdata, 'f', 3);  // резерв
    }
    else if (data.length() == 15) //Коралл-1 или Коралл+
    {
        if((_type != KorallType) && (_type != KorallPlusType)) setType(KorallType);
        agatChannel param;
        param.array[3] = data[0]; param.array[2] = data[1];
        param.array[1] = data[2]; param.array[0] = data[3];
        _values[0] = QString::number(param.fdata, 'f', 3);  // значение объёмного расхода
        param.array[3] = data[4]; param.array[2] = data[5];
        param.array[1] = data[6]; param.array[0] = data[7];
        _values[1] = QString::number(param.fdata, 'f', 3);  // значение объёма
        param.array[3] = data[8]; param.array[2] = data[9];
        param.array[1] = data[10]; param.array[0] = data[11];
        _values[2] = QString::number(param.fdata, 'f', 3);  // резерв
        _values[3] = "0x" + QString::number(data[12] & 0xFF, 16).toUpper();   // Это байт ошибки
        _values[4] = "0x" + QString::number(data[13] & 0xFF, 16).toUpper();   // Это байт статуса
        _values[5] = "0x" + QString::number(data[14] & 0xFF, 16).toUpper();   // резерв
    }
    else if (data.length() == 27) //Коралл+
    {
        if(_type != KorallPlusType) setType(KorallPlusType);
        agatChannel param;
        param.array[3] = data[0]; param.array[2] = data[1];
        param.array[1] = data[2]; param.array[0] = data[3];
        _values[0] = QString::number(param.fdata, 'f', 3);  // значение объёмного расхода
        param.array[3] = data[4]; param.array[2] = data[5];
        param.array[1] = data[6]; param.array[0] = data[7];
        _values[1] = QString::number(param.fdata, 'f', 3);  // значение объёма
        param.array[3] = data[8]; param.array[2] = data[9];
        param.array[1] = data[10]; param.array[0] = data[11];
        _values[2] = QString::number(param.fdata, 'f', 3);  // значение массового расхода
        param.array[3] = data[12]; param.array[2] = data[13];
        param.array[1] = data[14]; param.array[0] = data[15];
        _values[3] = QString::number(param.fdata, 'f', 3);  // значение массы
        param.array[3] = data[16]; param.array[2] = data[17];
        param.array[1] = data[18]; param.array[0] = data[19];
        _values[4] = QString::number(param.fdata, 'f', 3);  // значение плотности
        param.array[3] = data[20]; param.array[2] = data[21];
        param.array[1] = data[22]; param.array[0] = data[23];
        _values[5] = QString::number(param.fdata, 'f', 3);  // значение температуры
        _values[6] = "0x" + QString::number(data[24] & 0xFF, 16).toUpper();   // Это байт ошибки
        _values[7] = "0x" + QString::number(data[25] & 0xFF, 16).toUpper();   // Это байт статуса
        _values[8] = "0x" + QString::number(data[26] & 0xFF, 16).toUpper();   // резерв
    }
    else if (data.length() == data[0] * 4 + 5) //БКС
    {
        if(_type != BKSType) setTypeWithLen(BKSType, 4 + (data.length() - 5) / 4);
        agatChannel param;
        _values[0] = "0x" + QString::number(data[1] & 0xFF, 16).toUpper();   // Это байт общей ошибки
        _values[1] = "0x" + QString::number(data[2] & 0xFF, 16).toUpper();   // Это байт ошибки 1-2 канала
        _values[2] = "0x" + QString::number(data[3] & 0xFF, 16).toUpper();   // Это байт ошибки 3-4 канала
        _values[3] = "0x" + QString::number(data[4] & 0xFF, 16).toUpper();   // Это байт ошибки 5-6 канала
        for (int i = 4; i < MAX_NUM_OF_VALUES; i++) {
            int u = (i-3) * 4;
            if(data.length() >= (u + 5) ) {
                param.array[3] = data[u+1]; param.array[2] = data[u+2];
                param.array[1] = data[u+3]; param.array[0] = data[u+4];
                _values[i] = QString::number(param.fdata, 'f', 3);          // значение i-го параметра
            }
        };
    }
    else
    {
        //if(_type != UnknownType)
        setTypeWithLen(UnknownType, data.length());
        int len = data.length();
        if (len > MAX_NUM_OF_VALUES) len = MAX_NUM_OF_VALUES;
        for (int i = 0; i < len; i++)
            _values[i] = "0x" + QString::number(data[i] & 0xFF, 16).toUpper();   // Это байт
    };
    updateValues();
}

void cAgatSetting::updateValues()
{
    for(int i = 0; i < MAX_NUM_OF_VALUES; i++)
    {
        leValues[i]->setText(_values[i]);
        leValues[i]->setStatusTip(_values[i]);
        emit leValues[i]->textEdited(_values[i]);
    }
}
// вывод контекстного меню
void cAgatSetting::on_CustomContextMenuRequested(QPoint point)
{
    // объявление и инициализация конеткстного меню
    QLineEdit * le = qobject_cast<QLineEdit*>(sender());
    QMenu * menu = le->createStandardContextMenu();
    // создание нового действия
    menu->setParent(le);
    QAction * act_copy = new QAction(style()->standardIcon(QStyle::SP_ComputerIcon), tr("Вывести график"), menu->parent());
    // описание сочетания клавиш (только лишь?)
    act_copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    // соединение действия с функцией копирования в буфер обмена
    connect (act_copy, SIGNAL(triggered()), this, SLOT(showGraph()));
    menu->insertAction(menu->actions().at(0), act_copy);
    // вывести контекстное меню
    menu->popup(le->mapToGlobal(point));
}

// вывод окна графика
void cAgatSetting::showGraph()
{
// указатель на поле ввода, вызвавшее контекстное меню
    QLineEdit * le = qobject_cast<QLineEdit*>(sender()->parent());
// указатель на детектор, с этим полем ввода
    cAgatSetting * as = this;   //= qobject_cast<cAgatSetting*>(le->parent()->parent());
// поиск номера параметра для датчика
    int num_of_value = 0;
    for (int i = 0; i < MAX_NUM_OF_VALUES; i++)
        if (as->leValues[i] == le) num_of_value = i;
// указатель на окно графика
    cGraphWindow * cgw;
// проверка на создание нового окна
    if( as->graphWindows[num_of_value] == NULL ){
        // сделать шрифт окошка жирным
        QFont fnt = le->font();
        fnt.setBold(true);
        le->setFont(fnt);
        // новое окно для вывода графика и статистики
        cgw = new cGraphWindow(le->window());
        // добавить в список окон для вывода графика
        as->graphWindows[num_of_value] = cgw;
        // формирование заголовка формы вывода графика
        cgw->changeHeader(QString("%1 %2 (Адрес: %3), Параметр %4")
                          .arg(as->lNum->text())
                          .arg(as->getName())
                          .arg(as->_addr)
                          .arg(num_of_value + 1) );
        // связываем обновление параметра в поле ввода с окном вывода графика
        connect (le, SIGNAL(textEdited(QString)), cgw, SLOT(addValue(QString)));
        // добавляем первое значение
        emit le->textEdited(le->text());
        // конкретизируем номинал параметра и его описание по хинту
        cgw->changeNominal(SensorNominal[_type][num_of_value]);
        cgw->changeTooltip(SensorHint[_type][num_of_value]);
    }
    else
    {
        // если окно уже было создано
        cgw = as->graphWindows[num_of_value];
    }
// показать окно
    cgw->show();
}
