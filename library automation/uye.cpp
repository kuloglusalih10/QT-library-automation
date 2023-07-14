#include "uye.h"
#include "ui_uye.h"


uye::uye(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uye)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele();
}

void uye::listele(){
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_uyeler->setModel(model);
}

uye::~uye()
{
    delete ui;
}

void uye::on_tableView_uyeler_clicked(const QModelIndex &index)
{
    ui->lineEdit_uye_no->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_uye_ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_uye_soyad->setText(model->index(index.row(),2).data().toString());
}


void uye::on_btn_kayit_clicked()
{
    if(ui->lineEdit_uye_ad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Okay");
        return;
    }

    if(ui->lineEdit_uye_soyad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
    sorgu->addBindValue(ui->lineEdit_uye_ad->text());
    sorgu->addBindValue(ui->lineEdit_uye_soyad->text());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    ui->lineEdit_uye_no->setText("");
    ui->lineEdit_uye_ad->setText("");
    ui->lineEdit_uye_soyad->setText("");

    listele();
}

void uye::on_btn_guncelle_clicked()
{
    if(ui->lineEdit_uye_ad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    if(ui->lineEdit_uye_soyad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    sorgu->prepare("update uye set uye_ad=?,uye_soyad=? where uye_no=?");
    sorgu->addBindValue(ui->lineEdit_uye_ad->text());
    sorgu->addBindValue(ui->lineEdit_uye_soyad->text());
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());


    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }


    listele();
}

void uye::on_btn_sil_clicked()
{
    sorgu->prepare("select * from odunc_alinan where uye_no=?");
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    int sayac = 0;
    while(sorgu->next()){
        sayac++;
    }

    if(sayac>0){
        QMessageBox::critical(this,"Hata","Bu Üye silinemez. Teslim Etmediği Kitaplar mevcut","Tamam");
        return;
    }
    else{
        sorgu->prepare("delete from uye where uye_no=?");
        sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());

        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        }
    }


    ui->lineEdit_uye_no->setText("");
    ui->lineEdit_uye_ad->setText("");
    ui->lineEdit_uye_soyad->setText("");

    listele();
}
