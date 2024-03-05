#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

using std::string;

class Usuario{
    friend class MainWindow;
private:
    string name,cuenta,tipo;
public:
    Usuario();
    Usuario(string name, string cuenta,string tipo);
    ~Usuario();

    /*
    - [ ] Directores - solo Visualización
    - [ ] Decanos - solo Visualización
    ???
    */

    const string &getName() const;
    void setName(const string &newName);
    const string &getCuenta() const;
    void setCuenta(const string &newCuenta);
    const string &getTipo() const;
    void setTipo(const string &newTipo);
};





#endif // USUARIO_H
