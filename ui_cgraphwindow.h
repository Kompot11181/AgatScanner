/********************************************************************************
** Form generated from reading UI file 'cgraphwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CGRAPHWINDOW_H
#define UI_CGRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cGraphWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lValue;
    QLabel *lNominal;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;

    void setupUi(QDialog *cGraphWindow)
    {
        if (cGraphWindow->objectName().isEmpty())
            cGraphWindow->setObjectName(QStringLiteral("cGraphWindow"));
        cGraphWindow->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cGraphWindow->sizePolicy().hasHeightForWidth());
        cGraphWindow->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(cGraphWindow);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        lValue = new QLabel(cGraphWindow);
        lValue->setObjectName(QStringLiteral("lValue"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lValue->sizePolicy().hasHeightForWidth());
        lValue->setSizePolicy(sizePolicy1);
        lValue->setMinimumSize(QSize(0, 20));
        lValue->setMaximumSize(QSize(16777215, 20));
        lValue->setBaseSize(QSize(0, 20));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lValue->setFont(font);
        lValue->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        lValue->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_2->addWidget(lValue);

        lNominal = new QLabel(cGraphWindow);
        lNominal->setObjectName(QStringLiteral("lNominal"));
        sizePolicy1.setHeightForWidth(lNominal->sizePolicy().hasHeightForWidth());
        lNominal->setSizePolicy(sizePolicy1);
        lNominal->setMinimumSize(QSize(0, 20));
        lNominal->setFont(font);

        horizontalLayout_2->addWidget(lNominal);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(cGraphWindow);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setToolTipDuration(300);

        horizontalLayout->addWidget(widget);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(cGraphWindow);

        QMetaObject::connectSlotsByName(cGraphWindow);
    } // setupUi

    void retranslateUi(QDialog *cGraphWindow)
    {
        cGraphWindow->setWindowTitle(QApplication::translate("cGraphWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\260", 0));
        lValue->setText(QApplication::translate("cGraphWindow", "0", 0));
        lNominal->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class cGraphWindow: public Ui_cGraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGRAPHWINDOW_H
