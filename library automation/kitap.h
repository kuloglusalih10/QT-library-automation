#ifndef KITAP_H
#define KITAP_H
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class kitap;
}

class kitap : public QDialog
{
    Q_OBJECT

public:
    explicit kitap(QSqlDatabase db,QWidget *parent = nullptr);
    ~kitap();
    void listele();

private slots:
    void on_tableView_tum_kitaplar_clicked(const QModelIndex &index);

    void on_pushButton_kaydet_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::kitap *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model_1;
    QSqlQueryModel *model_2;
};

#endif // KITAP_H
