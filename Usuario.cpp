#include "Usuario.h"

const std::string &Usuario::getName() const {
    return name;
}

void Usuario::setName(const std::string &newName) {
    name = newName;
}

const std::string &Usuario::getCuenta() const {
    return cuenta;
}

void Usuario::setCuenta(const std::string &newCuenta) {
    cuenta = newCuenta;
}

const std::string &Usuario::getTipo() const {
    return tipo;
}

void Usuario::setTipo(const std::string &newTipo) {
    tipo = newTipo;
}

Usuario::Usuario() {
    this->name = "";
    this->cuenta = "";
    this->tipo = "";
}

Usuario::Usuario(std::string name, std::string cuenta, std::string tipo) {
    this->name = name;
    this->cuenta = cuenta;
    this->tipo = tipo;
}

Usuario::~Usuario() {}

