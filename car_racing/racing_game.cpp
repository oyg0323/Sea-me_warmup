//#include "racing_game.h"
#include "MainWindow.h"

#include "car.h"
#include "car_worker.h"
#include "race_track.h"

#include <QThread>

// 트랙 좌표 정의
constexpr int START_X  = -20;   // .ui 상 label_2, label_3 초기 x
constexpr int FINISH_X = 380;   // 결승선(대략 배경 라벨 오른쪽)

racing_game::racing_game(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , track_(new racetrack(FINISH_X))
{
    ui->setupUi(this);

    // 1) 버튼 연결
    connect(ui->pushButton,   &QPushButton::clicked, this, &racing_game::startRace); // start
    connect(ui->pushButton_2, &QPushButton::clicked, this, &racing_game::resetRace); // reset

    // 2) 자동차 2대 생성 (label_2, label_3)
    for (int i = 0; i < 2; ++i) {
        car* c = new car(i, this);
        cars_.append(c);
        connect(c, &car::positionchange,
                this, &racing_game::onPositionChanged);
    }
    initCarsUi();
}

racing_game::~racing_game() {
    stopThreads();
    delete track_;
    delete ui;
}

/*------------------------------  레이스 시작  ------------------------------*/
void racing_game::startRace()
{
    if (!threads_.isEmpty()) return;        // 이미 진행 중

    for (car* c : cars_) {
        QThread* t = new QThread(this);
        carworker* w = new carworker(c, track_, this);
        w->moveToThread(t);

        connect(t, &QThread::started,   w, &carworker::process);
        connect(w, &carworker::finished, this, &racing_game::onRaceFinished);
        connect(w, &carworker::finished, w, &QObject::deleteLater);
        connect(t, &QThread::finished,  t, &QObject::deleteLater);

        threads_.append(t);
        t->start();
    }
}

/*------------------------------  레이스 리셋  ------------------------------*/
void racing_game::resetRace()
{
    stopThreads();      // 스레드 종료
    for (car* c : cars_) c->setspeed(5);      // 속도 초기화(원하면)
    initCarsUi();       // 레이블 위치 원점
    ui->statusbar->clearMessage();
}

/*---------------------  자동차 위치 변경 → 화면 갱신  ----------------------*/
void racing_game::onPositionChanged(int carId, int pos)
{
    // pos 0~FINISH_X 범위 → 레이블 x 좌표
    int x = START_X + pos;
    if (carId == 0) ui->label_2->move(x, ui->label_2->y());
    else            ui->label_3->move(x, ui->label_3->y());
}

/*--------------------------  레이스 완료 알림  -----------------------------*/
void racing_game::onRaceFinished(int /*finalPos*/)
{
    ui->statusbar->showMessage("Race Finished!");
    stopThreads();      // 모든 스레드 정지
}

/*--------------------------  보조 메서드  ---------------------------------*/
void racing_game::initCarsUi()
{
    ui->label_2->move(START_X, 80);   // label_2 초기 y = 80
    ui->label_3->move(START_X, 140);  // label_3 초기 y = 140
}

void racing_game::stopThreads()
{
    for (QThread* t : threads_) t->quit();
    threads_.clear();
}
