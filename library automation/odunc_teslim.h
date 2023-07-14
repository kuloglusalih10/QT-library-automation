#ifndef ODUNC_TESLIM_H
#define ODUNC_TESLIM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class odunc_teslim;
}

class odunc_teslim : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_teslim();
    void listele();

private slots:
    void on_btn_odunc_ver_clicked();

    void on_tableView_oduncAl_clicked(const QModelIndex &index);

private:
    Ui::odunc_teslim *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
};

#endif // ODUNC_TESLIM_H
