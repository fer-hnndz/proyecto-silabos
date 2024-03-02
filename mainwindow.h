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
    void on_btn_sesion_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_tabWidget_currentChanged(int index);
    void on_cb_facultadE_currentIndexChanged(const QString &arg1);

    void on_btn_silaboE_clicked();

    void on_btn_archivoE_clicked();

private:
    Ui::MainWindow *ui;
    bool loginDocente=false;
    bool loginRevision=false;
    void limpiarEntrega();
};
#endif // MAINWINDOW_H
