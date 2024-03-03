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
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //imagenes y label color
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

    //hides iniciales
    ui->frameE->setVisible(false);
    ui->frameR->setVisible(false);

    //hola
    //HOLAAAAA ¿como estan?
   ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//ahorrando lineas para lo que nos espera :)
void MainWindow::on_btn_entregarM_clicked(){  ui->tabWidget->setCurrentIndex(1); }
void MainWindow::on_btn_revision_clicked(){   ui->tabWidget->setCurrentIndex(2); }
void MainWindow::on_btn_dashboardM_clicked(){ ui->tabWidget->setCurrentIndex(3); }

//cambio de tabs
void MainWindow::on_tabWidget_currentChanged(int index)
{
    QMessageBox::StandardButton cambio;
    if((index==2 || index==3) && loginDocente){
        cambio= QMessageBox::question(this,"Acceso Denegado","Los docentes no tiene acceso\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginDocente=false;
            ui->tabWidget->setCurrentIndex(2);
            ui->tab_3->setEnabled(true);
            limpiarEntrega();
        }else{
            ui->tabWidget->setCurrentIndex(1);
        }
    }else if(index==1 && loginRevision){
        cambio= QMessageBox::question(this,"Acceso Denegado","Ya ha iniciado sesion para otro proceso\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginRevision=false;
            ui->tabWidget->setCurrentIndex(1);
            ui->tab_2->setEnabled(true);
            limpiarRevision();
        }else{
            ui->tabWidget->setCurrentIndex(2);

        }
    }
}

//logica tab2 de entrega silabo
void MainWindow::on_btn_sesion_clicked()
{
    if(ui->le_nameE->text().isEmpty() || ui->le_claveE->text().isEmpty() || ui->le_cuentaE->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        ui->frameE->setVisible(true);
        ui->frameE2->setEnabled(false);
        loginDocente=true;
        ui->tab_3->setEnabled(false);
    }
}

void MainWindow::on_btn_closeE_clicked()
{
    loginDocente=false;
    ui->tab_3->setEnabled(true);
    limpiarEntrega();
    ui->tabWidget->setCurrentIndex(0);
}
void MainWindow::limpiarEntrega()
{
    QStringList items;
    ui->cb_carreraE->clear();
    items<<"...";
    ui->cb_carreraE->addItems(items);
    ui->le_claseE->clear();
    ui->le_codigoE->clear();
    ui->le_pathE->clear();
    if(loginDocente){
        ui->cb_facultadE->setCurrentIndex(0);
        ui->cb_carreraE->setCurrentIndex(0);
    }else{
        ui->le_nameE->clear();
        ui->le_cuentaE->clear();
        ui->le_claveE->clear();
        ui->cb_facultadE->setCurrentIndex(0);
        ui->cb_carreraE->setCurrentIndex(0);
        ui->frameE2->setEnabled(true);
        ui->frameE->setVisible(false);
    }
}

void MainWindow::on_btn_silaboE_clicked()
{
    if(ui->cb_facultadE->currentIndex()==0 || ui->cb_carreraE->currentIndex()==0 || ui->le_claseE->text().isEmpty()|| ui->le_codigoE->text().isEmpty() || ui->le_pathE->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        QMessageBox::information(this,"Enviado","Datos han sido enviados");
        limpiarEntrega();
    }
}
void MainWindow::on_btn_archivoE_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this, "Explorador de Archivos PDF", QDir::homePath(), "XML Files (*.pdf)");
    if (!filePath.isEmpty()) {
        ui->le_pathE->setText(filePath);
    }
}
void MainWindow::on_cb_facultadE_currentIndexChanged(int i)
{
    QStringList items;
    ui->cb_carreraE->clear();
    if(i==1){
        items<<"..."<<"Biomédica"<<"Ciena de datos e inteligencia artificial"<<"Civil"<<"Energía"<<"Industrial y de sistemas"<<"Mecatrónica"<<"Sistemas Computacionales"<<"Telecomunicaciones y electrónica";
        ui->cb_carreraE->addItems(items);
    }else if(i==2){
        items<<"..."<<"Administracion de la hospitalidad y el tursimo"<<"Administración industrial e inteligencia de negocios"<<"Administración industrial y emprendimiento"<<"Industrial y operaciones"<<"Derecho"<<"Finanzas y Economia"<<"Mercadotecnia y negocios internacionales"<<"Relaciones internacionales";
        ui->cb_carreraE->addItems(items);
    }else if(i==3){
        items<<"..."<<"Animación digital y diseño interactivo"<<"Arquitectura"<<"Comunicación audiovisual y publicitaria"<<"Diseño de modas"<<"Diseño Grafico"<<"Gastronomia";
        ui->cb_carreraE->addItems(items);
    }
}

