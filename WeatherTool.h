#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <map>
#include <QFile>

class WeatherTool
{

public:
    WeatherTool() {
        // 获取城市编码文件路径
        QString fileName = QCoreApplication::applicationDirPath();
        QJsonParseError err;
        fileName += "/citycode-2019-08-23.json";
        QFile file(fileName);

        // 打开文件
        file.open(QIODevice::ReadOnly | QIODevice::Text); // 以只读和文本方式读取
        //  读取文件的全部内容到一个 QByteArray 对象中
        QByteArray json = file.readAll();
        file.close(); // 关闭文件

        // 从 QByteArray (json) 解析JSON数据,并将解析错误信息（如果有）存储到err对象中。
        QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &err);
        //  JSON 文件的顶层结构是一个数组。将 QJsonDocument 转换（或获取）为一个 QJsonArray。
        QJsonArray citys = jsonDoc.array();

        for(int i = 0; i < citys.size(); i++)
        {
            //
            QString code = citys.at(i).toObject().value("city_code").toString();
            QString city = citys.at(i).toObject().value("city_name").toString();
            if(code.size() > 0)
            {
                // 哈希表中存储城市名称和邮政编码键值对
                m_mapCity2Code.insert(std::pair<QString, QString>(city, code));
            }
        }
    }

    // 通过城市名获取邮政编码
    QString operator[](const QString& city)
    {
        std::map<QString, QString>::iterator it = m_mapCity2Code.find(city);
        if(it == m_mapCity2Code.end())
        {
            it = m_mapCity2Code.find(city+u8"市 ");
        }
        if(it != m_mapCity2Code.end())
        {
            return it->second;
        }
        return "000000000";
    }

private:
    std::map<QString, QString> m_mapCity2Code;
};
#endif  // WEATHERTOOL_H
