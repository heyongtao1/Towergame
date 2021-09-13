/********************************************************************************
** Form generated from reading UI file 'second_level.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECOND_LEVEL_H
#define UI_SECOND_LEVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Second_Level
{
public:

    void setupUi(QWidget *Second_Level)
    {
        if (Second_Level->objectName().isEmpty())
            Second_Level->setObjectName(QStringLiteral("Second_Level"));
        Second_Level->resize(800, 600);
        Second_Level->setStyleSheet(QStringLiteral("background-image: url(:/Map.png);"));

        retranslateUi(Second_Level);

        QMetaObject::connectSlotsByName(Second_Level);
    } // setupUi

    void retranslateUi(QWidget *Second_Level)
    {
        Second_Level->setWindowTitle(QApplication::translate("Second_Level", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Second_Level: public Ui_Second_Level {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECOND_LEVEL_H
