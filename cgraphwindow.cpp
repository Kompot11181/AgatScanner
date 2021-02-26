#include "cgraphwindow.h"
#include "ui_cgraphwindow.h"

// конструктор формы
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
    // только лишь описание сочетания клавиш
    actSelect->setShortcut(QKeySequence(QKeySequence::StandardKey::SelectAll));

    // изменение автоподстройки оси X
    actAxisX = new QAction(tr("Автонастройка оси &X"), this);
    actAxisX->setCheckable(true);
    actAxisX->setChecked(_isRescalableAxisX);
    actAxisX->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));

    // изменение автоподстройки оси X
    actAxisY = new QAction(tr("Автонастройка оси &Y"), this);
    actAxisY->setCheckable(true);
    actAxisY->setChecked(_isRescalableAxisY);
    actAxisY->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));

    // копирование
    actCopy = new QAction(QIcon(":/images/copy.png"), tr("Копировать"), this);
    actCopy->setShortcut(QKeySequence(QKeySequence::StandardKey::Copy));

    // вставка
    actPaste = new QAction(QIcon(":/images/paste.png"), tr("Вставить"), this);
    actPaste->setShortcut(QKeySequence(QKeySequence::StandardKey::Paste));

    // очистка
    actClear = new QAction(QIcon(":/images/new.png"), tr("Очисить"), this);
    actClear->setShortcut(QKeySequence(QKeySequence::StandardKey::Delete));

    // очистка всех данных датчика
    actClearAll = new QAction(QIcon(":/images/new_all.png"), tr("Очисить всё"), this);
    actClearAll->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Delete));

    // соединение действия с функцией копирования в буфер обмена
    connect (actSelect, SIGNAL(triggered()), this, SLOT(on_pbSelect_clicked()));
    connect (actAxisX, SIGNAL(toggled(bool)), this, SLOT(fix_axisX(bool)));
    connect (actAxisY, SIGNAL(toggled(bool)), this, SLOT(fix_axisY(bool)));
    connect (actCopy, SIGNAL(triggered()), this, SLOT(on_pbCopyToClipboard_clicked()));
    connect (actPaste, SIGNAL(triggered()), this, SLOT(pasteFromClipboard()));
    connect (actClear, SIGNAL(triggered()), this, SLOT(on_pbDelete_clicked()));
    connect (actClearAll, SIGNAL(triggered()), this, SIGNAL(needToClearAll()));

    this->createPlot();
}

cGraphWindow::~cGraphWindow()
{
    delete ui;
}

// обработчик события нажатия на кнопку
void cGraphWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->matches(QKeySequence::StandardKey::Delete)) actClear->trigger();
    else if (e->matches(QKeySequence::StandardKey::Copy)) actCopy->trigger();
    else if (e->matches(QKeySequence::StandardKey::Paste)) actPaste->trigger();
    else if (e->matches(QKeySequence::StandardKey::SelectAll)) actSelect->trigger();
    else {
        if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key::Key_Delete)) actClearAll->trigger();
        else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key::Key_X)) actAxisX->toggle();
        else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key::Key_Y)) actAxisY->toggle();
    }
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

// обновление надписи над перекрестием
void cGraphWindow::updateTextHint()
{
    _tracer->updatePosition();

    double y = _tracer->position->value();
    double x = _tracer->position->key();

    _textHint->setText(QString("%1 \n %2").arg(y).arg(QDateTime::fromTime_t(x).toString("hh:mm:ss dd.MM.yy")));
}

// добавить новую точку на график
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
    } else {
        updateTextHint();
    }
    _plot->replot();
    this->repaint();
}

// инициализация графика
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
// инициализация указателя (перекрестия)
    _tracer = new QCPItemTracer(_plot);
    _tracer->setGraph(_graphic);
    _tracer->setInterpolating(false);
    _tracer->setStyle(QCPItemTracer::tsCrosshair);
    _tracer->setPen(QPen(Qt::red));
    _tracer->setBrush(Qt::red);
    _tracer->setSize(10);
    _tracer->setSelectable(true);
    _tracer->setVisible(false);
// инициализация надписи указателя
    _textHint = new QCPItemText(_plot);
    _textHint->setPositionAlignment(Qt::AlignBottom | Qt::AlignLeft);
    _textHint->position->setParentAnchor(_tracer->position);
    _textHint->setVisible(true);
    connect(_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(showToolTip(QMouseEvent*)));
}

