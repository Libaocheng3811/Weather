/********************************************************************************
** Form generated from reading UI file 'Weather.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHER_H
#define UI_WEATHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Weather
{
public:
    QWidget *widget;
    QLabel *date_lab;
    QLineEdit *cityLineEdit;
    QToolButton *search_btn;
    QToolButton *refresh_btn;
    QLabel *title_lab;
    QFrame *line;
    QLabel *temp_lab;
    QLabel *typeIcon_lab;
    QLabel *leaf_lab;
    QLabel *leafText_lab;
    QLabel *type_lab;
    QFrame *line_2;
    QLabel *subText_lab;
    QFrame *line_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QTextBrowser *gm_browser;
    QLabel *gmTxt_lab;
    QLabel *sunRise_lab;
    QFrame *line_4;
    QFrame *line_5;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QLabel *shidu_lab;
    QLabel *pm_lab;
    QLabel *fengliTxt_lab;
    QLabel *shiduTxt_lab;
    QLabel *fengxiang_lab;
    QLabel *fengxiangTxt_lab;
    QLabel *pmTxt_lab;
    QLabel *fengli_lab;
    QWidget *widget2;
    QGridLayout *gridLayout_3;
    QLabel *week0_lab;
    QLabel *week4_lab;
    QLabel *week3_lab;
    QLabel *week5_lab;
    QLabel *low0_lab;
    QLabel *week1_lab;
    QLabel *date0_lab;
    QLabel *week2_lab;
    QLabel *quality0_lab;
    QLabel *high0_lab;
    QLabel *date1_lab;
    QLabel *date2_lab;
    QLabel *date3_lab;
    QLabel *date4_lab;
    QLabel *date5_lab;
    QLabel *curve_lab;
    QLabel *quality1_lab;
    QLabel *quality2_lab;
    QLabel *quality3_lab;
    QLabel *quality4_lab;
    QLabel *quality5_lab;
    QLabel *type1_lab;
    QLabel *type2_lab;
    QLabel *type3_lab;
    QLabel *type4_lab;
    QLabel *type5_lab;
    QLabel *typeIco0_lab;
    QLabel *typeIco1_lab;
    QLabel *type0_lab;
    QLabel *typeIco3_lab;
    QLabel *high2_lab;
    QLabel *high1_lab;
    QLabel *typeIco2_lab;
    QLabel *high3_lab;
    QLabel *typeIco4_lab;
    QLabel *typeIco5_lab;
    QLabel *high4_lab;
    QLabel *high5_lab;
    QLabel *low1_lab;
    QLabel *low2_lab;
    QLabel *low3_lab;
    QLabel *low4_lab;
    QLabel *low5_lab;
    QWidget *widget3;
    QGridLayout *gridLayout_4;
    QLabel *locationIcon_lab;
    QLabel *location_lab;

    void setupUi(QWidget *Weather)
    {
        if (Weather->objectName().isEmpty())
            Weather->setObjectName("Weather");
        Weather->resize(800, 450);
        widget = new QWidget(Weather);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 800, 450));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"	border-image: url(:/weaUI/weaUI.png);\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QLabel{\n"
"	font: 25 10pt \"Microsoft YaHei\";\n"
"	border-radius: 4px;\n"
"	background-color: argb(60, 60, 60, 130);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"Line{\n"
"	background-color: rgb(0, 85, 0);\n"
"}"));
        date_lab = new QLabel(widget);
        date_lab->setObjectName("date_lab");
        date_lab->setGeometry(QRect(240, 10, 191, 31));
        date_lab->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\215\216\346\226\207\347\220\245\347\217\200\";\n"
"color: rgb(85, 255, 255)\n"
""));
        cityLineEdit = new QLineEdit(widget);
        cityLineEdit->setObjectName("cityLineEdit");
        cityLineEdit->setGeometry(QRect(460, 10, 261, 30));
        search_btn = new QToolButton(widget);
        search_btn->setObjectName("search_btn");
        search_btn->setGeometry(QRect(690, 10, 25, 31));
        search_btn->setStyleSheet(QString::fromUtf8("border-image: url(:/weatherIco/search.ico);"));
        search_btn->setCheckable(false);
        refresh_btn = new QToolButton(widget);
        refresh_btn->setObjectName("refresh_btn");
        refresh_btn->setGeometry(QRect(740, 10, 37, 31));
        refresh_btn->setStyleSheet(QString::fromUtf8("border-image: url(:/weatherIco/refresh.ico);"));
        title_lab = new QLabel(widget);
        title_lab->setObjectName("title_lab");
        title_lab->setGeometry(QRect(30, 10, 141, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200")});
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        title_lab->setFont(font);
        title_lab->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 127);\n"
"font: 20pt \"\345\215\216\346\226\207\347\220\245\347\217\200\";"));
        line = new QFrame(widget);
        line->setObjectName("line");
        line->setGeometry(QRect(5, 50, 800, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        temp_lab = new QLabel(widget);
        temp_lab->setObjectName("temp_lab");
        temp_lab->setGeometry(QRect(10, 50, 231, 121));
        temp_lab->setStyleSheet(QString::fromUtf8("font: 45pt \"\345\256\213\344\275\223\";"));
        temp_lab->setAlignment(Qt::AlignCenter);
        typeIcon_lab = new QLabel(widget);
        typeIcon_lab->setObjectName("typeIcon_lab");
        typeIcon_lab->setGeometry(QRect(240, 50, 91, 81));
        typeIcon_lab->setStyleSheet(QString::fromUtf8("border-image: url(:/day/day/\346\231\264.png);"));
        leaf_lab = new QLabel(widget);
        leaf_lab->setObjectName("leaf_lab");
        leaf_lab->setGeometry(QRect(10, 60, 31, 21));
        leaf_lab->setStyleSheet(QString::fromUtf8("image: url(:/weatherIco/leaf.ico)"));
        leafText_lab = new QLabel(widget);
        leafText_lab->setObjectName("leafText_lab");
        leafText_lab->setGeometry(QRect(40, 60, 51, 21));
        leafText_lab->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));
        type_lab = new QLabel(widget);
        type_lab->setObjectName("type_lab");
        type_lab->setGeometry(QRect(170, 60, 51, 21));
        type_lab->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));
        line_2 = new QFrame(widget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(5, 195, 331, 1));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        subText_lab = new QLabel(widget);
        subText_lab->setObjectName("subText_lab");
        subText_lab->setGeometry(QRect(10, 170, 301, 19));
        subText_lab->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 127);\n"
"font: 12pt \"Microsoft YaHei UI\";"));
        line_3 = new QFrame(widget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(5, 325, 331, 1));
        line_3->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 330, 171, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gm_browser = new QTextBrowser(gridLayoutWidget);
        gm_browser->setObjectName("gm_browser");
        gm_browser->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"color: rgb(255, 255, 255);\n"
"border: none;"));

        gridLayout_2->addWidget(gm_browser, 0, 1, 1, 1);

        gmTxt_lab = new QLabel(gridLayoutWidget);
        gmTxt_lab->setObjectName("gmTxt_lab");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gmTxt_lab->sizePolicy().hasHeightForWidth());
        gmTxt_lab->setSizePolicy(sizePolicy);
        gmTxt_lab->setLayoutDirection(Qt::LeftToRight);
        gmTxt_lab->setStyleSheet(QString::fromUtf8("background-color: argb(60, 60, 60, 130);\n"
"border-radius: 3px;\n"
"color: rgb(85, 255, 127);"));
        gmTxt_lab->setTextFormat(Qt::AutoText);
        gmTxt_lab->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(gmTxt_lab, 0, 0, 2, 1);

        sunRise_lab = new QLabel(widget);
        sunRise_lab->setObjectName("sunRise_lab");
        sunRise_lab->setGeometry(QRect(180, 340, 150, 100));
        line_4 = new QFrame(widget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(340, 50, 1, 391));
        line_4->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(widget);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(5, 50, 1, 401));
        line_5->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 200, 331, 121));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        shidu_lab = new QLabel(widget1);
        shidu_lab->setObjectName("shidu_lab");

        gridLayout->addWidget(shidu_lab, 0, 1, 1, 1);

        pm_lab = new QLabel(widget1);
        pm_lab->setObjectName("pm_lab");

        gridLayout->addWidget(pm_lab, 1, 1, 1, 1);

        fengliTxt_lab = new QLabel(widget1);
        fengliTxt_lab->setObjectName("fengliTxt_lab");

        gridLayout->addWidget(fengliTxt_lab, 2, 0, 1, 1);

        shiduTxt_lab = new QLabel(widget1);
        shiduTxt_lab->setObjectName("shiduTxt_lab");

        gridLayout->addWidget(shiduTxt_lab, 0, 0, 1, 1);

        fengxiang_lab = new QLabel(widget1);
        fengxiang_lab->setObjectName("fengxiang_lab");

        gridLayout->addWidget(fengxiang_lab, 2, 1, 1, 1);

        fengxiangTxt_lab = new QLabel(widget1);
        fengxiangTxt_lab->setObjectName("fengxiangTxt_lab");

        gridLayout->addWidget(fengxiangTxt_lab, 3, 0, 1, 1);

        pmTxt_lab = new QLabel(widget1);
        pmTxt_lab->setObjectName("pmTxt_lab");

        gridLayout->addWidget(pmTxt_lab, 1, 0, 1, 1);

        fengli_lab = new QLabel(widget1);
        fengli_lab->setObjectName("fengli_lab");

        gridLayout->addWidget(fengli_lab, 3, 1, 1, 1);

        widget2 = new QWidget(widget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(340, 60, 451, 381));
        gridLayout_3 = new QGridLayout(widget2);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        week0_lab = new QLabel(widget2);
        week0_lab->setObjectName("week0_lab");
        week0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week0_lab, 0, 0, 1, 1);

        week4_lab = new QLabel(widget2);
        week4_lab->setObjectName("week4_lab");
        week4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week4_lab, 0, 4, 1, 1);

        week3_lab = new QLabel(widget2);
        week3_lab->setObjectName("week3_lab");
        week3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week3_lab, 0, 3, 1, 1);

        week5_lab = new QLabel(widget2);
        week5_lab->setObjectName("week5_lab");
        week5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week5_lab, 0, 5, 1, 1);

        low0_lab = new QLabel(widget2);
        low0_lab->setObjectName("low0_lab");
        low0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low0_lab, 7, 0, 1, 1);

        week1_lab = new QLabel(widget2);
        week1_lab->setObjectName("week1_lab");
        week1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week1_lab, 0, 1, 1, 1);

        date0_lab = new QLabel(widget2);
        date0_lab->setObjectName("date0_lab");
        date0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date0_lab, 1, 0, 1, 1);

        week2_lab = new QLabel(widget2);
        week2_lab->setObjectName("week2_lab");
        week2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(week2_lab, 0, 2, 1, 1);

        quality0_lab = new QLabel(widget2);
        quality0_lab->setObjectName("quality0_lab");
        quality0_lab->setStyleSheet(QString::fromUtf8("color: rgb(85, 255, 127);"));
        quality0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality0_lab, 2, 0, 1, 1);

        high0_lab = new QLabel(widget2);
        high0_lab->setObjectName("high0_lab");
        high0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high0_lab, 5, 0, 1, 1);

        date1_lab = new QLabel(widget2);
        date1_lab->setObjectName("date1_lab");
        date1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date1_lab, 1, 1, 1, 1);

        date2_lab = new QLabel(widget2);
        date2_lab->setObjectName("date2_lab");
        date2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date2_lab, 1, 2, 1, 1);

        date3_lab = new QLabel(widget2);
        date3_lab->setObjectName("date3_lab");
        date3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date3_lab, 1, 3, 1, 1);

        date4_lab = new QLabel(widget2);
        date4_lab->setObjectName("date4_lab");
        date4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date4_lab, 1, 4, 1, 1);

        date5_lab = new QLabel(widget2);
        date5_lab->setObjectName("date5_lab");
        date5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(date5_lab, 1, 5, 1, 1);

        curve_lab = new QLabel(widget2);
        curve_lab->setObjectName("curve_lab");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(curve_lab->sizePolicy().hasHeightForWidth());
        curve_lab->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(curve_lab, 6, 0, 1, 6);

        quality1_lab = new QLabel(widget2);
        quality1_lab->setObjectName("quality1_lab");
        quality1_lab->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 127)"));
        quality1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality1_lab, 2, 1, 1, 1);

        quality2_lab = new QLabel(widget2);
        quality2_lab->setObjectName("quality2_lab");
        quality2_lab->setStyleSheet(QString::fromUtf8("color: rgb(255, 85, 127);"));
        quality2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality2_lab, 2, 2, 1, 1);

        quality3_lab = new QLabel(widget2);
        quality3_lab->setObjectName("quality3_lab");
        quality3_lab->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        quality3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality3_lab, 2, 3, 1, 1);

        quality4_lab = new QLabel(widget2);
        quality4_lab->setObjectName("quality4_lab");
        quality4_lab->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));
        quality4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality4_lab, 2, 4, 1, 1);

        quality5_lab = new QLabel(widget2);
        quality5_lab->setObjectName("quality5_lab");
        quality5_lab->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 127);"));
        quality5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(quality5_lab, 2, 5, 1, 1);

        type1_lab = new QLabel(widget2);
        type1_lab->setObjectName("type1_lab");
        type1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type1_lab, 3, 1, 1, 1);

        type2_lab = new QLabel(widget2);
        type2_lab->setObjectName("type2_lab");
        type2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type2_lab, 3, 2, 1, 1);

        type3_lab = new QLabel(widget2);
        type3_lab->setObjectName("type3_lab");
        type3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type3_lab, 3, 3, 1, 1);

        type4_lab = new QLabel(widget2);
        type4_lab->setObjectName("type4_lab");
        type4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type4_lab, 3, 4, 1, 1);

        type5_lab = new QLabel(widget2);
        type5_lab->setObjectName("type5_lab");
        type5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type5_lab, 3, 5, 1, 1);

        typeIco0_lab = new QLabel(widget2);
        typeIco0_lab->setObjectName("typeIco0_lab");
        sizePolicy1.setHeightForWidth(typeIco0_lab->sizePolicy().hasHeightForWidth());
        typeIco0_lab->setSizePolicy(sizePolicy1);
        typeIco0_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\344\270\255\351\233\250.png);"));

        gridLayout_3->addWidget(typeIco0_lab, 4, 0, 1, 1);

        typeIco1_lab = new QLabel(widget2);
        typeIco1_lab->setObjectName("typeIco1_lab");
        typeIco1_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\345\244\232\344\272\221.png);"));

        gridLayout_3->addWidget(typeIco1_lab, 4, 1, 1, 1);

        type0_lab = new QLabel(widget2);
        type0_lab->setObjectName("type0_lab");
        type0_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(type0_lab, 3, 0, 1, 1);

        typeIco3_lab = new QLabel(widget2);
        typeIco3_lab->setObjectName("typeIco3_lab");
        typeIco3_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\346\211\254\346\262\231.png);"));

        gridLayout_3->addWidget(typeIco3_lab, 4, 3, 1, 1);

        high2_lab = new QLabel(widget2);
        high2_lab->setObjectName("high2_lab");
        high2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high2_lab, 5, 2, 1, 1);

        high1_lab = new QLabel(widget2);
        high1_lab->setObjectName("high1_lab");
        high1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high1_lab, 5, 1, 1, 1);

        typeIco2_lab = new QLabel(widget2);
        typeIco2_lab->setObjectName("typeIco2_lab");
        typeIco2_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\351\230\265\351\233\250.png);"));

        gridLayout_3->addWidget(typeIco2_lab, 4, 2, 1, 1);

        high3_lab = new QLabel(widget2);
        high3_lab->setObjectName("high3_lab");
        high3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high3_lab, 5, 3, 1, 1);

        typeIco4_lab = new QLabel(widget2);
        typeIco4_lab->setObjectName("typeIco4_lab");
        typeIco4_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\346\262\231\345\260\230\346\232\264.png);"));

        gridLayout_3->addWidget(typeIco4_lab, 4, 4, 1, 1);

        typeIco5_lab = new QLabel(widget2);
        typeIco5_lab->setObjectName("typeIco5_lab");
        typeIco5_lab->setStyleSheet(QString::fromUtf8("image: url(:/day/day/\345\244\247\345\210\260\346\232\264\351\233\252.png);"));

        gridLayout_3->addWidget(typeIco5_lab, 4, 5, 1, 1);

        high4_lab = new QLabel(widget2);
        high4_lab->setObjectName("high4_lab");
        high4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high4_lab, 5, 4, 1, 1);

        high5_lab = new QLabel(widget2);
        high5_lab->setObjectName("high5_lab");
        high5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(high5_lab, 5, 5, 1, 1);

        low1_lab = new QLabel(widget2);
        low1_lab->setObjectName("low1_lab");
        low1_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low1_lab, 7, 1, 1, 1);

        low2_lab = new QLabel(widget2);
        low2_lab->setObjectName("low2_lab");
        low2_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low2_lab, 7, 2, 1, 1);

        low3_lab = new QLabel(widget2);
        low3_lab->setObjectName("low3_lab");
        sizePolicy.setHeightForWidth(low3_lab->sizePolicy().hasHeightForWidth());
        low3_lab->setSizePolicy(sizePolicy);
        low3_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low3_lab, 7, 3, 1, 1);

        low4_lab = new QLabel(widget2);
        low4_lab->setObjectName("low4_lab");
        low4_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low4_lab, 7, 4, 1, 1);

        low5_lab = new QLabel(widget2);
        low5_lab->setObjectName("low5_lab");
        low5_lab->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(low5_lab, 7, 5, 1, 1);

        widget3 = new QWidget(widget);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(190, 140, 141, 27));
        gridLayout_4 = new QGridLayout(widget3);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        locationIcon_lab = new QLabel(widget3);
        locationIcon_lab->setObjectName("locationIcon_lab");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(locationIcon_lab->sizePolicy().hasHeightForWidth());
        locationIcon_lab->setSizePolicy(sizePolicy2);
        locationIcon_lab->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";\n"
"Image: url(:/weatherIco/location.ico)"));

        gridLayout_4->addWidget(locationIcon_lab, 0, 0, 1, 1);

        location_lab = new QLabel(widget3);
        location_lab->setObjectName("location_lab");
        sizePolicy1.setHeightForWidth(location_lab->sizePolicy().hasHeightForWidth());
        location_lab->setSizePolicy(sizePolicy1);
        location_lab->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));

        gridLayout_4->addWidget(location_lab, 0, 1, 1, 1);


        retranslateUi(Weather);

        QMetaObject::connectSlotsByName(Weather);
    } // setupUi

    void retranslateUi(QWidget *Weather)
    {
        Weather->setWindowTitle(QCoreApplication::translate("Weather", "Widget", nullptr));
        date_lab->setText(QCoreApplication::translate("Weather", "2025-05-17", nullptr));
        cityLineEdit->setPlaceholderText(QCoreApplication::translate("Weather", "\345\237\216\345\270\202", nullptr));
        search_btn->setText(QString());
#if QT_CONFIG(shortcut)
        search_btn->setShortcut(QCoreApplication::translate("Weather", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        refresh_btn->setText(QString());
        title_lab->setText(QCoreApplication::translate("Weather", "\345\244\251\346\260\224\351\242\204\346\212\245", nullptr));
        temp_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        typeIcon_lab->setText(QString());
        leaf_lab->setText(QString());
        leafText_lab->setText(QCoreApplication::translate("Weather", "\344\274\230", nullptr));
        type_lab->setText(QCoreApplication::translate("Weather", "\346\231\264", nullptr));
        subText_lab->setText(QCoreApplication::translate("Weather", "\351\230\264\345\244\251\346\230\257\345\275\251\350\231\271\347\232\204\345\211\215\346\234\237\344\271\213\346\231\257", nullptr));
        gmTxt_lab->setText(QCoreApplication::translate("Weather", "\346\204\237\n"
"\345\206\222\n"
"\346\214\207\n"
"\346\225\260\n"
"", nullptr));
        sunRise_lab->setText(QString());
        shidu_lab->setText(QCoreApplication::translate("Weather", "86%", nullptr));
        pm_lab->setText(QCoreApplication::translate("Weather", "74", nullptr));
        fengliTxt_lab->setText(QCoreApplication::translate("Weather", "\351\243\216\345\220\221", nullptr));
        shiduTxt_lab->setText(QCoreApplication::translate("Weather", "\346\271\277\345\272\246", nullptr));
        fengxiang_lab->setText(QCoreApplication::translate("Weather", "\344\270\234\345\215\227\351\243\216", nullptr));
        fengxiangTxt_lab->setText(QCoreApplication::translate("Weather", "\351\243\216\345\212\233", nullptr));
        pmTxt_lab->setText(QCoreApplication::translate("Weather", "PM2.5", nullptr));
        fengli_lab->setText(QCoreApplication::translate("Weather", "<3\347\272\247", nullptr));
        week0_lab->setText(QCoreApplication::translate("Weather", "\346\230\250\345\244\251", nullptr));
        week4_lab->setText(QCoreApplication::translate("Weather", "\345\221\250\344\272\224", nullptr));
        week3_lab->setText(QCoreApplication::translate("Weather", "\345\221\250\345\233\233", nullptr));
        week5_lab->setText(QCoreApplication::translate("Weather", "\345\221\250\344\272\224", nullptr));
        low0_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        week1_lab->setText(QCoreApplication::translate("Weather", "\344\273\212\345\244\251", nullptr));
        date0_lab->setText(QCoreApplication::translate("Weather", "01/01", nullptr));
        week2_lab->setText(QCoreApplication::translate("Weather", "\345\221\250\344\270\211", nullptr));
        quality0_lab->setText(QCoreApplication::translate("Weather", "\344\274\230\350\264\250", nullptr));
        high0_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        date1_lab->setText(QCoreApplication::translate("Weather", "01/02", nullptr));
        date2_lab->setText(QCoreApplication::translate("Weather", "01/03", nullptr));
        date3_lab->setText(QCoreApplication::translate("Weather", "01/04", nullptr));
        date4_lab->setText(QCoreApplication::translate("Weather", "01/05", nullptr));
        date5_lab->setText(QCoreApplication::translate("Weather", "01/06", nullptr));
        curve_lab->setText(QString());
        quality1_lab->setText(QCoreApplication::translate("Weather", "\350\211\257\345\245\275", nullptr));
        quality2_lab->setText(QCoreApplication::translate("Weather", "\350\275\273\345\272\246\346\261\241\346\237\223", nullptr));
        quality3_lab->setText(QCoreApplication::translate("Weather", "\344\270\255\345\272\246\346\261\241\346\237\223", nullptr));
        quality4_lab->setText(QCoreApplication::translate("Weather", "\351\207\215\345\272\246\346\261\241\346\237\223", nullptr));
        quality5_lab->setText(QCoreApplication::translate("Weather", "\350\211\257\345\245\275", nullptr));
        type1_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        type2_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        type3_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        type4_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        type5_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        typeIco0_lab->setText(QString());
        typeIco1_lab->setText(QString());
        type0_lab->setText(QCoreApplication::translate("Weather", "\351\230\264", nullptr));
        typeIco3_lab->setText(QString());
        high2_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        high1_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        typeIco2_lab->setText(QString());
        high3_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        typeIco4_lab->setText(QString());
        typeIco5_lab->setText(QString());
        high4_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        high5_lab->setText(QCoreApplication::translate("Weather", "9\302\260", nullptr));
        low1_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        low2_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        low3_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        low4_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        low5_lab->setText(QCoreApplication::translate("Weather", "6\302\260", nullptr));
        locationIcon_lab->setText(QString());
        location_lab->setText(QCoreApplication::translate("Weather", "\351\207\215\345\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Weather: public Ui_Weather {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHER_H
