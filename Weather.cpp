#include "Weather.h"
#include "ui_Weather.h"

#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>
#include <QPoint>
#include <QRect>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QNetworkAccessManager>

#include "WeatherUtils.h"

#define SPAN_INDEX 3 // 温度曲线间隔指数
#define ORIGIN_SIZE 3 // 温度曲线原点大小
#define TEMPERATURE_STARTING_COORDINATE 45 // 高温平均值起始坐标


// 日出日落底线
const QPoint Weather::sun[2] = {
    QPoint(20, 75 ),
    QPoint(130, 75 )
};

// 日出日落时间
// QRect: Qt 中的一个类，用于表示一个矩形区域。它通常由左上角的 x 坐标、y 坐标、宽度 (width) 和高度 (height) 定义。
const QRect Weather::sunRizeset[2] = {
    QRect(0, 80, 50, 20),
    QRect(100, 80, 50, 20)
};

// 日出日落圆弧
const QRect Weather::rect[2] = {
    QRect(25, 25, 100, 100), // 虚线圆弧
    QRect(50, 80, 50, 20) // “日出日落”文本
};

Weather::Weather(QWidget* parent) : QWidget(parent), ui(new Ui::Weather)
{
  ui->setupUi(this);

    // 设置窗口为固定大小
    setFixedSize(width(), height());
  // 设置无边框模式，无边框模式会隐藏退出，以及最大最小化按钮,并且不能鼠标拖动
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/weaUI/AppIcon.jpg"));

    // 右键菜单退出
    m_pMenu = new QMenu(this); // this指定了menu的父对象为当前对象（Weather）
    m_pExitAct = new QAction(this);
    m_pExitAct->setText("exit");
    // :表示根目录，就是Resources文件夹，icons.qrc并不是目录，是资源配置文件
    m_pExitAct->setIcon(QIcon(":/weatherIco/close.ico")); // 设置图标
    m_pMenu->addAction(m_pExitAct);
    // connect(m_pExitAct, SIGNAL(triggered(bool)), this, SLOT(slot_exitApp()));
    connect(m_pExitAct, &QAction::triggered, this, &Weather::slot_exitApp); // 更推荐这种写法

    // 将标签放入列表中
    forecast_week_list << ui->week0_lab << ui->week1_lab << ui->week2_lab << ui->week3_lab << ui->week4_lab << ui->week5_lab;
    forecast_date_list << ui->date0_lab << ui->date1_lab << ui->date2_lab << ui->date3_lab << ui->date4_lab << ui->date5_lab;
    forecast_type_list << ui->type0_lab << ui->type1_lab << ui->type2_lab << ui->type3_lab <<ui->type4_lab << ui->type5_lab;
    forecast_aqi_list << ui->quality0_lab << ui->quality1_lab << ui->quality2_lab << ui->quality3_lab << ui->quality4_lab <<ui->quality5_lab;
    forecast_typeIco_list << ui->typeIco0_lab << ui->typeIco1_lab << ui->typeIco2_lab << ui->typeIco3_lab << ui->typeIco4_lab << ui->typeIco5_lab;
    forecast_high_list << ui->high0_lab << ui->high1_lab << ui->high2_lab << ui->high3_lab << ui->high4_lab << ui->high5_lab;
    forecast_low_list << ui->low0_lab << ui->low1_lab << ui->low2_lab << ui->low3_lab << ui->low4_lab << ui->low5_lab;

    // 结构体初始化
    today.date = "0000-00-00 ";
    today.city = "null ";
    today.fl = u8"无数据 ";
    today.fx = u8"无数据 ";
    today.ganmao = u8"无数据 ";
    today.notice = u8"无数据 ";
    today.pm25 = u8"无数据 ";
    today.quality = u8"无数据 ";
    today.shidu = u8"无数据 ";
    today.sunrise = "00:00 ";
    today.sunset = "00:00 ";
    today.wendu = "null ";
    today.type = u8"无数据 ";

    for(int i = 0; i < 6; i++)
    {
        forecast[i].aqi = "0";
        forecast[i].week = "星期";
        forecast[i].date = "00日星期0 ";
        forecast[i].high = "高温 0.0℃ ";
        forecast[i].low = "低温 0.0℃ ";
        forecast[i].type = "undefined";
    }

    // date_lab和week_lab样式设置,设置背景色
    for(int i = 0; i < 6; i++)
    {
        forecast_week_list[i]->setStyleSheet("background-color: rgba(0, 255, 255, 100);");
        forecast_date_list[i]->setStyleSheet("background-color: rgba(0, 255, 255, 100);");
    }

    // 请求天气API信息
    url = "http://t.weather.itboy.net/api/weather/city/";
    city = "成都";
    cityTmp = city;
    manager = new QNetworkAccessManager(this);

    // 当 manager 发出的某个请求完成后，会发出 finished(QNetworkReply*) 信号。
    // 相当于通知数据返回来了，可以获取了

    connect(manager, &QNetworkAccessManager::finished, this, &Weather::replyFinished);
    // 请求数据

    getWeatherInfo(manager);

    // 事件过滤
    // installEventFilter(QObject *filterObj):是 QObject 类的一个成员函数。将 filterObj（过滤器对象）安装到调用该函数的对象（被监视对象）上。
    // 任何发送给 ui->sunRise_lab 的事件（例如鼠标移动、点击等）会首先被发送到 this 对象的 eventFilter() 函数。
    // this 对象必须重写 QObject::eventFilter(QObject *watched, QEvent *event) 这个虚函数。
    /* 在 eventFilter() 函数内部，this 对象可以：
        检查事件类型和被监视的对象：
        watched 参数是指向事件最初目标对象（即 ui->sunRise_lab）的指针。
        event 参数是指向发生的事件对象的指针。
        处理事件： 根据事件类型和被监视的对象，执行自定义的逻辑。例如，可以改变控件的外观、响应特定的按键、或者执行某些操作。
        决定事件是否继续传递：
        如果 eventFilter() 函数返回 true，表示该事件已经被过滤器处理完毕，不应再传递给被监视对象 (ui->sunRise_lab) 的标准事件处理函数（如 mousePressEvent()）。事件处理到此为止。
        如果 eventFilter() 函数返回 false，表示过滤器没有完全处理该事件（或者只是观察了事件），事件应该继续传递给被监视对象 (ui->sunRise_lab) 进行其正常的事件处理。
        通常，如果过滤器不处理特定事件，应该调用基类的 eventFilter() 并返回其结果：return QObject::eventFilter(watched, event); 或 return false;。
     */
    ui->sunRise_lab->installEventFilter(this);
    ui->curve_lab->installEventFilter(this);
    ui->cityLineEdit->installEventFilter(this);

    // 创建一个 QTimer 定时器对象，并将 ui->sunRise_lab 设置为其父对象。
    sunTimer = new QTimer(ui->sunRise_lab);
    // connect(sunTimer, &QTimer::timeout, ui->sunRise_lab, &QLabel::update); // 这么写是错误的，因为QLabel::update() 是一个公共成员函数，但它不是 Qt 声明的槽（slot）函数
    // 老式写法
    // connect(sunTimer, SIGNAL(timeout()), ui->sunRise_lab, SLOT(update()));
    // 新式写法
    // 每隔 1 秒自动刷新一次 ui->sunRise_lab
    // ui->sunRise_lab->update() 的作用是：
    // 请求 Qt 重新绘制该控件（这里是 QLabel），即触发一次重绘事件 paintEvent()
    connect(sunTimer, &QTimer::timeout, this, [=]() {
        ui->sunRise_lab->update();
    });

    // 定时器负责周期性地发出信号（如每隔 1000 毫秒触发一次 timeout() 信号）。
    sunTimer->start(1000);

    connect(ui->search_btn, &QToolButton::clicked, this, &Weather::on_searchBt_clicked);
    connect(ui->refresh_btn, &QToolButton::clicked, this, &Weather::on_refreshBt_clicked);

}

