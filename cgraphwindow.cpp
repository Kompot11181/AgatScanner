#include "cgraphwindow.h"
#include "ui_cgraphwindow.h"

cGraphWindow::cGraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cGraphWindow)
{
    ui->setupUi(this);
    //ui->pbCopyToClipboard->setVisible(false);
    ui->pbDelete->setVisible(false);
    ui->pbSelect->setVisible(false);
    _isRescalableAxisX = true;
    _isRescalableAxisY = true;
    // ИНИЦИАЛИЗАЦИЯ ДЕЙСТВИЙ
    // выделение
    actSelect = new QAction(QIcon(":/images/plot.png"), tr("Выделить"), this);
    // описание сочетания клавиш (только лишь?)
    //act_select->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    // изменение автоподстройки оси X
    actAxisX = new QAction(tr("Автонастройка оси &X"), this);
    actAxisX->setCheckable(true);
    actAxisX->setChecked(_isRescalableAxisX);
    // описание сочетания клавиш (только лишь?)
    //act_axis->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    // изменение автоподстройки оси X
    actAxisY = new QAction(tr("Автонастройка оси &Y"), this);
    actAxisY->setCheckable(true);
    actAxisY->setChecked(_isRescalableAxisY);
    // описание сочетания клавиш (только лишь?)
    //act_axis->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    // копирование
    actCopy = new QAction(QIcon(":/images/copy.png"), tr("Копировать"), this);
    // описание сочетания клавиш (только лишь?)
    //act_copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    // соединение действия с функцией копирования в буфер обмена
    // очистка
    actClear = new QAction(tr("Очисить"), this);
    // описание сочетания клавиш (только лишь?)
    //act_clear->setShortcut(QKeySequence(Qt::Key_Delete));
    // соединение действия с функцией копирования в буфер обмена
    connect (actSelect, SIGNAL(triggered()), this, SLOT(on_pbSelect_clicked()));
    connect (actAxisX, SIGNAL(toggled(bool)), this, SLOT(fix_axisX(bool)));
    connect (actAxisY, SIGNAL(toggled(bool)), this, SLOT(fix_axisY(bool)));
    connect (actCopy, SIGNAL(triggered()), this, SLOT(on_pbCopyToClipboard_clicked()));
    connect (actClear, SIGNAL(triggered()), this, SLOT(on_pbDelete_clicked()));

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
    _data.append(val);
    if(val.contains("0x"))
    {
        int value = val.mid(val.lastIndexOf('x') + 1).toInt(&ok, 16);
        _graphic->addData(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0, value);
        ui->lValue->setText(val + " (" +QString::number(value) + ")");
    }
    else {
        float value = val.toFloat(&ok);
        _graphic->addData(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0, value);
        ui->lValue->setText(val);
    }
    if(!_graphic->selected()) {
        bool ok;
        if(_isRescalableAxisX) {    // маcштабирование оси X
            _plot->xAxis->setRange(_graphic->getKeyRange(ok));
            _plot->xAxis->rescale();
        }
        if(_isRescalableAxisY) {    // маcштабирование оси Y
            _plot->yAxis->setRange(_graphic->getValueRange(ok));
            _plot->yAxis->rescale();
        }
        //_plot->rescaleAxes();
    }
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
    _plot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_plot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_cGraphWindow_customContextMenuRequested(QPoint)));
    QHBoxLayout * lay = new QHBoxLayout(ui->widget);
    ui->widget->setLayout(lay);
    lay->setMargin(3);
    lay->addWidget(_plot);
    lay->setAlignment(this, Qt::AlignHCenter | Qt::AlignVCenter);
    _graphic = new QCPGraph(_plot->xAxis, _plot->yAxis);
    // from https://www.qcustomplot.com/documentation/classQCPAxisTickerDateTime.html
    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
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

// запись данных буфер обмена в формате строки с разделителями '\n'
void cGraphWindow::on_pbCopyToClipboard_clicked()
{
    if (QClipboard * c = QApplication::clipboard()) {
        c->setText(_data.join('\n').replace('.', QLocale::system().decimalPoint()));
    }
    int len = _data.length();
    QString suffix = tr("ек");
    if (len % 10 == 1) suffix = tr("ка");
    else if ((len % 10 == 2) || (len % 10 == 3) || (len % 10 == 4)) suffix = tr("ки");
    QMessageBox::information(this, tr("Копирование"), QString(tr("Всего скопировано в буфер обмена:\n %1 точ%2")).arg(len).arg(suffix), QDialogButtonBox::Ok);
}

void cGraphWindow::on_pbSelect_clicked()
{
    _graphic->setSelection(QCPDataSelection(QCPDataRange(0, _graphic->dataCount())));
}

void cGraphWindow::fix_axisX(bool t)
{
    _isRescalableAxisX = t;
}

void cGraphWindow::fix_axisY(bool t)
{
    _isRescalableAxisY = t;
}

void cGraphWindow::on_pbDelete_clicked()
{
    if(QMessageBox::warning(this, tr("Очистка данных"), QString(tr("Вы уверены, что хотите очистить график\nи удалить всю накопленную информацию?")), QMessageBox::Yes | QMessageBox::No, QMessageBox::No)
                            != QMessageBox::Yes) return;

    QColor cGraphPen = QColor(25, 20, 65, 200);
    QColor cGraphBrush = QColor(25, 20, 65, 70);
    QColor cGraphSelPen = QColor(50, 20, 255, 200);
    QColor cGraphSelBrush = QColor(50, 20, 255, 70);

    QPen pen, penSel;
    pen.setColor(cGraphPen);
    penSel.setColor(cGraphSelPen);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1.0);

    _data.clear();
    _graphic->data().clear();
    _plot->clearPlottables();
    _plot->replot();

    _graphic = new QCPGraph(_plot->xAxis, _plot->yAxis);
    _graphic->setLineStyle(QCPGraph::LineStyle::lsStepLeft);//::lsLine);
    _graphic->setPen(pen);
    _graphic->selectionDecorator()->setPen(penSel);
    _graphic->setBrush(QBrush(cGraphBrush));
    _graphic->selectionDecorator()->setBrush(QBrush(cGraphSelBrush));
    _graphic->setParent(_plot);
}

void cGraphWindow::on_cGraphWindow_customContextMenuRequested(const QPoint &pos)
{
    // объявление и инициализация конеткстного меню
    QMenu * menu = new QMenu(this->window());
    menu->addActions({actSelect, actCopy, actClear});
    menu->addSeparator();
    menu->addActions({actAxisY, actAxisX});
    // вывести контекстное меню
    menu->popup(this->mapToGlobal(pos));
}
