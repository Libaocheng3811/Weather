#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QPoint>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QRect>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>

#include "WeatherTool.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Weather;
}
QT_END_NAMESPACE

struct Today
{
    QString date;
    QString wendu;
    QString city;
    QString shidu;
    QString pm25;
    QString quality;
    QString ganmao;
    QString fx;
    QString fl;
    QString type;
    QString sunrise;
    QString sunset;
    QString notice;
};

struct Forecast
{
    QString date;
    QString week;
    QString type;
    QString high;
    QString low;
    QString aqi;
};

class Weather : public QWidget {
  Q_OBJECT

 public:
  explicit Weather(QWidget* parent = nullptr);
  ~Weather();

 protected:
  bool eventFilter(QObject* watched, QEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
     void mousePressEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent* menuEvent); //QContextMenuEvent` 是 Qt 提供的事件类型，代表用户右键点击、触发上下文菜单时的事件。

 public slots:
    void slot_exitApp();
     void replyFinished(QNetworkReply* reply);
    void on_searchBt_clicked();
     void on_refreshBt_clicked();


 private:
    Ui::Weather* ui;

     QList<QLabel*> forecast_week_list;
     QList<QLabel*> forecast_date_list;
     QList<QLabel*> forecast_aqi_list;
     QList<QLabel*> forecast_type_list;
     QList<QLabel*> forecast_typeIco_list;
     QList<QLabel*> forecast_high_list;
     QList<QLabel*> forecast_low_list;

     Today today;
     Forecast forecast[6];

     // 静态常量

     static const QPoint sun[2];
     static const QRect sunRizeset[2];
     static const QRect rect[2];

     QTimer *sunTimer;

     // QNetworkAccessManager 对象，用于发送网络请求,是 Qt 中发送 HTTP 请求的核心类。

     QNetworkAccessManager* manager;
     QString url;
     QString city;
     QString cityTmp;

    // 窗口移动
    QPoint  mPos;
    // 右键菜单
    QMenu* m_pMenu;
    QAction* m_pExitAct;

    WeatherTool tool;

    void getWeatherInfo(QNetworkAccessManager* manager);
    void parseJson(QByteArray bytes);
    void setLabelContent();
    void paintSunRiseSet();
    void paintCurve();
    void callKeyBoard();



};
#endif  // WEATHER_H