Weather::~Weather() { delete ui; }

// 获取响应信息
void Weather::replyFinished(QNetworkReply* reply)
{
    // 获取 HTTP 响应的状态码，状态码为200表示正常。
    // 调用 QNetworkReply 的 attribute() 方法。这个方法用于获取与请求或响应相关的特定属性。
    // QNetworkRequest::HttpStatusCodeAttribute: 这是一个枚举值，代表要查询的属性是 HTTP 状态码
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(reply->error() != QNetworkReply::NoError || status_code != 200)
    {
        // QMessageBox::Ok: 对话框只显示一个 "OK" 按钮。
        QMessageBox::warning(this, u8"错误", u8"天气：请求数据错误，检查网络连接！", QMessageBox::Ok);
        return;
    }

    // 如果网络请求和 HTTP 状态都表示成功，则读取响应体中的所有数据
    // QByteArray: Qt 中用于存储原始字节数组的类，常用于处理网络数据、文件内容等
    // 天气 API 返回的 JSON 数据通常就是以字节流的形式接收的。
    QByteArray bytes = reply->readAll();

    // 解析返回的JSON数据
    parseJson(bytes);
}

// 请求数据
void Weather::getWeatherInfo(QNetworkAccessManager* manager)
{
    // 获取城市邮政编码
    QString cityCode = tool[city];
    if(cityCode == "000000000")
    {
        // 弹出一个警告窗口
        QMessageBox::warning(this, u8"错误 ", u8"天气：指定城市不存在 ", QMessageBox::Ok);
        return;
    }
    // 获取完整的天气接口URL
    QUrl jsonUrl(url + cityCode);
    // 使用 `manager` 发起一个 GET 请求，访问上面构造好的 URL。请求返回后，Qt 会自动触发你之前写的信号槽
    // QNetworkRequest: 这个类封装了一个网络请求的所有信息,get() 函数的参数位置创建并传递一个 QNetworkRequest 对象。
    // manager->get() 函数会返回一个指向 QNetworkReply 对象的指针 (QNetworkReply*)。QNetworkReply 类封装了对特定网络请求的响应,通过QNetworkReply对象可以获得相应的数据
    manager->get(QNetworkRequest(jsonUrl));
}

