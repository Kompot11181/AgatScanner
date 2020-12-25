#include "agatsetting.h"

cAgatSetting::cAgatSetting(QWidget *parent) : QWidget(parent), textParser("")
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
//    делает пункты меню недоступными
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
    spinBoxAddress->setMaximum(255);
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
    leData->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    leData->setLayoutDirection(Qt::LeftToRight);
    leData->setText("");
    leData->setReadOnly(true);
    horLayout->addWidget(leData);
    leData->setVisible(false);

    leParser = new QLineEdit(backwidget);
    leParser->setBaseSize(QSize(200, 20));
    leParser->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leParser->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
     //setValidator(QRegExpValidator(QRegExp("[0-9a-fA-F]{2};[14]{1,}")).validate(), 0);
    horLayout->addWidget(leParser);
    leParser->setEnabled(false);
    leParser->setVisible(true);

//    QValidator *valid = new QRegExpValidator(QRegExp("[0-9a-fA-F]{2};[.14]{1,}"), backwidget);
//    leParser->setValidator(valid);

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
    leParser->setText(textParser);
    leParser->setPlaceholderText(tr("Задание для посылки и парсера"));
    leParser->setStatusTip(tr("Байт команды запроса в формате HEX (0 - FF), разделитель ';', парсер байт: '1'-byte, '4'-float, '.'-ignore byte, '_'-ignore 4 bytes"));

    comboBoxType->setStatusTip("Тип датчика. Для 'Коралла-8' с поключённым 'Вибро-1' использовать тип 'Коралл+'" );
    spinBoxAddress->setStatusTip("Адрес датчика (0..31)");
    checkBoxInLoop->setStatusTip("Флаг включения датчика в цикл опроса");
    leData->setStatusTip("сырые данные от датчика");

    connect(comboBoxType, SIGNAL(currentIndexChanged(int)), this, SLOT(setType(int)));
    connect(spinBoxAddress, SIGNAL(valueChanged(int)),this, SLOT(setAddr(int)));
//    connect(checkBoxInLoop, SIGNAL(toggled(bool)),this, SLOT(setLoop(bool)));
    connect(checkBoxInLoop, SIGNAL(released()),this, SLOT(setLoop()));
    connect(leParser, SIGNAL(textEdited(QString)), this, SLOT(setParser(QString)));

    this->setMouseTracking(true);
}

void cAgatSetting::blink(int interval, QColor col)
{
    QPalette pal = leData->palette();
    pal.setColor(QPalette::Base, col);
    leData->setPalette(pal);
    leParser->setPalette(pal);
    QTimer::singleShot(interval, this, SLOT(restorFromBlink()));
}

void cAgatSetting::restorFromBlink()
{
    leData->setPalette(spinBoxAddress->palette());
    leParser->setPalette(spinBoxAddress->palette());
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
        case VibroType:
        case KorallType:
        case KorallPlusType:
        case BKS14Type:
        {
            textParser = SensorsParser[_type];
            leParser->setEnabled(true);
            break;
        }
        case BKS16Type:
        {
            textParser = SensorsParser[BKS16Type];
            leParser->setEnabled(true);
            break;
        }
        case CustomType:
        {
            leParser->setEnabled(true);
            break;
        }
        default:
        {
            textParser = SensorsParser[UnknownType];
            leParser->setEnabled(true);
            break;
        }
    }
// дешифровать текст парсера
    leParser->setText(textParser);
    QStringList sl = textParser.split(QChar(';'));
    _command = QString(sl.at(0)).toInt(nullptr, 16);
    QString pars = sl.at(1);
    visibleValues = 0;
    for (int i = 0; i < pars.length(); i++) {
        if (pars[i] == '1') {
            leValues[visibleValues++]->setFixedWidth(30);
        } else if (pars[i] == '4') {
            leValues[visibleValues++]->setFixedWidth(60);
        }
    }
