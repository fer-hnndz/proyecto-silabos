#ifndef LISTAD_H
#define LISTAD_H
#include <nodoD.h>
#include <iostream>
#include <QMessageBox>
#include <Usuario.h>
#include <fstream>
using std::cout;
using std::string;
using std::cerr;


template<typename tipo>
class listaD{
    friend class MainWindow;
    friend class Arbol;
private:
    nodoD<tipo> *PrimPtr;
    nodoD<tipo> *UltPtr;
    int Cantidad;

public:
    listaD();
    ~listaD();
    void InsertarFin(const tipo &);

    bool Vacia()const;

    bool GuardarEnArchivo(string Nombre)const;
    bool ImportarArchivo(string Nombre);
    void guardarExcelUsuarios(std::ofstream &file, listaD<Usuario> &listaUsuarios);
    void guardarUsuarios(listaD<Usuario> &listaUsuarios);
    void cargarUsuarios();

};

template<typename tipo>
listaD<tipo>::listaD() :PrimPtr(0),UltPtr(0), Cantidad(0)
{}

template<typename tipo>
listaD<tipo>::~listaD()
{
    if (!Vacia()) {
        cout << "Limpiando\n" << std::endl;
        nodoD<tipo> *ptrAct = PrimPtr;
        nodoD<tipo> *ptrTemp;
        while (ptrAct != 0) {
            ptrTemp = ptrAct;
            //            cout << ptrTemp->Dato << "\n";
            ptrAct = ptrAct->SigPtr;
            if (ptrAct != nullptr) {
                ptrAct->AntPtr = nullptr;
            }
            Cantidad--;
            delete ptrTemp;
        }
        cout << "Vacio\n";
    }
}

template<typename tipo>
void listaD<tipo>::InsertarFin(const tipo &Dato)
{
    nodoD<tipo> *nuevo=new nodoD<tipo>(Dato);
    if(Vacia()){
        PrimPtr=nuevo;
        UltPtr=nuevo;
    }else{
        if(Cantidad==1){
            nuevo->SigPtr=0;
            nuevo->AntPtr=PrimPtr;
            UltPtr=nuevo;
            PrimPtr->SigPtr=nuevo;
        }else{
            nuevo->SigPtr=0;
            nuevo->AntPtr=UltPtr;
            UltPtr->SigPtr=nuevo;
            UltPtr=nuevo;
        }
    }
    Cantidad++;

}

template<typename tipo>
bool listaD<tipo>::Vacia() const
{
    return PrimPtr==nullptr;
}

template<typename tipo>
void listaD<tipo>::guardarExcelUsuarios(std::ofstream &file, listaD<Usuario> &listaUsuarios)
{
    nodoD<Usuario> *tmp = listaUsuarios.PrimPtr;
    while (tmp != nullptr) {
        Usuario usuario = tmp->getDato();
        file << usuario.getName() << "\t"
             << usuario.getCuenta() << "\t"
             << usuario.getTipo() << "\n";
        tmp = tmp->SigPtr;
    }
}

template<typename tipo>
void listaD<tipo>::guardarUsuarios(listaD<Usuario> &listaUsuarios)
{
    std::ifstream file;
    file.open("usuarios.xls");
    file.close();
    std::ofstream File("usuarios.xls");
    if (File.is_open()) {
        File << "Nombre\tCuenta\tClase Ingresada\n";
        guardarExcelUsuarios(File, listaUsuarios);
        File.close();
        cout << "XLS exportado\n";
    } else {
        cerr << "Error en el archivo\n";
    }
}

template<typename tipo>
void listaD<tipo>::cargarUsuarios()
{
    std::ifstream file("usuarios.xls");
    if (file.is_open()) {

        string header;
        std::getline(file, header);

        string nombre, cuenta, code;
        while (file >> nombre >> cuenta >> code) {
            Usuario nuevo(nombre, cuenta, code);
            InsertarFin(nuevo);
        }
        file.close();
        cout << "Usuarios cargados desde el archivo\n";
    } else {
        cerr << "Error al abrir el archivo\n";
    }

//    if (std::remove("usuarios.xls") != 0 ) {
//        std::cerr << "Error al eliminar el archivo.\n";
//    } else {
//        cout << "Archivo eliminado exitosamente.\n";
//    }
}
#endif // LISTAD_H
