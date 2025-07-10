#ifndef CAR_H
#define CAR_H
#include <QObject>
// CAR_H
class car : public QObject {
    Q_OBJECT
public:
    explicit car(int id, QObject* parent = nullptr)
        : QObject(parent)
        ,id_(id)
        ,position_(0)
        ,speed_(5)

    {}
    int position()const{
        return position_;
    }
    void setspeed(int speed) {
        speed_=speed;
    }
    void resetposition(){
        position_=0;
    }
    int getId(){
        return id_;
    }
public slots:
    void move(){
        position_=position_+speed_;
        emit positionchange(id_,position_);
    }
signals:
    void positionchange(int carid,int newposition);
private:
    int id_;
    int position_;
    int speed_;

};
#endif
