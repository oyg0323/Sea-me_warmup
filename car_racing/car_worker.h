#ifndef CAR_WORKER_H
#define CAR_WORKER_H
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QThread>
#include <cstdlib>
#include <ctime>
#include "car.h"
#include "race_track.h"
#endif // CAR_WORKER_H

class carworker : public QObject{
    Q_OBJECT
public:
    explicit carworker(car* car, racetrack* track, QObject* parent = nullptr)
        : QObject(parent)
        ,car_(car)
        ,track_(track){}
public slots:
    void process(){
        while(!track_->ckeckfinish(car_->position())){{
                 QMutexLocker lock(&mutex_);
                int random = rand()%10+1;
                car_->setspeed(random);

            car_->move();
        }
        QThread::msleep(50);
    }
        emit finished(car_->getId());
    }
signals:
    void finished(int carId);
private:
    car* car_;
    racetrack* track_;
    QMutex mutex_;
};
