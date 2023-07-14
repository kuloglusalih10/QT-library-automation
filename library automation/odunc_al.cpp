#include "odunc_al.h"
#include "ui_odunc_al.h"
#include <QDateEdit>

oduncAl::oduncAl(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oduncAl)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    sorgu2 =new QSqlQuery(db);
    listele();

}

oduncAl::~oduncAl()
{
    delete ui;
}

void oduncAl::on_tableView_tum_uyeler_clicked(const QModelIndex &index)
{
    ui->lineEdit_uye_no->setText(model->index(index.row(),0).data().toString());
}

QString stok;

void oduncAl::on_btn_odunc_al_clicked()
{
    if(ui->lineEdit_uye_no->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    if(ui->lineEdit_kitap_no->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }



    sorgu->prepare("select * from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());
    sorgu->exec();

    int sayac = 0;
    while(sorgu->next()){
        sayac++;
    }

    if(sayac>0){
        QMessageBox::critical(this,"Hata","Bu üye bu kitabın bir tanesini zaten ödünç almış. Tekrar ödünç verilemez ","Tamam");
        return;
    }

    sorgu2->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu2->addBindValue(ui->lineEdit_kitap_no->text().toInt());
    sorgu2->exec();

    int oduncAdet = 0;
    while(sorgu2->next()){
        oduncAdet++;
    }

    if(oduncAdet >= stok.toInt()){
        QMessageBox::critical(this,"Hata","Bu Kitabın Stoğu Tükenmiştir, Lütfen Başka Bir Kitap Seçiniz ","Tamam");
        return;
    }

    sorgu->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());
    sorgu->addBindValue(ui->dateEdit->date());


    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    listele();
}



void oduncAl::on_tableView_tum_kitaplar_clicked(const QModelIndex &index)
{
    ui->lineEdit_kitap_no->setText(model1->index(index.row(),0).data().toString());
    stok = model1->index(index.row(),2).data().toString();
}

void oduncAl::listele(){

    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_tum_uyeler->setModel(model);

    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }
    model1 = new QSqlQueryModel();
    model1->setQuery(*sorgu);
    ui->tableView_tum_kitaplar->setModel(model1);

    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_tum_oduc_al->setModel(model2);
}
