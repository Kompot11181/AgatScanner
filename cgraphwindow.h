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

public slots:

    void addValue(QString);

private slots:
    void on_pbCopyToClipboard_clicked();

    void on_pbDelete_clicked();

    void on_cGraphWindow_customContextMenuRequested(const QPoint &pos);

    void on_pbSelect_clicked();

    void fix_axisX(bool);
    void fix_axisY(bool);

private:
    Ui::cGraphWindow *ui;               // интерфейс пользователя
    QCPGraph *_graphic;                 // график изменения параметра
    QCustomPlot *_plot;                 // окно отображения графика
    QStringList _data;                  // массив данных изменения параметра
    bool _isRescalableAxisX;            // флаг автонастройки шкалы оси X
    bool _isRescalableAxisY;            // флаг автонастройки шкалы оси Y

    QAction * actSelect;                // действие: выделение графика
    QAction * actAxisX;                 // действие: изменение флага автонастройки шкалы X
    QAction * actAxisY;                 // действие: изменение флага автонастройки шкалы Y
    QAction * actCopy;                  // действие: копирование данных в буфер обмена
    QAction * actClear;                 // действие: очистка графика и накопленных данных
    void createPlot();
};

#endif // CGRAPHWINDOW_H
