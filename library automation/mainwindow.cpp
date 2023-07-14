#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uye.h"
#include "kitap.h"
#include "odunc_al.h"
#include "odunc_teslim.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Gorsel/ikinciOdev/odev2.db");
    if(!db.open())
    {
        ui->statusBar->showMessage("Veri tabanına bağlanılamadı.");
    }

    else
    {
         ui->statusBar->showMessage("Veri tabanına bağlanıldı");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_odunc_teslim_clicked()
{
    odunc_teslim *oduncT = new odunc_teslim(db);
    oduncT->show();
}


void MainWindow::on_btn_uye_clicked()
{
    uye *uye_ = new uye(db);
    uye_->show();
}


void MainWindow::on_btn_kitap_clicked()
{
    kitap *kitap_ = new kitap(db);
    kitap_->show();
}


void MainWindow::on_btb_odunc_al_clicked()
{
    oduncAl *odunc_al = new oduncAl(db);
    odunc_al->show();
}

