#ifndef CONTACT_H
#define CONTACT_H
#pragma once
#include <QString>
#endif // CONTACT_H
class contact{
    public:
    contact(const QString &name="name",
            const QString &phone="number",
            const QString &email="email")
            : name_(name), phone_(phone), email_(email){}
    QString name() const{
        return name_;
    }
    QString phone() const{
        return phone_;
    }
    QString email() const{
        return email_;
    }
    void setname(const QString &name){
        name_=name;
    }
    void setphone(const QString &phone){
        phone_=phone;
    }
    void setemail(const QString &email){
        email_=email;
    }
private:
    QString name_;
    QString phone_;
    QString email_;
};