//logica tab3 de revision

void MainWindow::on_Rcb_usuario_currentIndexChanged(int i)
{
    QStringList items;
    ui->Rcb_cambiarE->clear();
    if(i==1 || i==2){//jefe o coordinador
        items<<"..."<<"Cargar silabo (Enviar a IEDD)"<<"Rechazar";
        ui->Rcb_cambiarE->addItems(items);
    }else if(i==3){//en iedd
        items<<"..."<<"Listo para revision 1"<<"Devolver a Academia";
        ui->Rcb_cambiarE->addItems(items);
    }else if(i==4){//consultor
        //revisar en que estado de revision esta
        //si revision es 2 poner true
        if(!revision2){
            items<<"..."<<"Aprobado"<<"Correcion Mayor"<<"Correcion Menor";
        }else{
            items<<"..."<<"Aprobado"<<"Aprobado con condicion";
        }
        ui->Rcb_cambiarE->addItems(items);

    }

}

void MainWindow::on_Rbtn_sesion_clicked()
{
    if(ui->Rle_name->text().isEmpty() || ui->Rle_clave->text().isEmpty() || ui->Rcb_usuario->currentIndex()==0){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        ui->frameR->setVisible(true);
        ui->frameR1->setEnabled(false);
        loginRevision=true;
        ui->tab_2->setEnabled(false);
        pruebitaBotonesTab();
    }
}

void MainWindow::limpiarRevision()
{
    QStringList items;
    ui->Rle_comentario->clear();
    ui->Rle_seleccion->clear();
    ui->Rle_estadoA->clear();
    if(loginRevision){
        ui->Rcb_cambiarE->setCurrentIndex(0);
    }else{
        ui->Rcb_cambiarE->clear();
        items<<"...";
        ui->Rcb_cambiarE->addItems(items);
        ui->Rle_name->clear();
        ui->Rle_clave->clear();
        ui->Rcb_usuario->setCurrentIndex(0);
        ui->Rcb_cambiarE->setCurrentIndex(0);
        ui->frameR->setVisible(false);
        ui->frameR1->setEnabled(true);
    }
}

void MainWindow::on_Rbtn_cerrar_clicked()
{
    loginRevision=false;
    ui->tab_2->setEnabled(true);
    limpiarRevision();
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_Rbtn_cambiar_clicked()
{
    if( ui->Rle_estadoA->text().isEmpty() || ui->Rle_seleccion->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","No ha seleccionado que editar");
    }else if(ui->Rle_comentario->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","No olvide comentar");
    }else if(ui->Rcb_cambiarE->currentIndex()==0){
        QMessageBox::warning(this,"Datos no congruetes","No ha seleccionado estado a cambiar");
    }else{
        QMessageBox::information(this,"Datos congruetes","Datos han sido actualizados");
        limpiarRevision();
    }

}

void MainWindow::pruebitaBotonesTab()
{
    ui->RTW_revision->clear();
    ui->RTW_revision->setColumnCount(4);
    ui->RTW_revision->setRowCount(4);
    ui->RTW_revision->setHorizontalHeaderLabels(QStringList() << "dato prueba"<<"estado prueba"<<"documento"<<"Cambiar Estado");

    for (int f = 0; f < 5; f++) {
        ui->RTW_revision->setItem(f, 0, new QTableWidgetItem(QString::number(f)));
        ui->RTW_revision->setItem(f, 1, new QTableWidgetItem(QString::number(f) +QString::fromStdString(" feliz ") +QString::number(f+1)));
        ui->RTW_revision->setItem(f, 2, new QTableWidgetItem(QString::fromStdString("VER")));
        ui->RTW_revision->setItem(f, 3, new QTableWidgetItem(QString::fromStdString("EDITAR")));

    }
}

void MainWindow::on_RTW_revision_cellClicked(int row, int column)
{
    if(column==3){
        QString dato = ui->RTW_revision->item(row, 0)->text();
        ui->Rle_seleccion->setText(dato);
        QString estado = ui->RTW_revision->item(row, 1)->text();
        ui->Rle_estadoA->setText(estado);
        QMessageBox::information(this, "Informacion seleccionada", "Dato: "+dato+"\nEstado: "+estado);
    }else if(column ==2){
//abrir docx

    }

}

