#ifndef CONTACTLIST_H
#define CONTACTLIST_H
#pragma once
#include "contact.h"
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonValue>
#endif // CONTACTLIST_H
class contactlist{
public:
    void add(const contact&c){
        list_.append(c);
    }
    void remove(int idx){
        if(idx>=0 && idx<list_.size()){
            list_.remove(idx);
        }
    }

    QVector<contact> all() const{
        return list_;
    }
    QVector<contact> search(const QString &term)const{
        QVector<contact> results;
        for(const auto&c : list_){
            if(c.name().contains(term, Qt::CaseInsensitive))
                results.append(c);
        }
        return results;
    }
    // JSON 파일로 저장
    bool saveToFile(const QString &path) const {
        QJsonArray arr;
        for (const auto &c : list_) {
            QJsonObject obj{
                {"name",  c.name()},
                {"phone", c.phone()},
                {"email", c.email()}
            };
            arr.append(QJsonValue(obj));   // ← QJsonValue로 감싸서 append
        }
        QJsonDocument doc(arr);
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)) return true;
        file.write(doc.toJson());
        return file.close(),true;
        }
    // contactlist.h (헤더 안)
    bool loadFromFile(const QString &path) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) return false;
        auto arr = QJsonDocument::fromJson(file.readAll()).array();
        list_.clear();
        for (auto v : arr) {
            auto obj = v.toObject();
            list_.append(contact(
                obj["name"].toString(),
                obj["phone"].toString(),
                obj["email"].toString()));
        }
        return file.close(),true;
    }


private:
    QVector<contact> list_;
};
