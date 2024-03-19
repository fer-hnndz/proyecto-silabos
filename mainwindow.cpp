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
#include <fstream>
#include <iostream>
#include <sstream>
using std::ofstream;
using std::ios;
using std::string;
using std::ios;

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
    ui->frameB->setVisible(false);



     connect(ui->RTW_revision, &QTableWidget::cellDoubleClicked, this, &MainWindow::on_RTW_revision_cellClicked);

   listaUsuarios.cargarUsuarios();
   this->arbolSilabo->extraerArbol(this->arbolSilabo);

}

MainWindow::~MainWindow()
{
    listaUsuarios.guardarUsuarios(listaUsuarios);
    this->arbolSilabo->guardar();
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
            ui->tabWidget->setCurrentIndex(index);
            ui->tab_3->setEnabled(true);
            ui->tab_4->setEnabled(true);
            limpiarEntrega();
        }else{
            ui->tabWidget->setCurrentIndex(1);
        }
    }else if((index==1 || index==3 )&& loginRevision){
        cambio= QMessageBox::question(this,"Acceso Denegado","Ya ha iniciado sesion para otro proceso\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginRevision=false;
            ui->tabWidget->setCurrentIndex(index);
            ui->tab_2->setEnabled(true);
            ui->tab_4->setEnabled(true);
            limpiarRevision();
        }else{
            ui->tabWidget->setCurrentIndex(2);

        }
    }else if((index==1 || index==2) && loginBoard){
        cambio= QMessageBox::question(this,"Acceso Denegado","Ya ha iniciado sesion solo para visualizar\n¿Desea cerrar sesión? ",QMessageBox::Yes | QMessageBox::No);
        if(cambio==QMessageBox::Yes){
            loginBoard=false;
            ui->tabWidget->setCurrentIndex(index);
            ui->tab_3->setEnabled(true);
            ui->tab_2->setEnabled(true);
            limpiarBoard();
        }else{
            ui->tabWidget->setCurrentIndex(3);

        }
    }
}

