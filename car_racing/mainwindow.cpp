#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "car.h"
#include "car_worker.h"
#include "race_track.h"

#include <QThread>

// .ui 상 레이블의 시작 X 좌표와 결승선 좌표
static constexpr int START_X  = -20;
static constexpr int FINISH_X = 500;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , track_(new racetrack(FINISH_X))   // 결승선 위치를 FINISH_X 로 설정
{
    ui->setupUi(this);

    // 버튼 시그널 연결
    connect(ui->pushButton,   &QPushButton::clicked, this, &MainWindow::startRace);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::resetRace);

    // 자동차 2대 생성(label_2, label_3) 및 시그널 연결
    for (int i = 0; i < 2; ++i) {
        car* c = new car(i, this);
        cars_.append(c);
        connect(c, &car::positionchange,
                this, &MainWindow::onPositionChanged);
    }

    // UI 상 레이블 초기 위치 설정
    ui->label_2->move(START_X, ui->label_2->y());
    ui->label_3->move(START_X, ui->label_3->y());
}

MainWindow::~MainWindow()
{
    // 실행 중인 스레드가 있으면 정리
    resetRace();

    delete track_;
    delete ui;
}

void MainWindow::startRace()
{
    if (!threads_.isEmpty())
        return;  // 이미 레이스 중이면 무시


    for (car* c : cars_) {
        c->resetposition();
        QThread* t = new QThread(this);
        carworker* w = new carworker(c, track_, nullptr);

        c->setspeed(5);
        w->moveToThread(t);

        // 스레드 시작 시 process() 호출
        connect(t, &QThread::started,   w, &carworker::process);
        // 완료 시 onRaceFinished() 호출
        connect(w, &carworker::finished, this, &MainWindow::onRaceFinished);
        // 워커·스레드 자동 정리
        connect(w, &carworker::finished, w, &QObject::deleteLater);
        connect(t, &QThread::finished,  t, &QObject::deleteLater);

        threads_.append(t);
        t->start();
    }
}

void MainWindow::resetRace()
{
    // 모든 스레드 종료
    for (QThread* t : threads_)
        t->quit();
    threads_.clear();

    // 자동차 속도·위치 초기화 (필요시 setspeed 사용)
    for (car* c : cars_){
        c->resetposition();
        c->setspeed(5);
    }
    winnerId_=-1;
    // UI 리셋
    ui->winner->clear();
    ui->label_2->move(START_X, ui->label_2->y());
    ui->label_3->move(START_X, ui->label_3->y());
}

void MainWindow::onPositionChanged(int carId, int pos)
{
    // racetrack::ckeckfinish 에서 전달하는 pos 범위(0~FINISH_X) 기반
    int x = START_X + pos;

    if (carId == 0)
        ui->label_2->move(x, ui->label_2->y());
    else
        ui->label_3->move(x, ui->label_3->y());
}

void MainWindow::onRaceFinished(int carId)
{

    if (winnerId_ == -1) {
        winnerId_ = carId;
        // 상태바 대신 라인에디트에 표시
        if(winnerId_==0){
            ui->winner->setText(QString("Mario win!!!"));
        }
        else{
             ui->winner->setText(QString("Ruigi win!!!"));
        }
        //resetRace();
    }
}