// 解析JSON数据
void Weather::parseJson(QByteArray bytes)
{
    // JSON 格式有效性检查
    // 将传入的 QByteArray 解析为一个 QJsonDocument 对象，并检查解析过程中是否发生错误。
    // 如果解析成功返回一个有效的 QJsonDocument；如果失败，err 对象会包含错误详情
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &err); // 检测json格式
    if (err.error != QJsonParseError::NoError) // Json格式错误
    {
        return;
    }

    // 假设 JSON 数据的顶层结构是一个对象，将其转换为 QJsonObject
    QJsonObject jsObj = jsonDoc.object();
    // 从顶层对象中获取键为 "message" 的值，并将其转换为字符串
    QString message = jsObj.value("message").toString();
    // 检查 "message" 字符串是否不包含 "success"。这是一种常见的 API 设计，用消息字段来传达成功或失败的状态。
    if (!message.contains("success"))
    {
        QMessageBox::information(this, tr("The information of Json_desc"),
                                 u8"天气：城市错误！", QMessageBox::Ok );
        city = cityTmp;
        return;
    }

    // 从顶层 JSON 对象中提取日期和城市名称，并存储到 today 对象的相应成员中。
    // jsObj.value("cityInfo").toObject()获取 "date" 字段的值
    QString dateStr = jsObj.value("date").toString();
    today.date = QDate::fromString(dateStr, "yyyyMMdd").toString("yyyy-MM-dd");
    // 获取名为 "cityInfo" 的嵌套 JSON 对象
    // value("city").toString(): 从 "cityInfo" 对象中获取 "city" 字段的值（城市名称），并赋值给 today.city。
    today.city = jsObj.value("cityInfo").toObject().value("city").toString();

    // 解析data,从名为 "data" 的嵌套 JSON 对象中提取湿度、PM2.5、空气质量、温度和感冒指数等信息
    //
    QJsonObject dataObj = jsObj.value("data").toObject();
    today.shidu = dataObj.value("shidu").toString();
    // API 可能返回数字类型，所以先用 toDouble() 转换，然后用 QString::number() 转为字符串
    today.pm25 = QString::number( dataObj.value("pm25").toDouble() );
    today.quality = dataObj.value("quality").toString();
    today.wendu = dataObj.value("wendu").toString() + u8"°";
    today.ganmao = dataObj.value("ganmao").toString();

    // 解析data中的yesterday
    // 获取名为"yestoday"的嵌套对象
    QJsonObject yestObj = dataObj.value("yesterday").toObject();
    forecast[0].date = yestObj.value("date").toString();
    forecast[0].high = yestObj.value("high").toString();
    forecast[0].low = yestObj.value("low").toString();
    forecast[0].aqi = QString::number( yestObj.value("aqi").toDouble() );
    forecast[0].type = yestObj.value("type").toString();

    // 解析data中的forecast
    //  从 "data" 对象中名为 "forecast" 的 JSON 数组中提取未来几天的天气预报信息，并存储到 forecast 数组的后续元素中 (从 forecast[1] 开始)
    QJsonArray forecastArr = dataObj.value("forecast").toArray();
    int j = 0;
    for (int i = 1; i < 6; i++)
    {
        // 取 JSON 数组中第 j 个元素（是一个 JSON 对象，代表一天的预报）
        QJsonObject dateObj = forecastArr.at(j).toObject();
        forecast[i].date = dateObj.value("date").toString();
        forecast[i].week = dateObj.value("week").toString();
        forecast[i].aqi = QString::number( dateObj.value("aqi").toDouble() );
        forecast[i].high = dateObj.value("high").toString();
        forecast[i].low = dateObj.value("low").toString();
        forecast[i].type = dateObj.value("type").toString();
        j++;
    }

    // 取得今日数据
    QJsonObject todayObj = forecastArr.at(0).toObject();
    today.fx = todayObj.value("fx").toString();
    today.fl = todayObj.value("fl").toString();
    today.type = todayObj.value("type").toString();
    today.sunrise = todayObj.value("sunrise").toString();
    today.sunset = todayObj.value("sunset").toString();
    today.notice = todayObj.value("notice").toString();

    setLabelContent();
}

