// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class car;
class carworker;
class racetrack;
class QThread;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startRace();                       // Start 버튼 슬롯
    void resetRace();                       // Reset 버튼 슬롯
    void onPositionChanged(int carId, int pos);
    void onRaceFinished(int carId);

private:
    Ui::MainWindow *ui;

    racetrack*       track_;                // 트랙 정보
    QList<car*>      cars_;                 // car 객체들
    QList<QThread*>  threads_;              // 실행 중인 스레드들
    int winnerId_{-1};
};

#endif // MAINWINDOW_H
