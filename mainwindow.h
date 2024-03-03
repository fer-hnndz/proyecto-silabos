#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    bool loginDocente=false,loginRevision=false, revision2=false;
    void limpiarEntrega();
    void limpiarRevision();

    void pruebitaBotonesTab();
};
#endif // MAINWINDOW_H