// 设置控件文本
void Weather::setLabelContent()
{
    // 今日数据
    ui->date_lab->setText(today.date);
    ui->temp_lab->setText(today.wendu);
    ui->location_lab->setText(today.city);
    ui->type_lab->setText(today.type);
    ui->subText_lab->setText(today.notice);
    ui->shidu_lab->setText(today.shidu);
    ui->pm_lab->setText(today.pm25);
    ui->fengxiang_lab->setText(today.fx);
    ui->fengli_lab->setText(today.fl);
    ui->gm_browser->setText(today.ganmao);

    // 判断白天还是夜晚图标
    QString sunsetTime = today.date + " " + today.sunset;
    if (QDateTime::currentDateTime() <= QDateTime::fromString(sunsetTime, "yyyy-MM-dd hh::mm"))
    {
        // iconPath为完整路径
        QString iconPath = WeatherUtils::getWeatherIconResourcePath(today.type, true); // true表示白天
        ui->typeIcon_lab->setStyleSheet(tr("border-image: url(%1); background-color: argb(60, 60, 60, 0);").arg(iconPath));
    }
    else
    {
        QString iconPath = WeatherUtils::getWeatherIconResourcePath(today.type, false); // false表示晚上
        ui->typeIcon_lab->setStyleSheet(tr("border-image: url(%1); background-color: argb(60, 60, 60, 0);").arg(iconPath));
    }

    ui->leafText_lab->setText(today.quality == "" ? "无 " : today.quality); // 设置天气质量标签
    if (today.quality == "优 ")
    {
        ui->leafText_lab->setStyleSheet("color: rgb(0, 255, 0); background-color: argb(255, 255, 255, 0);");
    }
    else if (today.quality == "良 ")
    {
        ui->leafText_lab->setStyleSheet("color: rgb(255, 255, 0); background-color: argb(255, 255, 255, 0);");
    }
    else if (today.quality == "轻度污染 ")
    {
        ui->leafText_lab->setStyleSheet("color: rgb(255, 170, 0); background-color: argb(255, 255, 255, 0);");
    }
    else if (today.quality == "重度污染 ")
    {
        ui->leafText_lab->setStyleSheet("color: rgb(255, 0, 0); background-color: argb(255, 255, 255, 0);");
    }
    else if (today.quality == "严重污染 ")
    {
        ui->leafText_lab->setStyleSheet("color: rgb(170, 0, 0); background-color: argb(255, 255, 255, 0);");
    }
    else
    {
        ui->leafText_lab->setStyleSheet("color: rgb(255, 255, 255); background-color: argb(255, 255, 255, 0);");
    }

    // 六天的数据
    for(int i = 0; i < 6; i++)
    {
        forecast_week_list[i]->setText(forecast[i].week.right(3));
        forecast_date_list[i]->setText(forecast[i].date.left(3));
        forecast_type_list[i]->setText(forecast[i].type);
        forecast_high_list[i]->setText(forecast[i].high.split(" ").at(1));
        forecast_low_list[i]->setText(forecast[i].low.split(" ").at(1));
        // 由于没有获取夜晚图标，所以只能显示白天的图标
        QString iconPath = WeatherUtils::getWeatherIconResourcePath(forecast[i].type, true);
        forecast_typeIco_list[i]->setStyleSheet(tr("image: url(%1);").arg(iconPath));

        // 根据aqi指数设置显示文字以及文字颜色
        if (forecast[i].aqi.toInt() >= 0 && forecast[i].aqi.toInt() <= 50)
        {
            forecast_aqi_list[i]->setText(u8"优质 ");
            forecast_aqi_list[i]->setStyleSheet("color: rgb(0, 255, 0);");
        }
        else if (forecast[i].aqi.toInt() > 50 && forecast[i].aqi.toInt() <= 100)
        {
            forecast_aqi_list[i]->setText(u8"良好 ");
            forecast_aqi_list[i]->setStyleSheet("color: rgb(255, 255, 0);");
        }
        else if (forecast[i].aqi.toInt() > 100 && forecast[i].aqi.toInt() <= 150)
        {
            forecast_aqi_list[i]->setText(u8"轻度污染 ");
            forecast_aqi_list[i]->setStyleSheet("color: rgb(255, 170, 0);");
        }
        else if (forecast[i].aqi.toInt() > 150 && forecast[i].aqi.toInt() <= 200)
        {
            forecast_aqi_list[i]->setText(u8"重度污染 ");
            forecast_aqi_list[i]->setStyleSheet("color: rgb(255, 0, 0);");
        }
        else
        {
            forecast_aqi_list[i]->setText(u8"严重污染 ");
            forecast_aqi_list[i]->setStyleSheet("color: rgb(170, 0, 0);");
        }
    }

    // 单独显示今天、昨天、明天
    ui->week0_lab->setText(u8"昨天 ");
    ui->week1_lab->setText(u8"今天 ");
    // ui->week2_lab->setText(u8"明天 ");

    // ?
    ui->curve_lab->update();
}

