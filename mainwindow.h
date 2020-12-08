#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QStyle>
#include <QTextCodec>
#include <QTime>
#include <QProcess>
#include <QDebug>
#include "sg_comport.h"
#include "agat.h"
#include "agatsetting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void serialReceive(QByteArray pack);
    void serialSend(QByteArray snd);
    void sending();     // здесь процедра посылки

    void on_pbSave_clicked();

    void on_pbLoad_clicked();

    void on_pbClear_clicked();

    void on_pbScan_clicked();

    void on_pbStart_clicked();

    void on_pbStop_clicked();

    void on_cbCommonLoop_released();

    void cbCommonLoop_toChange(bool loop);

    void on_spinBox_valueChanged(int arg1);

    void on_leOutputData_textEdited(const QString &arg1);

    void on_pbCalcCRC_clicked();

    void on_pbSend_clicked();

    void contextMenuRequested(QPoint);

    void copyFromOutputData();

protected slots:
//    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    SgComPort *com;
    QTimer timer;
    unsigned int scanningCount;
    bool loop_mode;                 // флаг режима циклического опроса определённых датчиков
    bool send_user_pack;            // флаг необходимости послыки введённого пользотелей запроса
    void initSerial();
};
#endif // MAINWINDOW_H
