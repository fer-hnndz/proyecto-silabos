#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Usuario.h>
#include <string>
#include <listaD.h>
#include <nodoD.h>
#include <Estado.h>
#include <Arbol.h>
#include <QTableWidgetItem>
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_entregarM_clicked();
    void on_btn_revision_clicked();
    void on_btn_dashboardM_clicked();
    //tab entrega
    void on_btn_sesion_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_btn_silaboE_clicked();
    void on_btn_archivoE_clicked();
    void on_cb_facultadE_currentIndexChanged(int index);
    void on_btn_closeE_clicked();
    //tab revision
    void on_Rcb_usuario_currentIndexChanged(int index);
    void on_Rbtn_sesion_clicked();
    void on_Rbtn_cerrar_clicked();
    void on_Rbtn_cambiar_clicked();
    void on_RTW_revision_cellClicked(int row, int column);
    //tab board
    void on_Bbtn_sesion_clicked();
    void on_Bbtn_cerrar_clicked();
    void on_Bbtn_proceso_clicked();
    void on_Bbtn_aceptados_clicked();

    //tab reload
    void on_Dbtn_sesion_clicked();
    void on_Dbtn_salir_clicked();
    void on_DRTW_revision_cellClicked(int row, int column);




private:
    Ui::MainWindow *ui;

    bool loginDocente=false,loginRevision=false, revision2=false, loginBoard=false, loginCheck=false;;
    void limpiarEntrega();
    void limpiarRevision();
    void limpiarBoard();

    void recorrerArbolParaTabla(Arbol *nodo, int &fila,nodoD<Usuario> *actD);
    void recorrerArbolParaTable(Arbol *nodo, QTableWidget *tableWidget, const std::string &estado);
    bool todo=false;

    void pruebitaBotonesTab();

    void cambiarSilabo(int id,QString pathActual);
    void modificarDatosSilabo(Arbol *nodo,int id,QString pathNuevo);
    string obtenerNombre(string);
    bool cambiarPath=false, cambiarEstado=false;

    listaD<Usuario> listaUsuarios;
    nodoD<Usuario> *actD;
    nodoD<Usuario> *ultD;

    Arbol *actS;
    Arbol *arbolSilabo  = new Arbol(nullptr);

    int cantSilabos=0;
    int id=0;

    string claveDocente="teacher123", claveJefe="boss123",claveCoordinador="coordinator123",claveIEDD="what123",claveConsultor="advisor123",claveDecano="dean123",claveDirector="director123";

    void mostrarDocente(Arbol *nodo,int fila,string numCuenta);

};


#endif // MAINWINDOW_H