// 搜索
void Weather::on_searchBt_clicked()
{
    cityTmp = city;
    city = ui->cityLineEdit->text();
    getWeatherInfo(manager);

}

// 刷新
void Weather::on_refreshBt_clicked()
{
    getWeatherInfo(manager);
    ui->curve_lab->update();
}

// 事件过滤
bool Weather::eventFilter(QObject* watched, QEvent* event)
{
    // 拦截 sunRise_lab 的绘制事件
    if (watched == ui->sunRise_lab && event->type() == QEvent::Paint)
    {
        // 调用自定义的绘制函数, 如果不拦截会调用默认的绘制函数
        // 代码没有让 ui->sunRise_lab 执行其默认的 paintEvent，而是调用了 Weather 类中一个名为 paintSunRiseSet() 的成员函数。
        paintSunRiseSet();
    }
    else if (watched == ui->curve_lab && event->type() == QEvent::Paint) // 拦截 curve_lab 的绘制事件
    {
        paintCurve();
    }
    else if (watched == ui->cityLineEdit && event->type() == QEvent::MouseButtonPress) //  拦截 cityLineEdit 的鼠标按下事件
    {
        callKeyBoard(); //调用软键盘
    }

    // 对于事件过滤器中没有显式处理的事件（即不满足上述 if 或 else if 条件的事件），这行代码会将事件传递给 Weather 类的基类 (QWidget) 的 eventFilter() 方法。
    // 这是事件过滤器的标准做法。它确保了那些过滤器不关心的事件仍然能够被被监视对象（或其父类链）以正常的方式处理。
    // 如果不调用基类的 eventFilter 或返回 false，可能会导致某些默认行为（如 QLabel 显示文本，QLineEdit 响应键盘输入等）失效
    return QWidget::eventFilter(watched,event);
}

