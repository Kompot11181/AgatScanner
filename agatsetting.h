#ifndef KORALSETTING_H
#define KORALSETTING_H

#include <QWidget>
#include <QtWidgets>
#include "agat.h"  // добавлена лишь для типа koralChannel для перевода float в hex текст
#include "cgraphwindow.h"

#define MAX_NUM_OF_VALUES   12 // максимально возможное количество данных из посылки

class cAgatSetting : public QWidget
{
    Q_OBJECT
public:
    explicit cAgatSetting(QWidget *parent = 0);
    cAgatSetting(const quint32 num, tSensorType type, const quint8 adr) : cAgatSetting(0)
    {
//        cAgatSetting();
        _values.reserve(MAX_NUM_OF_VALUES);
        for(int i = 0; i < MAX_NUM_OF_VALUES; i++) {
            _values.append("");
            graphWindows[i] = NULL;
        }
        lNum->setText(QString::number(num) + ":");
        setType(type); setAddr(adr);
        // если сенсор чётный. Для равен массметра наоборот
        if  (num%2) {
            QPalette pal = backwidget->palette();
            // изменить цвет, сделать его на 5% ярче
            pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).lighter(105)));
            backwidget->setPalette(pal);
            backwidget->setAutoFillBackground(true);    // автоматически залить фон цветом
        }
        else
        {
                    QPalette pal = backwidget->palette();
                    // изменить цвет, сделать его на 5% темнее
                    pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).darker(105)));
                    backwidget->setPalette(pal);
                    backwidget->setAutoFillBackground(true);    // автоматически залить фон цветом
                }
        setType(UnknownType);
    }
    ~cAgatSetting()
    {
        for(int i = 0; i < MAX_NUM_OF_VALUES; i++) {
            if(graphWindows[i] != NULL) {graphWindows[i]->deleteLater(); graphWindows[i]=NULL;}
        }
    }

    quint8 getAddr() const {return _addr;}
    tSensorType getType() const {return _type;}
    QString getName() const {return SensorsName[_type];}
    bool getLoop() const {return _loop;}
    void blink(int interval, QColor col);

signals:
    void loopChanged(bool);     // срабатывает, когда изменяется флаг опроса