//logica tab2 de entrega silabo
void MainWindow::on_btn_sesion_clicked()
{
    if(ui->le_nameE->text().isEmpty() || ui->le_claveE->text().isEmpty() || ui->le_cuentaE->text().isEmpty()){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        if(ui->le_claveE->text().toStdString()==claveDocente){
            ui->frameE->setVisible(true);
            ui->frameE2->setEnabled(false);
            loginDocente=true;
            ui->tab_3->setEnabled(false);
            ui->tab_4->setEnabled(false);
        }else{
            QMessageBox::warning(this,"Datos no congruetes","Clave incorrecta");
        }

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
        cantSilabos++;
        //datos usuario
        string name=ui->le_nameE->text().toStdString();
        string tipoUsuario="DOCENTE";
        string numCuenta=ui->le_cuentaE->text().toStdString();

        string codigoClase=ui->le_codigoE->text().toStdString();
        Usuario nuevo(name, numCuenta, codigoClase);
        listaUsuarios.InsertarFin(nuevo);
        listaUsuarios.guardarUsuarios(listaUsuarios);

        //datos del silabo que SUBE ESE USUARIO
        string facultad=ui->cb_facultadE->currentText().toStdString();

        string carrera=ui->cb_carreraE->currentText().toStdString();


        string clase=ui->le_claseE->text().toStdString();
        QString path=ui->le_pathE->text();
        string comentario="";

    //    Estado estado=Prerevision;
        //poner numero de revisiones en 0
        //id seria cantidad en lista mas uno
        // Silabo(string facultad, std::vector<Ingenieria> carreras, string nombre, string codigoClase, QString ruta, Estado estado, string observacion, int id, int numRevisiones)
        Silabo* silaboEjemplo = new Silabo(facultad,carrera,numCuenta,codigoClase,path,"Prerevision","h",cantSilabos,0);

        this->arbolSilabo->add(silaboEjemplo);
        this->arbolSilabo->guardar();


        limpiarEntrega();
    }
}
void MainWindow::on_btn_archivoE_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Explorador de Archivos PDF", QDir::homePath(), "PDF Files (*.pdf)");
        if (!filePath.isEmpty()) {
            pdfFilePaths.append(filePath);
            // Mostrar la ruta en el cuadro de texto
            ui->le_pathE->setText(filePath);
        }
}
void MainWindow::on_cb_facultadE_currentIndexChanged(int i)
{
    QStringList items;
    ui->cb_carreraE->clear();
    if(i==1){
        items<<"..."<<"Biomedica"<<"Ciencia de datos e inteligencia artificial"<<"Civil"<<"Energia"<<"Industrial y de sistemas"<<"Mecatronica"<<"Sistemas Computacionales"<<"Telecomunicaciones y electronica";
        ui->cb_carreraE->addItems(items);
    }else if(i==2){
        items<<"..."<<"Administracion de la hospitalidad y el tursimo"<<"Administracion industrial e inteligencia de negocios"<<"Administracion industrial y emprendimiento"<<"Industrial y operaciones"<<"Derecho"<<"Finanzas y Economia"<<"Mercadotecnia y negocios internacionales"<<"Relaciones internacionales";
        ui->cb_carreraE->addItems(items);
    }else if(i==3){
        items<<"..."<<"Animacion digital y diseño interactivo"<<"Arquitectura"<<"Comunicacion audiovisual y publicitaria"<<"Diseno de modas"<<"Diseno Grafico"<<"Gastronomia";
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
        //this->arbolSilabo->extraer();
        if((ui->Rcb_usuario->currentIndex()==1 && ui->Rle_clave->text().toStdString()==claveJefe)        ||
           (ui->Rcb_usuario->currentIndex()==2 && ui->Rle_clave->text().toStdString()==claveCoordinador) ||
           (ui->Rcb_usuario->currentIndex()==3 && ui->Rle_clave->text().toStdString()==claveIEDD)        ||
           (ui->Rcb_usuario->currentIndex()==4 && ui->Rle_clave->text().toStdString()==claveConsultor)   ){

            ui->frameR->setVisible(true);
            ui->frameR1->setEnabled(false);
            loginRevision=true;
            ui->tab_2->setEnabled(false);
            ui->tab_4->setEnabled(false);
            pruebitaBotonesTab();

        }else{
            QMessageBox::warning(this,"Datos no congruetes","Clave incorrecta");
        }

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
     ui->RTW_revision->setRowCount(0);
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
    ui->RTW_revision->setColumnCount(10);//tab 2 tw_doble

    ui->RTW_revision->setHorizontalHeaderLabels(QStringList() <<"MODIFCAR"<<"VER DOCX"<<"ESTADO"<<"INGRESADO POR"<<"# CUENTA"<<"FACULTAD"<<"CARRERA"<<"CODIGO CLASE"<<"PATH"<<"OBSERVACION");
    int fila = 0;

    recorrerArbolParaTabla(arbolSilabo, fila,listaUsuarios.PrimPtr);
}

void MainWindow::recorrerArbolParaTabla(Arbol *nodo, int &fila,nodoD<Usuario> *actD )
{
    if (nodo == nullptr || actD==0) {
        return;
    }
    bool mostrar=false;

    recorrerArbolParaTabla(nodo->getArbolIzq(), fila,actD);

    Silabo *silabo = nodo->getRaiz();

    if(actD != nullptr){
        if((ui->Rcb_usuario->currentIndex()==1 || ui->Rcb_usuario->currentIndex()==2)&& (silabo->getEstado()=="Prerevision" || silabo->getEstado()=="Devolver a Academia")){
            mostrar=true;
        }else if(ui->Rcb_usuario->currentIndex()==3 && silabo->getEstado()=="Cargar silabo (Enviar a IEDD)"){
            mostrar=true;
        }else if(ui->Rcb_usuario->currentIndex()==4 && silabo->getNumRevisiones()>0){
            mostrar=true;
        }else{
            mostrar=false;
        }

        if(mostrar){
            ui->RTW_revision->setRowCount(fila + 1);
            ui->RTW_revision->setItem(fila, 0, new QTableWidgetItem(QString::fromStdString("EDITAR")));
            ui->RTW_revision->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString("VER")));
            ui->RTW_revision->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(silabo->getEstado())));
            ui->RTW_revision->setItem(fila, 3, new QTableWidgetItem(QString::fromStdString(actD->Dato.getName())));
            ui->RTW_revision->setItem(fila, 4, new QTableWidgetItem(QString::fromStdString(actD->Dato.getCuenta())));
            ui->RTW_revision->setItem(fila, 5, new QTableWidgetItem(QString::fromStdString(silabo->getFacultad())));
            ui->RTW_revision->setItem(fila, 6, new QTableWidgetItem(QString::fromStdString(silabo->getCarreras())));
            ui->RTW_revision->setItem(fila, 7, new QTableWidgetItem(QString::fromStdString(silabo->getCodigoClase())));
            ui->RTW_revision->setItem(fila, 8, new QTableWidgetItem(silabo->getRuta()));
            ui->RTW_revision->setItem(fila, 9, new QTableWidgetItem(QString::fromStdString(silabo->getObservacion())));
            fila++;
        }


   }
    // Incrementar el contador de filas
 //   fila++;
    actD = actD->SigPtr;

    recorrerArbolParaTabla(nodo->getArbolDer(), fila,actD);
}