// 绘制日出日落图
// 在label中绘制使用到的坐标以及矩形坐标都是相对于绘制目标label的内部坐标
void Weather::paintSunRiseSet()
{
    // 创建一个 QPainter 对象，并将其与 ui->sunRise_lab UI 元素关联起来。这意味着所有后续的绘图操作都将在这个 QLabel
    // QPainter构造函数接受一个类型为QPaintDeviec的指针对象，而QWidget又继承自QPaintDevice
    QPainter painter(ui->sunRise_lab);
    // 启用抗锯齿渲染，使线条更加平滑
    painter.setRenderHint(QPainter::Antialiasing, true); // 反锯齿

    // 绘制日出日落线和文本
    // save() 保存当前 QPainter 的状态（如画笔、画刷、字体、变换等）。
    painter.save();
    // 获取当前的画笔
    QPen pen = painter.pen();
    pen.setWidthF(0.5); // 设置画笔宽度为0.5像素
    pen.setColor(Qt::yellow); // 设置画笔颜色
    painter.setPen(pen); // 设置pen为当前画笔
    painter.drawLine(sun[0], sun[1]); // 使用之前定义的点绘制一条线
    // restore() 恢复到上次 save() 时保存的状态
    painter.restore();

    painter.save();
    painter.setFont( QFont("Microsoft Yahei", 8, QFont::Normal) ); // 字体、大小、正常粗细
    painter.setPen(Qt::white);

    // 如果日出日落时间不为空，则绘制日出日落时间文本
    if (today.sunrise != "" && today.sunset != "")
    {
        painter.drawText(sunRizeset[0], Qt::AlignHCenter, today.sunrise);
        painter.drawText(sunRizeset[1], Qt::AlignHCenter, today.sunset);
    }
    // 绘制文本
    //
    painter.drawText(rect[1], Qt::AlignHCenter, u8"日出日落");
    painter.restore();

    // 绘制圆弧
    painter.save();
    //    pen.setWidth(1);
    pen.setWidthF(0.5);
    pen.setStyle(Qt::DotLine); // 虚线
    pen.setColor(Qt::green);
    painter.setPen(pen);
    // 在之前定义的 rect[0] (QRect(25, 25, 100, 100)) 矩形边界框内绘制一个圆弧。
    // 0 * 16: 起始角度。Qt 中角度以 1/16 度为单位，所以这是 0 度 (通常是 3 点钟方向)。180 * 16: 跨越角度。这是 180 度。
    painter.drawArc(rect[0], 0 * 16, 180 * 16);
    painter.restore();

    // 绘制日出日落占比
    if (today.sunrise != "" && today.sunset != "")
    {
        painter.setPen(Qt::NoPen); // s设置无边框画笔
        painter.setBrush(QColor(255, 85, 0, 100));  // 设置画刷，RGBA，a表示透明度

        int startAngle, spanAngle; // 用于扇形绘制的起始角度和终止角度
        QString sunsetTime = today.date + " " + today.sunset;

        // 判断当前时间是否已过日落，如果已过日落，则填充整个半圆，表示太阳已经完全落下
        if (QDateTime::currentDateTime() > QDateTime::fromString(sunsetTime, "yyyy-MM-dd hh:mm"))
        {
            startAngle = 0 * 16;
            spanAngle = 180 * 16;
        }
        else
        {
            // 计算起始角度和跨越角度
            // Qt 的 QString::split() 方法。按照冒号 : 分隔字符串。
            static QStringList sunSetTime = today.sunset.split(":");
            static QStringList sunRiseTime = today.sunrise.split(":");

            static QString sunsetHour = sunSetTime.at(0);
            static QString sunsetMint = sunSetTime.at(1);
            static QString sunriseHour = sunRiseTime.at(0);
            static QString sunriseMint = sunRiseTime.at(1);

            // 将 "hh:mm" 格式的日出日落时间转换为从午夜开始的总分钟数
            static int sunrise = sunriseHour.toInt() * 60 + sunriseMint.toInt();
            static int sunset = sunsetHour.toInt() * 60 + sunsetMint.toInt();
            int now = QTime::currentTime().hour() * 60 + QTime::currentTime().minute(); // 将当前时间也转换成从午夜开始的总分钟数

            //  计算角度
            startAngle = ( (double)(sunset - now) / (sunset - sunrise) ) * 180 * 16;
            spanAngle = ( (double)(now - sunrise) / (sunset - sunrise) ) * 180 * 16;
        }

        if (startAngle >= 0 && spanAngle >= 0)
        {
            // Qt 的 drawPie 从 startAngle 开始，逆时针绘制 spanAngle 度的扇形。
            painter.drawPie(rect[0], startAngle, spanAngle); // 扇形绘制
        }
    }
}

