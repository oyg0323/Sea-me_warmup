#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    contacts_.loadFromFile("contacts.json");
    refreshlist(contacts_.all());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::refreshlist(const QVector<contact> &list)
{
    ui->listWidget->clear();
    for (const auto &c : list) {

        ui->listWidget->addItem(c.name() + " | " + c.phone()+" | "+c.email());
    }
}
// “추가” 버튼 클릭 시
void MainWindow::on_add_clicked()
{
    // 1) QLineEdit에서 입력 읽기
    contact c(
        ui->nameEdit->text(),
        ui->phoneEdit->text(),
        ui->emailEdit->text()
        );

    // 2) 모델에 새 연락처 추가
   contacts_.add(c);

    // 3) 화면 갱신
    refreshlist(contacts_.all());

    // 4) 입력창 초기화 및 포커스 이동
    ui->nameEdit->clear();
    ui->phoneEdit->clear();
    ui->emailEdit->clear();
    ui->nameEdit->setFocus();
}

// “삭제” 버튼 클릭 시
void MainWindow::on_remove_clicked()
{
    int idx = ui->listWidget->currentRow();
    if (idx < 0) return;  // 선택된 항목 없으면 무시

    contacts_.remove(idx);
    refreshlist(contacts_.all());
}

// “검색” 버튼 클릭 시
void MainWindow::on_search_clicked()
{
    // 이름 입력창의 텍스트를 검색어로 사용
    auto results = contacts_.search(ui->searchEdit->text());
    refreshlist(results);
}
