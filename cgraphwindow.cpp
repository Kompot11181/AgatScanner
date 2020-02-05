#include "cgraphwindow.h"
#include "ui_cgraphwindow.h"

cGraphWindow::cGraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cGraphWindow)
{
    ui->setupUi(this);
    this->createPlot();
}

cGraphWindow::~cGraphWindow()
{
    delete ui;
}

// изменить название окна
void cGraphWindow::changeHeader(QString str)
{
    this->setWindowTitle(str);
}

// изменить номинал параметра
void cGraphWindow::changeNominal(QString str)
{
   ui->lNominal->setText(str);
}

// изменить подсказку
void cGraphWindow::changeTooltip(QString str)
{
    _plot->setToolTip(str);
    ui->lNominal->setToolTip(str);
    ui->lValue->setToolTip(str);
}

void cGraphWindow::addValue(QString val)
{
    bool ok;
    if(val.contains("0x"))
    {
        int value = val.right(val.lastIndexOf('x')).toInt(&ok, 16);
        _graphic->addData(QTime::currentTime().msecsSinceStartOfDay()/1000.0, value);
    }
    else {
        float value = val.toFloat(&ok);
        _graphic->addData(QTime::currentTime().msecsSinceStartOfDay()/1000.0, value);
    }
    if(!_graphic->selected()) {
        bool ok;
        _plot->xAxis->setRange(_graphic->getKeyRange(ok));
        _plot->yAxis->setRange(_graphic->getValueRange(ok));
        _plot->rescaleAxes();
    }
    ui->lValue->setText(val);
    _plot->replot();
    this->repaint();
}

void cGraphWindow::createPlot()
{
    QColor cGraphPen = QColor(25, 20, 65, 200);
    QColor cGraphBrush = QColor(25, 20, 65, 70);
    QColor cGraphSelPen = QColor(50, 20, 255, 200);
    QColor cGraphSelBrush = QColor(50, 20, 255, 70);

    QPen pen, penSel;
    pen.setColor(cGraphPen);
    penSel.setColor(cGraphSelPen);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1.0);

    _plot = new QCustomPlot(this);
    QHBoxLayout * lay = new QHBoxLayout(ui->widget);
    ui->widget->setLayout(lay);
    lay->setMargin(3);
    lay->addWidget(_plot);
    lay->setAlignment(this, Qt::AlignHCenter | Qt::AlignVCenter);
    _graphic = new QCPGraph(_plot->xAxis, _plot->yAxis);
    // from https://www.qcustomplot.com/documentation/classQCPAxisTickerDateTime.html
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    _plot->xAxis->setTicker(timeTicker);
    //timeTicker->setTimeFormat("%h:%m:%s.%z");
    bool ok;
    _plot->xAxis->setRange(_graphic->getKeyRange(ok));
    _plot->yAxis->setRange(_graphic->getValueRange(ok));
    _plot->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability); //:tssMeetTickCount);
    _plot->xAxis->ticker()->setTickCount(4);
    _plot->yAxis->ticker()->setTickCount(4);
    _plot->xAxis2->setVisible(true); _plot->xAxis2->setTicks(false); _plot->xAxis2->setTickLabels(false);
    _plot->yAxis2->setVisible(true); _plot->yAxis2->setTicks(false); _plot->yAxis2->setTickLabels(false);
    _plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    _graphic->setLineStyle(QCPGraph::LineStyle::lsStepLeft);//::lsLine);
    _graphic->setPen(pen);
    _graphic->selectionDecorator()->setPen(penSel);
    _graphic->setBrush(QBrush(cGraphBrush));
    _graphic->selectionDecorator()->setBrush(QBrush(cGraphSelBrush));
    _graphic->setParent(_plot);
}
