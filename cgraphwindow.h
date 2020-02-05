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

private:
    Ui::cGraphWindow *ui;
    QCPGraph *_graphic;
    QCustomPlot *_plot;

    void createPlot();
};

#endif // CGRAPHWINDOW_H
