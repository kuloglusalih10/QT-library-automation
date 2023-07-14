#ifndef ODUNC_AL_H
#define ODUNC_AL_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class oduncAl;
}

class oduncAl : public QDialog
{
    Q_OBJECT

public:
    explicit oduncAl(QSqlDatabase db,QWidget *parent = nullptr);
    ~oduncAl();
    void listele();

private slots:
    void on_tableView_tum_uyeler_clicked(const QModelIndex &index);

    void on_tableView_tum_kitaplar_clicked(const QModelIndex &index);

    void on_btn_odunc_al_clicked();

private:
    Ui::oduncAl *ui;
    QSqlQuery *sorgu;
    QSqlQuery *sorgu2;
    QSqlQueryModel *model2;
    QSqlQueryModel *model;
    QSqlQueryModel *model1;
    QSqlQueryModel *model3;
};

#endif // ODUNC_AL_H
