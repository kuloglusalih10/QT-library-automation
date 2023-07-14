#include "odunc_teslim.h"
#include "ui_odunc_teslim.h"
#include "QDateEdit"

odunc_teslim::odunc_teslim(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_teslim)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele();

}

odunc_teslim::~odunc_teslim()
{
    delete ui;
}

void odunc_teslim::listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_oduncAl->setModel(model);

    sorgu->prepare("select * from odunc_teslim_eden");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_oduncTeslim->setModel(model2);
}

QDate alma_tarihi;

void odunc_teslim::on_btn_odunc_ver_clicked()
{
    if(ui->lineEdit_kitap_no->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    if(ui->lineEdit_uye_no->text().isEmpty()){
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
        return;
    }

    int borc;
    int days = alma_tarihi.daysTo(ui->dateEdit->date());
    if(days < 0){
        QMessageBox::critical(this,"Hata","Teslim Tarihi Alma Tarihinden önce olamaz","Tamam");
        return;
    }

    if(days <= 15){
        borc = 0;
    }
    else
    {
        borc = (days - 15)+1;
    }

    sorgu->prepare("insert into odunc_teslim_eden(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());
    sorgu->addBindValue(alma_tarihi);
    sorgu->addBindValue(ui->dateEdit->date());
    sorgu->addBindValue(borc);


    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }
    sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->lineEdit_uye_no->text().toInt());
    sorgu->addBindValue(ui->lineEdit_kitap_no->text().toInt());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Tamam");
        return;
    }

    ui->lineEdit_uye_no->setText("");
    ui->lineEdit_kitap_no->setText("");

    listele();



}


void odunc_teslim::on_tableView_oduncAl_clicked(const QModelIndex &index)
{
    ui->lineEdit_uye_no->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_kitap_no->setText(model->index(index.row(),1).data().toString());
    alma_tarihi = model->index(index.row(),2).data().toDate();
}

