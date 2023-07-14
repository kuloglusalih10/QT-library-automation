#include "kitap.h"
#include "ui_kitap.h"

kitap::kitap(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitap)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele();
}


kitap::~kitap()
{
    delete ui;
}

void kitap::listele(){
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_tum_kitaplar->setModel(model);
}


void kitap::on_pushButton_sil_clicked()
{
    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());

    qDebug() << ui->lineEdit_kitap_no->text().toInt();

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    int sayac = 0;
    while(sorgu->next()){
        sayac++;
    }

    if(sayac>0){
        QMessageBox::critical(this,"Hata","Bu kitap silinemez. Bu kitap bir üyeye ödünç verilmiştir.","Tamam");
        return;
    }
    else{
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());

        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        }
    }

    ui->lineEdit_kitap_ad->setText("");
    ui->lineEdit_kitap_no->setText("");
    ui->lineEdit_stok->setText("");

    listele();
}


void kitap::on_pushButton_kaydet_clicked()
{

    if(ui->lineEdit_kitap_ad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }
    if(ui->lineEdit_stok->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }



    sorgu->prepare("insert into kitap(kitap_ad,kitap_sayısı) values(?,?)");
    sorgu->addBindValue(ui->lineEdit_kitap_ad->text());
    sorgu->addBindValue(ui->lineEdit_stok->text().toInt());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    ui->lineEdit_kitap_ad->setText("");
    ui->lineEdit_kitap_no->setText("");
    ui->lineEdit_stok->setText("");

    listele();
}


void kitap::on_pushButton_guncelle_clicked()
{


    if(ui->lineEdit_kitap_ad->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }
    if(ui->lineEdit_stok->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    sorgu->prepare("update kitap set kitap_ad=?,kitap_sayısı=?  where kitap_no=?");
    sorgu->addBindValue(ui->lineEdit_kitap_ad->text());
    sorgu->addBindValue(ui->lineEdit_stok->text().toInt());
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());

    qDebug() << ui->lineEdit_stok->text().toInt();
    qDebug() << ui->lineEdit_kitap_ad->text();
    qDebug() << ui->lineEdit_kitap_no->text().toInt();

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
    }

    listele();
}


void kitap::on_tableView_tum_kitaplar_clicked(const QModelIndex &index)
{
    ui->lineEdit_stok->setText(model->index(index.row(),2).data().toString());
    ui->lineEdit_kitap_ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_kitap_no->setText(model->index(index.row(),0).data().toString());

    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(model->index(index.row(),0).data().toString());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    model_1 = new QSqlQueryModel();
    model_1->setQuery(*sorgu);
    ui->tableView_odunc_alma_durum->setModel(model_1);

    sorgu->prepare("select * from odunc_teslim_eden where kitap_no=?");
    sorgu->addBindValue(model->index(index.row(),0).data().toString());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    model_2 = new QSqlQueryModel();
    model_2->setQuery(*sorgu);
    ui->tableView_dahaOnceOduncAlma->setModel(model_2);
}
