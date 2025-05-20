#ifndef WEATHER_WEATHERUTILS_H
#define WEATHER_WEATHERUTILS_H

#include <QString>

// 该函数用于获取天气图标的资源路径
namespace WeatherUtils {
    // 函数声明
    QString getWeatherIconResourcePath(const QString& weatherDescription, bool isDayTime = true);
}

#endif //WEATHER_WEATHERUTILS_H
