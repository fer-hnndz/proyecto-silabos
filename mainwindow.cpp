#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <istream>
#include <iostream>
#include <string>
#include <sstream>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage menu(":/prefix/principal proyecto.png");
    ui->lbl_pngMenu->setPixmap(QPixmap::fromImage(menu));
    ui->lbl_b1M->setStyleSheet("background-color: #062458;");
    ui->lbl_b2M->setStyleSheet("background-color: #062458;");
    QImage entrega(":/prefix/1.png");
    ui->lbl_pngE->setPixmap(QPixmap::fromImage(entrega));
    QImage revision(":/prefix/2.png");
    ui->lbl_pngR->setPixmap(QPixmap::fromImage(revision));
    QImage dash(":/prefix/3.png");
    ui->lbl_pngD->setPixmap(QPixmap::fromImage(dash));
    //hola
    //HOLAAAAA ¿como estan?
   ui->frameE->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//ahorrando lineas para lo que nos espera :)
void MainWindow::on_btn_entregarM_clicked(){
    ui->tabWidget->setCurrentIndex(1);
}
void MainWindow::on_btn_revision_clicked(){ ui->tabWidget->setCurrentIndex(2); }
void MainWindow::on_btn_dashboardM_clicked(){ ui->tabWidget->setCurrentIndex(3);}




void MainWindow::on_btn_sesion_clicked()
{
    ui->frameE->setVisible(true);
    ui->frameE2->setEnabled(false);
    loginDocente=true;
    ui->tab_3->setEnabled(false);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    QMessageBox::StandardButton cambio;
    if(index==2 && loginDocente){
        cambio= QMessageBox::question(this,"Acceso Denegado","Los docentes no tiene acceso\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginDocente=false;
            ui->tabWidget->setCurrentIndex(2);
            ui->tab_3->setEnabled(true);
        }else{
            ui->tabWidget->setCurrentIndex(1);
        }
    }else if(index==1 && loginRevision){
        cambio= QMessageBox::question(this,"Acceso Denegado","Ya ha iniciado sesion para otro proceso\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginRevision=false;
            ui->tabWidget->setCurrentIndex(1);
            ui->tab_2->setEnabled(true);
        }else{
            ui->tabWidget->setCurrentIndex(1);

        }
    }
}


void MainWindow::on_cb_facultadE_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::limpiarEntrega()
{
    if(loginDocente){
        ui->cb_facultadE->setCurrentIndex(0);
        ui->cb_carreraE->setCurrentIndex(0);
        ui->le_claseE->clear();
        ui->le_codigoE->clear();
        ui->le_pathE->clear();
    }else{
        ui->le_nameE->clear();
        ui->le_cuentaE->clear();
        ui->le_claveE->clear();
        ui->cb_facultadE->setCurrentIndex(0);
        ui->cb_carreraE->setCurrentIndex(0);
        ui->le_claseE->clear();
        ui->le_codigoE->clear();
        ui->le_pathE->clear();
    }
}

void MainWindow::on_btn_silaboE_clicked()
{
    //se cambiara?
    if(ui->cb_facultadE->currentIndex()==0 || ui->cb_carreraE->currentIndex()==0 || ui->le_claseE->text().isEmpty()|| ui->le_codigoE->text().isEmpty() || ui->le_pathE->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        QMessageBox::information(this,"Enviado","Datos han sido enviados");
        ui->cb_facultadE->setCurrentIndex(0);
        ui->cb_carreraE->setCurrentIndex(0);
        ui->le_claseE->clear();
        ui->le_codigoE->clear();
        ui->le_pathE->clear();
    }


}

void MainWindow::on_btn_archivoE_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "XML Files (*.pdf)");
    if (!filePath.isEmpty()) {
        ui->le_pathE->setText(filePath);
    }
}

