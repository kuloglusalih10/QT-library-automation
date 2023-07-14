#ifndef UYE_H
#define UYE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class uye;
}

class uye : public QDialog
{
    Q_OBJECT

public:
    explicit uye(QSqlDatabase db,QWidget *parent = nullptr);
    ~uye();
    void listele();

private slots:
    void on_tableView_uyeler_clicked(const QModelIndex &index);

    void on_btn_kayit_clicked();

    void on_btn_sil_clicked();

    void on_btn_guncelle_clicked();

private:
    Ui::uye *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
};

#endif // UYE_H