void MainWindow::on_RTW_revision_cellClicked(int row, int column)
{
    if(column==0){
        QString dato = ui->RTW_revision->item(row, 7)->text() +"    Observacion:"  +ui->RTW_revision->item(row, 9)->text();
        ui->Rle_seleccion->setText(dato);
        QString estado = ui->RTW_revision->item(row, 2)->text();
        ui->Rle_estadoA->setText(estado);

    }else if(column ==1){
        if (row>=0 && row<pdfFilePaths.size()) {
            QString selectedFilePath = pdfFilePaths[row];
            QDesktopServices::openUrl(QUrl::fromLocalFile(selectedFilePath));
        }
    }
}

//logica tab3
void MainWindow::on_Bbtn_sesion_clicked()
{
    if(ui->Ble_name->text().isEmpty() || ui->Ble_clave->text().isEmpty() || ui->Bcb_usuario->currentIndex()==0){
        QMessageBox::warning(this,"Datos no congruetes","Favor no deje campos sin completar");
    }else{
        if((ui->Bcb_usuario->currentIndex()==1 && ui->Ble_clave->text().toStdString()==claveDirector) ||
           (ui->Bcb_usuario->currentIndex()==2 && ui->Ble_clave->text().toStdString()==claveDecano)   ){

            ui->frameB->setVisible(true);
            ui->frameB1->setEnabled(false);
            loginBoard=true;
            ui->tab_3->setEnabled(false);
            ui->tab_2->setEnabled(false);

            ui->treeWidget->clear();


                       QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->treeWidget);
                       parentItem->setText(0, "Raíz");

                       recorrerArbolParaTree(arbolSilabo, parentItem, "Prerevision");

        }else{
            QMessageBox::warning(this,"Datos no congruetes","Clave incorrecta");
        }

    }
}

void MainWindow::recorrerArbolParaTree(Arbol *nodo, QTreeWidgetItem *parentItem, const std::string &estado)
{
    if (nodo == nullptr) {
        return;
    }

    recorrerArbolParaTree(nodo->getArbolIzq(), parentItem, estado);

    Silabo *silabo = nodo->getRaiz();

        QTreeWidgetItem *item = new QTreeWidgetItem(parentItem);

        item->setText(0, QString::fromStdString(silabo->getCodigoClase()));


    recorrerArbolParaTree(nodo->getArbolDer(), parentItem, estado);
}

void MainWindow::on_Bbtn_cerrar_clicked()
{
    loginBoard=false;
    limpiarBoard();
}
void MainWindow::limpiarBoard()
{
    ui->Ble_name->clear();
    ui->Ble_clave->clear();
    ui->Bcb_usuario->setCurrentIndex(0);
    ui->tab_3->setEnabled(true);
    ui->tab_2->setEnabled(true);
    ui->frameB->setVisible(false);
    ui->frameB1->setEnabled(true);
}



