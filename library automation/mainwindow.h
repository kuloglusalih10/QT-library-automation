#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_odunc_teslim_clicked();

    void on_btn_uye_clicked();

    void on_btn_kitap_clicked();

    void on_btb_odunc_al_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};
#endif
