#ifndef LISTAD_H
#define LISTAD_H
#include <nodoD.h>
#include <iostream>
#include <QMessageBox>

using std::cout;
using std::string;

template<typename tipo>
class listaD{
    friend class cframe;
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
            cout << ptrTemp->Dato << "\n";
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
#endif // LISTAD_H
