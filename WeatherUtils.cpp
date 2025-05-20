#include "WeatherUtils.h"
#include <QMap>
#include <QDebug> // For qWarning
#include <QReadWriteLock> // For thread-safe initialization if needed in multi-threaded context

// 使用匿名命名空间来限制这些静态变量和辅助函数的链接范围
namespace {

// 定义映射表为静态变量，它们只会被初始化一次
    static QMap<QString, QString> s_dayIconAliasMap;
    static QMap<QString, QString> s_nightIconAliasMap;
    static bool s_mapsInitialized = false;
    static QReadWriteLock s_mapLock; // 用于多线程环境下的安全初始化

    void initializeWeatherIconMaps() {
        // 使用写锁确保只有一个线程进行初始化
        QWriteLocker locker(&s_mapLock);
        if (s_mapsInitialized) {
            return;
        }

        // --- Day Icons Aliases (这些是你在 .qrc 文件中定义的 alias) ---
        s_dayIconAliasMap.insert(QString::fromUtf8("暴雪"),                  "day_baoxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("暴雨"),                  "day_baoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("暴雨到大暴雨"),          "day_baoyu_dao_dabaoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("大暴雨"),                "day_dabaoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("大暴雨到特大暴雨"),      "day_dabaoyu_dao_tedabaoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("大到暴雪"),            "day_da_dao_baoxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("大到暴雨"),            "day_da_dao_baoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("大雪"),                  "day_daxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("大雨"),                  "day_dayu");
        s_dayIconAliasMap.insert(QString::fromUtf8("冻雨"),                  "day_dongyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("多云"),                  "day_duoyun");
        s_dayIconAliasMap.insert(QString::fromUtf8("浮沉"),                  "day_fuchen");
        s_dayIconAliasMap.insert(QString::fromUtf8("雷阵雨"),                "day_leizhenyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("雷阵雨伴有冰雹"),      "day_leizhenyu_ban_bingbao");
        s_dayIconAliasMap.insert(QString::fromUtf8("霾"),                    "day_mai");
        s_dayIconAliasMap.insert(QString::fromUtf8("强沙尘暴"),            "day_qiangshachenbao");
        s_dayIconAliasMap.insert(QString::fromUtf8("晴"),                    "day_qing");
        s_dayIconAliasMap.insert(QString::fromUtf8("沙尘暴"),                "day_shachenbao");
        s_dayIconAliasMap.insert(QString::fromUtf8("特大暴雨"),            "day_tedabaoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("雾"),                    "day_wu");
        s_dayIconAliasMap.insert(QString::fromUtf8("小到中雪"),            "day_xiao_dao_zhongxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("小到中雨"),            "day_xiao_dao_zhongyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("小雪"),                  "day_xiaoxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("小雨"),                  "day_xiaoyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("雪"),                    "day_xue");
        s_dayIconAliasMap.insert(QString::fromUtf8("扬沙"),                  "day_yangsha");
        s_dayIconAliasMap.insert(QString::fromUtf8("阴"),                    "day_yin");
        s_dayIconAliasMap.insert(QString::fromUtf8("雨"),                    "day_yu");
        s_dayIconAliasMap.insert(QString::fromUtf8("雨夹雪"),                "day_yujiaxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("阵雪"),                  "day_zhenxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("阵雨"),                  "day_zhenyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("中到大雪"),            "day_zhong_dao_daxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("中到大雨"),            "day_zhong_dao_dayu");
        s_dayIconAliasMap.insert(QString::fromUtf8("中雪"),                  "day_zhongxue");
        s_dayIconAliasMap.insert(QString::fromUtf8("中雨"),                  "day_zhongyu");
        s_dayIconAliasMap.insert(QString::fromUtf8("undefined"),           "day_undefined"); // Default

        // --- Night Icons Aliases ---
        s_nightIconAliasMap.insert(QString::fromUtf8("暴雪"),                 "night_baoxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("暴雨"),                 "night_baoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("暴雨到大暴雨"),         "night_baoyu_dao_dabaoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("大暴雨"),               "night_dabaoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("大暴雨到特大暴雨"),     "night_dabaoyu_dao_tedabaoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("大到暴雪"),           "night_da_dao_baoxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("大到暴雨"),           "night_da_dao_baoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("大雪"),                 "night_daxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("大雨"),                 "night_dayu");
        s_nightIconAliasMap.insert(QString::fromUtf8("冻雨"),                 "night_dongyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("多云"),                 "night_duoyun");
        s_nightIconAliasMap.insert(QString::fromUtf8("浮沉"),                 "night_fuchen");
        s_nightIconAliasMap.insert(QString::fromUtf8("雷阵雨"),               "night_leizhenyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("雷阵雨伴有冰雹"),     "night_leizhenyu_ban_bingbao");
        s_nightIconAliasMap.insert(QString::fromUtf8("霾"),                   "night_mai");
        s_nightIconAliasMap.insert(QString::fromUtf8("强沙尘暴"),           "night_qiangshachenbao");
        s_nightIconAliasMap.insert(QString::fromUtf8("晴"),                   "night_qing");
        s_nightIconAliasMap.insert(QString::fromUtf8("沙尘暴"),               "night_shachenbao");
        s_nightIconAliasMap.insert(QString::fromUtf8("特大暴雨"),           "night_tedabaoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("雾"),                   "night_wu");
        s_nightIconAliasMap.insert(QString::fromUtf8("小到中雪"),           "night_xiao_dao_zhongxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("小到中雨"),           "night_xiao_dao_zhongyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("小雪"),                 "night_xiaoxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("小雨"),                 "night_xiaoyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("雪"),                   "night_xue");
        s_nightIconAliasMap.insert(QString::fromUtf8("扬沙"),                 "night_yangsha");
        s_nightIconAliasMap.insert(QString::fromUtf8("阴"),                   "night_yin");
        s_nightIconAliasMap.insert(QString::fromUtf8("雨"),                   "night_yu");
        s_nightIconAliasMap.insert(QString::fromUtf8("雨夹雪"),               "night_yujiaxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("阵雪"),                 "night_zhenxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("阵雨"),                 "night_zhenyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("中到大雪"),           "night_zhong_dao_daxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("中到大雨"),           "night_zhong_dao_dayu");
        s_nightIconAliasMap.insert(QString::fromUtf8("中雪"),                 "night_zhongxue");
        s_nightIconAliasMap.insert(QString::fromUtf8("中雨"),                 "night_zhongyu");
        s_nightIconAliasMap.insert(QString::fromUtf8("undefined"),          "night_undefined"); // Default

        s_mapsInitialized = true;
    }

} // end anonymous namespace

QString WeatherUtils::getWeatherIconResourcePath(const QString& weatherDescription, bool isDayTime) {
    // 确保映射表只在第一次调用时初始化
    // 对于多线程，需要更安全的初始化方式，例如 std::call_once 或 QReadWriteLock
    if (!s_mapsInitialized) {
        initializeWeatherIconMaps();
    }

    QString iconAlias;
    // 使用读锁来安全地访问映射表
    QReadLocker locker(&s_mapLock);

    if (isDayTime) {
        iconAlias = s_dayIconAliasMap.value(weatherDescription, s_dayIconAliasMap.value(QString::fromUtf8("undefined")));
    } else {
        iconAlias = s_nightIconAliasMap.value(weatherDescription, s_nightIconAliasMap.value(QString::fromUtf8("undefined")));
    }
    locker.unlock(); // 及时释放锁

    if (iconAlias.isEmpty()) {
        // This case should ideally not be reached if "undefined" is always in the map
        // and value() with a default is used correctly.
        qWarning() << "Icon alias is empty for weather:" << weatherDescription << (isDayTime ? "(day)" : "(night)");
        // Fallback to a hardcoded undefined icon path if alias somehow becomes empty
        return isDayTime ? QStringLiteral(":/weatherIcons/day_undefined") : QStringLiteral(":/weatherIcons/night_undefined");
    }

    // 假设你的 .qrc 文件中的顶层 prefix 是 "/weatherIcons"
    return QStringLiteral(":/weatherIcons/") + iconAlias;
}