// запись данных буфер обмена в формате строки с разделителями '\n'
void cGraphWindow::on_pbCopyToClipboard_clicked()
{
    QClipboard * c = QApplication::clipboard();
    c->setText(_data.join('\n').replace('.', QLocale::system().decimalPoint()));
    int len = _data.length();
    QString suffix = tr("ек");
    if (len % 10 == 1) suffix = tr("ка");
    else if ((len % 10 == 2) || (len % 10 == 3) || (len % 10 == 4)) suffix = tr("ки");
    int btn = QMessageBox::information(this, tr("Копирование"), QString(tr("Всего скопировано в буфер обмена:\n %1 точ%2")).arg(len).arg(suffix),
                QString(tr("Копировать вместе с временем")), QString(tr("OK")), QString(), 1, 1);
    if (btn == 0) {
        QStringList buf;
        for(int i = 0; i < _graphic->dataCount(); i++)
        {
            buf.append(QString("%1\t%2").arg(QDateTime::fromMSecsSinceEpoch(_graphic->dataMainKey(i) * 1000).toString("dd.MM.yyyy hh:mm:ss" + QString(QLocale::system().decimalPoint()) + "zzz"))
                                          .arg(QString(_data.at(i)).replace('.', QLocale::system().decimalPoint())) );
        }
        c->setText(buf.join('\n'));
    }
}

// выделить основной график
void cGraphWindow::on_pbSelect_clicked()
{
    _graphic->setSelection(QCPDataSelection(QCPDataRange(0, _graphic->dataCount())));
}

// изменить флаг фиксации оси абсцисс
void cGraphWindow::fix_axisX(bool t)
{
    _isRescalableAxisX = t;
}

// изменить флаг фиксации оси ординат
void cGraphWindow::fix_axisY(bool t)
{
    _isRescalableAxisY = t;
}

// добавить дополнительный график из буфера обмена
void cGraphWindow::pasteFromClipboard()
{
    bool ok;
    QColor cGraphPen = QColor(25, 20, 65, 200);
    QString data = "";
    if (QClipboard * c = QApplication::clipboard()) {
        data = c->text().replace(QLocale::system().decimalPoint(), '.');
        QStringList sl = data.split('\n');
        QCPGraph * newGraph = new QCPGraph(_plot->xAxis, _plot->yAxis);
        newGraph->setLineStyle(QCPGraph::LineStyle::lsStepLeft);
        newGraph->setPen(QPen(cGraphPen));
        newGraph->setParent(_plot);
        int i = 0;
        foreach (QString s, sl) {
            if (s.contains('\t')) {
            // если данные содержат привязку к времени
                newGraph->addData(QDateTime::fromString(s.split('\t').at(0), "dd.MM.yyyy hh:mm:ss.zzz").toMSecsSinceEpoch()/1000.0,
                                  QString(s.split('\t').at(1)).toDouble());
            } else {
            // если данные не содержат привязки к времени
                if (_graphic->dataCount() <= i) break;
                newGraph->addData(_graphic->dataMainKey(i++), s.toDouble(&ok));
            }
        }
    }
}

// показать всплывающую подскаку у курсора мышки
void cGraphWindow::showToolTip(QMouseEvent *e)
{
    double x = this->_plot->xAxis->pixelToCoord(e->pos().x());
    double y = this->_plot->yAxis->pixelToCoord(e->pos().y());
    if (_plot->selectedGraphs().contains(_graphic))
    {
        _tracer->setVisible(true); _textHint->setVisible(true);
        _tracer->setGraphKey(x);
        updateTextHint();
    }
    else
    {
        _tracer->setVisible(false); _textHint->setVisible(false);
    }
    this->changeTooltip(QString("%1 / %2").arg(y).arg(QDateTime::fromTime_t(x).toString("hh:mm:ss dd.MM.yy")));
    this->setToolTipDuration(0);
}

// очистка данных с выводом предупреждения
void cGraphWindow::on_pbDelete_clicked()
{
    // выделены неосновные графики, тогда их просто почистить
    if ((_plot->selectedGraphs().size()) && !(_plot->selectedGraphs().contains(_graphic))) {
        foreach(QCPGraph* g, _plot->selectedGraphs()) {
            g->data()->clear();
            g->setParent(0);
            g->setSelectable(QCP::SelectionType::stNone);
        }
    } else {
    // если выделен основной график, то спросить, реально нужно ли удалять
        if(QMessageBox::warning(this, tr("Очистка данных"), QString(tr("Вы уверены, что хотите очистить график\nи удалить всю накопленную информацию?")), QMessageBox::Yes | QMessageBox::No, QMessageBox::No)
                            != QMessageBox::Yes) return;
        clear();
    }
    _tracer->setVisible(false);
    _textHint->setVisible(false);
}

// очистка данных, подготовка к заполнению новыми данными
void cGraphWindow::clear()
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

    _tracer->setGraph(0);
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
    _tracer->setGraph(_graphic);
    _tracer->setVisible(false);
    _textHint->setVisible(false);
}

// вывод контекстного меню
void cGraphWindow::on_cGraphWindow_customContextMenuRequested(const QPoint &pos)
{
    // объявление и инициализация конеткстного меню
    QMenu * menu = new QMenu(this->window());
    menu->addActions({actSelect, actCopy, actPaste, actClear, actClearAll});
    menu->addSeparator();
    menu->addActions({actAxisY, actAxisX});
    // вывести контекстное меню
    menu->popup(this->mapToGlobal(pos));
}