// 绘制温度曲线
void Weather::paintCurve()
{
    QPainter painter(ui->curve_lab);
    painter.setRenderHint(QPainter::Antialiasing, true); // 反锯齿

    // 将温度转换为int类型，并计算平均值，平均值作为curveLb曲线的参考值，参考Y坐标为45
    int tempTotal = 0;
    int high[6] = {};
    int low[6] = {};

    QString h, l;
    // 解析温度数据
    for (int i = 0; i < 6; i++)
    {
        // forecast 是一个包含未来天气预报数据的数组或列表，每个元素有一个 high 成员（字符串类型），例如 "高温 25℃"。 .split(" "): 按空格分割字符串，得到如 ["高温", "25℃"] 的列表。
        // .at(1): 取第二个元素，即 "25℃"。
        h = forecast[i].high.split(" ").at(1);
        // 移除字符串末尾的最后一个字符（假定是温度单位 "℃" 或 "°"），得到 "25"。
        h = h.left(h.length() - 1);
        high[i] = (int)(h.toDouble());
        tempTotal += high[i];

        // 同理解析低温数据
        l = forecast[i].low.split(" ").at(1);
        l = l.left(l.length() - 1);
        low[i] = (int)(l.toDouble());
    }
    int tempAverage = (int)(tempTotal / 6); // 最高温平均值

    // 算出温度对应坐标
    int pointX[6] = {39, 115, 191, 267, 343, 419}; // 点的X坐标
    int pointHY[6] = {0};
    int pointLY[6] = {0};
    for (int i = 0; i < 6; i++)
    {
        // 以 TEMPERATURE_STARTING_COORDINATE 为基准，如果当前最高温高于平均值，则 (high[i] - tempAverage) 为正，Y 坐标会减小（即点向上移动，因为屏幕坐标系 Y 轴向下为正）。
        pointHY[i] = TEMPERATURE_STARTING_COORDINATE - ((high[i] - tempAverage) * SPAN_INDEX);
        pointLY[i] = TEMPERATURE_STARTING_COORDINATE + ((tempAverage - low[i]) * SPAN_INDEX);
    }


    QPen pen = painter.pen(); //
    pen.setWidth(1);

    // 高温曲线绘制
    painter.save();
    pen.setColor(QColor(255, 170, 0));
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 170, 0)); // 设置填充刷颜色为橙色
    // 在第一个数据点 (pointX[0], pointHY[0]) 处绘制一个小圆点
    painter.drawEllipse(QPoint(pointX[0], pointHY[0]), ORIGIN_SIZE, ORIGIN_SIZE);
    // 在第二个数据点处绘制小圆点。
    painter.drawEllipse(QPoint(pointX[1], pointHY[1]), ORIGIN_SIZE, ORIGIN_SIZE);
    // 用点状虚线连接前两个数据点。
    painter.drawLine(pointX[0], pointHY[0], pointX[1], pointHY[1]);

    pen.setStyle(Qt::SolidLine); // 将画笔改回实线
    pen.setWidth(1);
    painter.setPen(pen);

    // 循环绘制剩余小圆点
    for (int i = 1; i < 5; i++)
    {
        painter.drawEllipse(QPoint(pointX[i+1], pointHY[i+1]), ORIGIN_SIZE, ORIGIN_SIZE);
        painter.drawLine(pointX[i], pointHY[i], pointX[i+1], pointHY[i+1]);
    }
    painter.restore();

    // 低温曲线绘制
    pen.setColor(QColor(0, 255, 255));
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 255, 255));
    painter.drawEllipse(QPoint(pointX[0], pointLY[0]), ORIGIN_SIZE, ORIGIN_SIZE);
    painter.drawEllipse(QPoint(pointX[1], pointLY[1]), ORIGIN_SIZE, ORIGIN_SIZE);
    painter.drawLine(pointX[0], pointLY[0], pointX[1], pointLY[1]);

    pen.setColor(QColor(0, 255, 255));
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for (int i = 1; i < 5; i++)
    {
        painter.drawEllipse(QPoint(pointX[i+1], pointLY[i+1]), ORIGIN_SIZE, ORIGIN_SIZE);
        painter.drawLine(pointX[i], pointLY[i], pointX[i+1], pointLY[i+1]);
    }
}

