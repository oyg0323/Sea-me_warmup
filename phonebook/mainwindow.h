#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contactlist.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_add_clicked();
    void on_remove_clicked();
    void on_search_clicked();
    void on_Save_clicked();
    void on_Load_clicked();
private:
    Ui::MainWindow *ui;
    contactlist contacts_;
    void refreshlist(const QVector<contact> & list);
};
#endif // MAINWINDOW_H