// показать или скрыть лишние параметры
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
    case BKS16Type:
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
    case BKS14Type:
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
    if (_type == CustomType) {
        QStringList sl = textParser.split(QChar(';'));
        QString pars = sl.at(1);
        int numOfValue = 0, u = 0;
        for (int i = 0; i < pars.length(); i++) {
            if (pars[i] == '1') {           // нужно принять 1 байт данных char
                if( (u+1) <= data.length()) {
                    _values[numOfValue++] = "0x" + QString::number(data[u++] & 0xFF, 16).toUpper();
                } else break;
            } else if (pars[i] == '4') {    // нужно принять 4 байта данных float
                if( (u+4) <= data.length()) {
                    agatChannel param;
                    param.array[3] = data[u++];
                    param.array[2] = data[u++];
                    param.array[1] = data[u++];
                    param.array[0] = data[u++];
                    _values[numOfValue++] = QString::number(param.fdata, 'f', 3);
                }
            } else if (pars[i] == '.') {    // нужно проигнорировать 1 байт данных
                ++u;
            } else if (pars[i] == '_') {    // нужно проигнорировать 4 байта данных
                u += 4;
            }
        }
    }
    else if (data.length() == 5) //КРУ-1
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
    else if (data.length() == 32) //БКС14
    {
        if(_type != BKS14Type) setType(BKS14Type);
        agatChannel param;
        _values[0] = "0x" + QString::number(data[0] & 0xFF, 16).toUpper();   // общий статус
        _values[1] = "0x" + QString::number(data[1] & 0xFF, 16).toUpper();   // общая ошибка
        param.array[3] = data[2]; param.array[2] = data[3];
        param.array[1] = data[4]; param.array[0] = data[5];
        _values[2] = QString::number(param.fdata, 'f', 3);          // значение канала 1
        _values[3] = "0x" + QString::number(data[6] & 0xFF, 16).toUpper();   // статус 1
        param.array[3] = data[7]; param.array[2] = data[8];
        param.array[1] = data[9]; param.array[0] = data[10];
        _values[4] = QString::number(param.fdata, 'f', 3);          // значение канала 2
        _values[5] = "0x" + QString::number(data[11] & 0xFF, 16).toUpper();   // статус 2
        param.array[3] = data[12]; param.array[2] = data[13];
        param.array[1] = data[14]; param.array[0] = data[15];
        _values[6] = QString::number(param.fdata, 'f', 3);           // значение канала 3
        _values[7] = "0x" + QString::number(data[16] & 0xFF, 16).toUpper();   // статус 3
        param.array[3] = data[17]; param.array[2] = data[18];
        param.array[1] = data[19]; param.array[0] = data[20];
        _values[8] = QString::number(param.fdata, 'f', 3);           // значение канала 4
        _values[9] = "0x" + QString::number(data[21] & 0xFF, 16).toUpper();   // статус 4
        param.array[3] = data[22]; param.array[2] = data[23];
        param.array[1] = data[24]; param.array[0] = data[25];
        _values[10] = QString::number(param.fdata, 'f', 3);           // значение канала 5
        _values[11] = "0x" + QString::number(data[26] & 0xFF, 16).toUpper();   // статус 5
        param.array[3] = data[27]; param.array[2] = data[28];
        param.array[1] = data[29]; param.array[0] = data[30];
        _values[12] = QString::number(param.fdata, 'f', 3);           // значение канала 6
        _values[13] = "0x" + QString::number(data[31] & 0xFF, 16).toUpper();   // статус 6
    }
    else if (data.length() == data[0] * 4 + 5) //БКС
    {
        if(_type != BKS16Type) setTypeWithLen(BKS16Type, 4 + (data.length() - 5) / 4);
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

// задать строку парсера в соответствии с пришедщей строкой
void cAgatSetting::setParser(QString parser)
{
    // разложить строку парсера
    QStringList p = parser.split(QChar(';'));
    // если нет двух составляющих, считать, что
    // команда запроса (первая часть текста парсера) равна 0x01
    if (p.length() < 2) {
        p.append(p.at(0));
        p[0] = "1";
    }
    p[0] = QString::number(p.at(0).toInt(nullptr, 16), 16).right(2).toUpper();
    p[1] = QString(p.at(1)).replace(QRegExp("[^._14]"), "");  // удалить все незначащие символы
    QString pars = QString("%1;%2").arg(p.at(0)).arg(p.at(1));
    textParser = pars;
    setType(_type);
}

void cAgatSetting::updateValues()
{
    for(int i = 0; i < MAX_NUM_OF_VALUES; i++)
    {
        if (leValues[i]->text() == _values[i]) {
            leValues[i]->setPalette(spinBoxAddress->palette()); // если данные не менялись, то стандартная палитра
        } else {
            QPalette pal = leValues[i]->palette();              // если данные менялись, то
            pal.setColor(QPalette::Text, Qt::darkRed);              // цвет текста сделать красным
            leValues[i]->setPalette(pal);
        }
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
    QAction * act_copy = new QAction(QIcon(":/images/plot.png"), tr("Вывести график"), menu->parent());
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
