/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hCOMLayout;
    QPushButton *pbLoad;
    QPushButton *pbSave;
    QLabel *lComport;
    QComboBox *cbPort;
    QSpacerItem *hSpacerBitrate;
    QPushButton *pbScan;
    QSpacerItem *hSpacerAgat;
    QLabel *label;
    QVBoxLayout *vCentralLayout;
    QGroupBox *groupBoxKorals;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *vKoralLayout;
    QFrame *hLineUp;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *vLayout;
    QFrame *hLineDown;
    QHBoxLayout *hLoopLayout;
    QCheckBox *cbCommonLoop;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lStep;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *lLoopMode;
    QPushButton *pbStart;
    QPushButton *pbStop;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *teInputData;
    QPushButton *pbClear;
    QFrame *line;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(920, 550);
        MainWindow->setMinimumSize(QSize(920, 330));
        QIcon icon;
        icon.addFile(QStringLiteral(":/List.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, 0, 4, 0);
        hCOMLayout = new QHBoxLayout();
        hCOMLayout->setSpacing(6);
        hCOMLayout->setObjectName(QStringLiteral("hCOMLayout"));
        hCOMLayout->setContentsMargins(10, -1, -1, -1);
        pbLoad = new QPushButton(centralWidget);
        pbLoad->setObjectName(QStringLiteral("pbLoad"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbLoad->sizePolicy().hasHeightForWidth());
        pbLoad->setSizePolicy(sizePolicy);
        pbLoad->setMinimumSize(QSize(30, 30));
        pbLoad->setMaximumSize(QSize(30, 30));
        pbLoad->setIconSize(QSize(24, 20));
        pbLoad->setFlat(true);

        hCOMLayout->addWidget(pbLoad);

        pbSave = new QPushButton(centralWidget);
        pbSave->setObjectName(QStringLiteral("pbSave"));
        pbSave->setMinimumSize(QSize(30, 30));
        pbSave->setMaximumSize(QSize(30, 30));
        pbSave->setIconSize(QSize(24, 20));
        pbSave->setFlat(true);

        hCOMLayout->addWidget(pbSave);

        lComport = new QLabel(centralWidget);
        lComport->setObjectName(QStringLiteral("lComport"));
        lComport->setMinimumSize(QSize(100, 0));
        lComport->setLayoutDirection(Qt::LeftToRight);
        lComport->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hCOMLayout->addWidget(lComport);

        cbPort = new QComboBox(centralWidget);
        cbPort->setObjectName(QStringLiteral("cbPort"));
        cbPort->setMinimumSize(QSize(80, 0));
        cbPort->setFocusPolicy(Qt::TabFocus);

        hCOMLayout->addWidget(cbPort);

        hSpacerBitrate = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hCOMLayout->addItem(hSpacerBitrate);

        pbScan = new QPushButton(centralWidget);
        pbScan->setObjectName(QStringLiteral("pbScan"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbScan->sizePolicy().hasHeightForWidth());
        pbScan->setSizePolicy(sizePolicy1);
        pbScan->setMinimumSize(QSize(100, 25));
        pbScan->setMaximumSize(QSize(100, 25));
        pbScan->setFocusPolicy(Qt::TabFocus);

        hCOMLayout->addWidget(pbScan);

        hSpacerAgat = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        hCOMLayout->addItem(hSpacerAgat);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(50, 50));
        label->setMaximumSize(QSize(50, 50));

        hCOMLayout->addWidget(label);


        verticalLayout->addLayout(hCOMLayout);

        vCentralLayout = new QVBoxLayout();
        vCentralLayout->setSpacing(6);
        vCentralLayout->setObjectName(QStringLiteral("vCentralLayout"));
        groupBoxKorals = new QGroupBox(centralWidget);
        groupBoxKorals->setObjectName(QStringLiteral("groupBoxKorals"));
        groupBoxKorals->setAutoFillBackground(false);
        horizontalLayout_4 = new QHBoxLayout(groupBoxKorals);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        vKoralLayout = new QVBoxLayout();
        vKoralLayout->setSpacing(0);
        vKoralLayout->setObjectName(QStringLiteral("vKoralLayout"));
        vKoralLayout->setContentsMargins(4, 4, 4, 4);
        hLineUp = new QFrame(groupBoxKorals);
        hLineUp->setObjectName(QStringLiteral("hLineUp"));
        hLineUp->setFrameShadow(QFrame::Raised);
        hLineUp->setFrameShape(QFrame::HLine);

        vKoralLayout->addWidget(hLineUp);

        scrollArea = new QScrollArea(groupBoxKorals);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setLineWidth(0);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 120));
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(410, 50, 61, 40));
        vLayout = new QVBoxLayout(verticalLayoutWidget_3);
        vLayout->setSpacing(0);
        vLayout->setContentsMargins(11, 11, 11, 11);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        vLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        vKoralLayout->addWidget(scrollArea);

        hLineDown = new QFrame(groupBoxKorals);
        hLineDown->setObjectName(QStringLiteral("hLineDown"));
        hLineDown->setFrameShape(QFrame::HLine);
        hLineDown->setFrameShadow(QFrame::Sunken);

        vKoralLayout->addWidget(hLineDown);

        hLoopLayout = new QHBoxLayout();
        hLoopLayout->setSpacing(6);
        hLoopLayout->setObjectName(QStringLiteral("hLoopLayout"));
        hLoopLayout->setContentsMargins(10, -1, -1, -1);
        cbCommonLoop = new QCheckBox(groupBoxKorals);
        cbCommonLoop->setObjectName(QStringLiteral("cbCommonLoop"));
        cbCommonLoop->setMinimumSize(QSize(210, 0));
        cbCommonLoop->setLayoutDirection(Qt::RightToLeft);
        cbCommonLoop->setChecked(true);
        cbCommonLoop->setTristate(false);

        hLoopLayout->addWidget(cbCommonLoop);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLoopLayout->addItem(horizontalSpacer_2);

        lStep = new QLabel(groupBoxKorals);
        lStep->setObjectName(QStringLiteral("lStep"));

        hLoopLayout->addWidget(lStep);

        spinBox = new QSpinBox(groupBoxKorals);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimumSize(QSize(50, 0));
        spinBox->setMinimum(100);
        spinBox->setMaximum(5000);
        spinBox->setSingleStep(100);

        hLoopLayout->addWidget(spinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLoopLayout->addItem(horizontalSpacer);

        lLoopMode = new QLabel(groupBoxKorals);
        lLoopMode->setObjectName(QStringLiteral("lLoopMode"));
        lLoopMode->setMinimumSize(QSize(50, 0));
        lLoopMode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hLoopLayout->addWidget(lLoopMode);

        pbStart = new QPushButton(groupBoxKorals);
        pbStart->setObjectName(QStringLiteral("pbStart"));
        pbStart->setEnabled(true);
        sizePolicy1.setHeightForWidth(pbStart->sizePolicy().hasHeightForWidth());
        pbStart->setSizePolicy(sizePolicy1);
        pbStart->setMinimumSize(QSize(32, 32));
        pbStart->setMaximumSize(QSize(32, 32));
        pbStart->setBaseSize(QSize(0, 0));
        pbStart->setFocusPolicy(Qt::WheelFocus);
        pbStart->setIconSize(QSize(16, 16));
        pbStart->setAutoDefault(false);
        pbStart->setFlat(true);

        hLoopLayout->addWidget(pbStart);

        pbStop = new QPushButton(groupBoxKorals);
        pbStop->setObjectName(QStringLiteral("pbStop"));
        pbStop->setEnabled(true);
        sizePolicy1.setHeightForWidth(pbStop->sizePolicy().hasHeightForWidth());
        pbStop->setSizePolicy(sizePolicy1);
        pbStop->setMinimumSize(QSize(32, 32));
        pbStop->setMaximumSize(QSize(32, 32));
        pbStop->setIconSize(QSize(16, 16));
        pbStop->setAutoDefault(false);
        pbStop->setFlat(true);

        hLoopLayout->addWidget(pbStop);


        vKoralLayout->addLayout(hLoopLayout);


        horizontalLayout_4->addLayout(vKoralLayout);


        vCentralLayout->addWidget(groupBoxKorals);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(true);
        groupBox->setChecked(false);
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        teInputData = new QTextEdit(groupBox);
        teInputData->setObjectName(QStringLiteral("teInputData"));
        teInputData->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(10);
        teInputData->setFont(font);
        teInputData->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        teInputData->setMouseTracking(false);
        teInputData->setFocusPolicy(Qt::WheelFocus);
        teInputData->setLayoutDirection(Qt::LeftToRight);
        teInputData->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        teInputData->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout_7->addWidget(teInputData);

        pbClear = new QPushButton(groupBox);
        pbClear->setObjectName(QStringLiteral("pbClear"));
        pbClear->setEnabled(true);
        sizePolicy1.setHeightForWidth(pbClear->sizePolicy().hasHeightForWidth());
        pbClear->setSizePolicy(sizePolicy1);
        pbClear->setMinimumSize(QSize(60, 20));
        pbClear->setMaximumSize(QSize(60, 20));
        pbClear->setBaseSize(QSize(60, 20));
        pbClear->setLayoutDirection(Qt::RightToLeft);
        pbClear->setAutoFillBackground(false);
        pbClear->setFlat(true);

        verticalLayout_7->addWidget(pbClear);


        vCentralLayout->addWidget(groupBox);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vCentralLayout->addWidget(line);


        verticalLayout->addLayout(vCentralLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 920, 21));
        menuBar->setNativeMenuBar(false);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setMaximumSize(QSize(16777215, 20));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        lComport->setBuddy(cbPort);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cbPort, pbScan);

        retranslateUi(MainWindow);

        pbClear->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\220\320\223\320\220\320\242-\321\201\320\272\320\260\320\275\320\275\320\265\321\200", 0));
