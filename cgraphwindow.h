#ifndef CGRAPHWINDOW_H
#define CGRAPHWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QtWidgets>
#include "qcustomplot.h"

namespace Ui {
class cGraphWindow;
}

class cGraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit cGraphWindow(QWidget *parent = 0);
    ~cGraphWindow();

    void changeHeader(QString);         // изменить заголовок окна
    void changeNominal(QString str);    // изменить значение номинала параметра
    void changeTooltip(QString str);    // изменить всплывающую подсказку

signals:
    void needToClearAll();              // сигнал на очитку всех данных с датчика

public slots:

    void addValue(QString);             // добавление нового значения
    void clear();                       // очистка данных (без окна предупреждения)

private slots:
    void on_pbCopyToClipboard_clicked();    // копирование в буфер обмена

    void on_pbDelete_clicked();             // очистка данных (с выводом окна предупреждения)

    void on_cGraphWindow_customContextMenuRequested(const QPoint &pos);     // вывод контекстного меню

    void on_pbSelect_clicked();             // выделение графика

    void fix_axisX(bool);                   // изменение флага фиксирования оси X
    void fix_axisY(bool);                   // изменение флага фиксирования оси Y

    void pasteFromClipboard();              // добавить на график

    void showToolTip(QMouseEvent * e);      // вывод данных о точке графика

private:
    Ui::cGraphWindow *ui;               // интерфейс пользователя
    QCPItemTracer * _tracer;            // указатель (графический) на точку графика
    QCPItemText * _textHint;            // вывод координат точки, привязанной к указателю _tracer
    QCPGraph *_graphic;                 // график изменения параметра
    QCustomPlot *_plot;                 // окно отображения графика
    QStringList _data;                  // массив данных изменения параметра
    bool _isRescalableAxisX;            // флаг автонастройки шкалы оси X
    bool _isRescalableAxisY;            // флаг автонастройки шкалы оси Y

    QAction * actSelect;                // действие: выделение графика
    QAction * actAxisX;                 // действие: изменение флага автонастройки шкалы X
    QAction * actAxisY;                 // действие: изменение флага автонастройки шкалы Y
    QAction * actCopy;                  // действие: копирование данных в буфер обмена
    QAction * actPaste;                 // действие: вставить из буфера обмена
    QAction * actClear;                 // действие: очистка графика и накопленных данных
    QAction * actClearAll;              // действие: очистка графиков для каждого параметра из датчика
    void createPlot();                  // инициализация графика
    void updateTextHint();              // обновление надипси с координатами

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // CGRAPHWINDOW_H