private:
    quint8 _addr = 0;       // адрес датчика в системе
    tSensorType _type = KorallType;       // тип датчика
    bool _loop = true;      // флаг участия в периодическом опросе

    QStringList _values;        // массив знчений расшифрованных параметров

    QWidget * backwidget;
    QVBoxLayout * verLayout;
    QHBoxLayout * horLayout;

    QLabel * lNum;              // "1:"
    QComboBox * comboBoxType;   // "КРУ-1"     (тип датчика)
    QLabel * lAddress;          // "Адрес "
    QSpinBox * spinBoxAddress;  // "31"        (адрес датчика)
    QCheckBox * checkBoxInLoop; // (галка для вклчения датчика в циклический опрос)
    QLineEdit * leData;         // "0043166666"(данные с датчика)
    QLabel * lValues;           // "Параметры: "
    QLineEdit * leValues[MAX_NUM_OF_VALUES];        // массив окон для вывода значений
    cGraphWindow * graphWindows[MAX_NUM_OF_VALUES]; // массив указателей на графики значений

    QSpacerItem * horSpacer;

    static const int ErrorCount = 9;
    static const int StatusCount = 8;
    static const int SensorsCount = NumOfTypes;
    const QString SensorsName[SensorsCount] = {
        tr("Коралл-8"),
        tr("Вибро-1"),
        tr("КРУ-1"),
        tr("Коралл+"),
        tr("Неизвестный"),
    };

    const QString SensorNominal[SensorsCount][MAX_NUM_OF_VALUES] = {
        {tr("м³/час"),  tr("м³"), tr(""), tr("[ERROR]"), tr("[STATUS]"), tr("")},         //Коралл
        {tr("[ERROR]"), tr("[STATUS]"), tr("кг/м³"),  tr("°C"), tr("")},                  //Вибро-1
        {tr("[STATUS]"), tr("мм")},                                                       //КРУ-1
        {tr("м³/час"),  tr("м³"), tr("т/час"), tr("т"), tr("кг/м³"),  tr("°C"), tr("[ERROR]"), tr("[STATUS]"), tr("")},         //Коралл+
        {tr("") }                                                                         //неизвестный
    };

    const QString SensorHint[SensorsCount][MAX_NUM_OF_VALUES] = {
// Коралл
        {tr("Измеренное значение объёмного расхода"),  tr("Измеренное значение объёма"), tr("резерв"),
         tr("Байт ошибки:\n0x00 - нет ошибок\n0x01 - режим «Контроль»\n"
             "0x02 - резерв\n0x03 - отсутствие измеряемой среды\n0x04 - ошибка акустических каналов\n"
             "0x05 - ошибка вторичного преобразователя\n0x06 - нет первичного преобразователя"),
         tr("Байт статуса:\n0x00 - измерение объёмного расхода без счёта объёма\n"
            "0x01 - измерение объёмного расхода и счёт объёма\n"
            "0x02 - измерение массового расхода без счёта массы\n"
            "0x03 - измерение массового расхода и счёт массы\n"
            "0x04 - калибровка аналогового выходного сигнала\n"
            "0x05 - режим имитации расхода\n0x06 - режим калибровки\n"
            "0x07 - режим работы ПЗУ при записи и чтении"), tr("резерв") },     //Коралл
//Вибро-1
        {tr("Байт ошибки:\n0x00 - нет ошибок\n0x01 - отсутствие измеряемой среды\n"
            "0x02 - чувствительный элемент загрязнен\n"
            "0x03 - неисправность канала измерений температуры\n"
            "0x04 - неисправность канала измерений плотности электронного блока\n"
            "0x05 - ошибка электронного блока\n"
            "0x06 - нет первичного преобразователя\n"
            "0x07 - плотномер в режиме «Диагностика»"),
         tr("Байт статуса:\n0x00 - режим измерения плотности и температуры\n0x01 - режим «Диагностика»"),
         tr("Измеренное значение плотности"), tr("Измеренное значение температуры"), tr("резерв"), },           //Вибро-1
//КРУ-1В
        {tr("Байт статуса:\n0x00 - рабочий режим\n0x01 - нет ПП\n0x02 - плохая связь с ПП\n"
            "0x04 - ошибка по питанию ПП\n0x08 - ошибка по питанию ВП\n"
            "0x10 - ошибка поиска импульсов или измерения\n"
            "0x20 - не соответствия з/н ПП и ВП\n0x40 - прочие ошибки"),
         tr("Измеренное значение уровня жидкости")},                                                            //КРУ-1В
//Коралл+
        {tr("Измеренное значение объёмного расхода"), tr("Измеренное значение объёма"),
         tr("Измеренное значение массового расхода"), tr("Измеренное значение массы"),
         tr("Измеренное значение плотности"), tr("Измеренное значение температуры"),
                tr("Байт ошибки:\n0x00 - нет ошибок\n0x01 - режим «Контроль»\n"
                    "0x02 - резерв\n0x03 - отсутствие измеряемой среды\n0x04 - ошибка акустических каналов\n"
                    "0x05 - ошибка вторичного преобразователя\n0x06 - нет первичного преобразователя\n"
                    "0x07 - отсутствие плотномера\n0x08 - неисправность плотномера"),
                 tr("Байт статуса:\n0x00 - измерение объёмного расхода без счёта объёма\n"
                    "0x01 - измерение объёмного расхода и счёт объёма\n"
                    "0x02 - измерение массового расхода без счёта массы\n"
                    "0x03 - измерение массового расхода и счёт массы\n"
                    "0x04 - калибровка аналогового выходного сигнала\n"
                    "0x05 - режим имитации расхода\n0x06 - режим калибровки\n"
                    "0x07 - режим работы ПЗУ при записи и чтении"), tr("резерв") },     //Коралл+
//Неизвестный
        {tr("Параметр 1"), tr("Параметр 2"), tr("Параметр 3"), tr("Параметр 4"),
         tr("Параметр 5"), tr("Параметр 6"), tr("Параметр 7"), tr("Параметр 8"),
         tr("Параметр 9"), tr("Параметр 10"), tr("Параметр 11"), tr("Параметр 12")}    //неизвестный
    };

public slots:
    void setType(int type);
    void setAddr(int adr);
    void setLoop(bool looped) {_loop = looped; checkBoxInLoop->setChecked(_loop);}
    void setLoop(void) {_loop = checkBoxInLoop->isChecked(); emit loopChanged(_loop);}
    void setData(QByteArray &data);
    void updateValues();
    void restorFromBlink() {leData->setPalette(spinBoxAddress->palette());}
private slots:
    void on_CustomContextMenuRequested(QPoint);
    void showGraph();
protected:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // KORALSETTING_H