#ifndef QT_NO_STATUSTIP
        pbLoad->setStatusTip(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\272\320\271\320\270", 0));
#endif // QT_NO_STATUSTIP
        pbLoad->setText(QString());
#ifndef QT_NO_STATUSTIP
        pbSave->setStatusTip(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
#endif // QT_NO_STATUSTIP
        pbSave->setText(QString());
        lComport->setText(QApplication::translate("MainWindow", "COM-\320\277\320\276\321\200\321\202", 0));
#ifndef QT_NO_STATUSTIP
        cbPort->setStatusTip(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 COM-\320\277\320\276\321\200\321\202\320\260 (ttyS \320\264\320\273\321\217 Linux)", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        pbScan->setStatusTip(QApplication::translate("MainWindow", "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\320\265\321\202\321\214 COM-\320\277\320\276\321\200\321\202\320\260", 0));
#endif // QT_NO_STATUSTIP
        pbScan->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("MainWindow", "\320\220\320\223\320\220\320\242-\320\232\320\230\320\237", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QApplication::translate("MainWindow", "\320\220\320\236 \320\234\320\276\321\200\320\270\320\275\321\204\320\276\321\200\320\274\321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\220\320\263\320\260\321\202-\320\232\320\230\320\237 \320\263.\320\240\321\217\320\267\320\260\320\275\321\214, \320\232\320\260\321\200\320\277\321\203\320\275\321\214\320\272\320\270\320\275 \320\257., 2020 \320\263.", 0));
#endif // QT_NO_STATUSTIP
        label->setText(QApplication::translate("MainWindow", "\320\220\320\263\320\260\321\202-\320\232\320\230\320\237", 0));
#ifndef QT_NO_STATUSTIP
        groupBoxKorals->setStatusTip(QApplication::translate("MainWindow", "\320\224\320\273\321\217 \320\264\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\275\320\276\320\262\320\276\320\263\320\276 \321\200\320\260\321\201\321\205\320\276\320\264\320\276\320\274\320\265\321\200\320\260 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 +", 0));
#endif // QT_NO_STATUSTIP
        groupBoxKorals->setTitle(QApplication::translate("MainWindow", "\320\224\320\260\321\202\321\207\320\270\320\272\320\270", 0));
#ifndef QT_NO_STATUSTIP
        cbCommonLoop->setStatusTip(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265/\320\262\321\213\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\276\320\277\321\200\320\276\321\201\320\260 \320\262\321\201\320\265\321\205 \320\275\320\260\320\271\320\264\320\265\320\275\320\275\321\213\321\205 \320\264\320\260\321\202\321\207\320\270\320\272\320\276\320\262", 0));
#endif // QT_NO_STATUSTIP
        cbCommonLoop->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\200\320\260\321\210\320\270\320\262\320\260\321\202\321\214 \320\262 \321\206\320\270\320\272\320\273\320\265", 0));
#ifndef QT_NO_STATUSTIP
        lStep->setStatusTip(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \321\210\320\260\320\263 \320\276\320\277\321\200\320\276\321\201\320\260 (\320\276\320\277\321\200\320\260\321\210\320\270\320\262\320\260\321\202\321\214 \321\201\320\273\320\265\320\264\321\203\321\211\320\270\320\271 \320\264\320\260\321\202\321\207\320\270\320\272 \321\207\320\265\321\200\320\265\320\267 N \320\274\320\270\320\273\320\273\320\270\321\201\320\265\320\272\321\203\320\275\320\264)", 0));
#endif // QT_NO_STATUSTIP
        lStep->setText(QApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\276\320\277\321\200\320\276\321\201\320\260", 0));
#ifndef QT_NO_STATUSTIP
        spinBox->setStatusTip(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \321\210\320\260\320\263 \320\276\320\277\321\200\320\276\321\201\320\260 (\320\276\320\277\321\200\320\260\321\210\320\270\320\262\320\260\321\202\321\214 \321\201\320\273\320\265\320\264\321\203\321\211\320\270\320\271 \320\264\320\260\321\202\321\207\320\270\320\272 \321\207\320\265\321\200\320\265\320\267 N \320\274\320\270\320\273\320\273\320\270\321\201\320\265\320\272\321\203\320\275\320\264)", 0));
#endif // QT_NO_STATUSTIP
        spinBox->setSuffix(QApplication::translate("MainWindow", " \320\274\321\201", 0));
        lLoopMode->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\200\320\276\321\201 \320\264\320\260\321\202\321\207\320\270\320\272\320\276\320\262", 0));
#ifndef QT_NO_STATUSTIP
        pbStart->setStatusTip(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\277\321\200\320\276\321\201 \320\277\320\276\320\274\320\265\321\207\320\265\320\275\320\275\321\213\321\205 \320\264\320\260\321\202\321\207\320\270\320\272\320\276\320\262", 0));
#endif // QT_NO_STATUSTIP
        pbStart->setText(QString());
#ifndef QT_NO_STATUSTIP
        pbStop->setStatusTip(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\276\320\277\321\200\320\276\321\201 \320\264\320\260\321\202\321\207\320\270\320\272\320\276\320\262", 0));
#endif // QT_NO_STATUSTIP
        pbStop->setText(QString());
#ifndef QT_NO_STATUSTIP
        groupBox->setStatusTip(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 / \320\262\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\273\320\276\320\263\320\263\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0));
#endif // QT_NO_STATUSTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#ifndef QT_NO_STATUSTIP
        teInputData->setStatusTip(QApplication::translate("MainWindow", "\320\236\320\272\320\275\320\276 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#endif // QT_NO_STATUSTIP
        teInputData->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
#ifndef QT_NO_STATUSTIP
        pbClear->setStatusTip(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\276\320\272\320\275\320\276 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#endif // QT_NO_STATUSTIP
        pbClear->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