// 调用软键盘
void Weather::callKeyBoard()
{}

// 鼠标移动事件
void Weather::mouseMoveEvent(QMouseEvent* event)
{
    // event->globalPos() - mPos：表示窗口左上角的位置，窗口应该移动到哪里，才能保证鼠标点始终保持在窗口的相同位置。
    this->move(event->globalPos() - mPos);
}

// 鼠标点击事件
void Weather::mousePressEvent(QMouseEvent* event)
{
    // event->globalPos()获取鼠标的全局坐标
    // this->pos()获取当前窗口左上角的全局坐标
    // mPos保存的是“鼠标点在窗口内的位置” → 即鼠标点击点距离窗口左上角的偏移量。
    mPos = event->globalPos() - this->pos();
}

// 当鼠标右键事件发生时，此函数会被Qt自动调用
void Weather::contextMenuEvent(QContextMenuEvent* menuEvent)
{
    // QCursor::pos() 表示当前鼠标的全局位置（屏幕坐标）
    // exec(QPoint) 表示：以阻塞方式显示菜单
    m_pMenu->exec(QCursor::pos()); // 显示菜单
    // 表示这个事件已经被你处理了，不需要再传递给父类或其他控件
    menuEvent->accept();
}

void Weather::slot_exitApp()
{
    // 退出
    // qApp 是一个宏，指向当前运行的 QApplication 或 QGuiApplication 实例的指针。
    // exit(int code) 方法会终止应用程序的事件循环，并关闭程序。0表示正常退出
    qApp->exit(0);
}
