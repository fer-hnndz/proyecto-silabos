#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string.h>

using std::string;

class Usuario{
    Usuario();
    Usuario(string name, string pass); //Los permisos se agregarian despues de crear el usuario con los setters
    string name;
    string pass;

    // permisos
    bool canLoadSyllabus; // si puede cargar silabo (cuenta como pre-revision tambien)
    bool canMakePrerevision; // si puede hacer pre-revision (incluye enviar devuelta a docente)
    bool canSendToConsultor; // si puede enviar silabo a revision (enviarlo a consultor)
    bool canSendToIEDD; // si puede enviarlo al IEDD
    bool canMakeRevision;
    bool canSendBackToIEDD; // enviar a revision con IEDD
    bool canApproveSyllabus; // Si puede aprobar el silabo


    // bool canAssignConsultor; // si puede asignar consultor (??)

    /*
    - [ ] Directores - solo Visualización
    - [ ] Decanos - solo Visualización
    ???
    */


private:
    void setPermisosDocente();
    void setPermisosCoordinador();
    void setPermisosDirectorODecano();
    void setPermisosIEDD();
    void setPermisosConsultor();
};


Usuario::Usuario()
{
    this->name = "";
    this->pass = "";
}

Usuario::Usuario(std::string name, std::string pass)
{
    this->name=name;
    this->pass=pass;
}

void Usuario::setPermisosDocente()
{
    this->canLoadSyllabus = true;

    this->canMakePrerevision = false;
    this->canSendToConsultor = false;
    this->canSendToIEDD = false;
    this->canMakeRevision = false;
    this->canApproveSyllabus = false;
}

void Usuario::setPermisosCoordinador()
{
    this->canMakePrerevision = true;
    this->canSendToIEDD = true;

    this->canLoadSyllabus = false;
    this->canSendToConsultor = false;
    this->canMakeRevision = false;
    this->canApproveSyllabus = false;
}


void Usuario::setPermisosIEDD()
{
    this->canSendToConsultor = true;
    this->canMakeRevision = true;

    this->canMakePrerevision = false;
    this->canSendToIEDD = false;
    this->canLoadSyllabus = false;
    this->canApproveSyllabus = false;
}

void Usuario::setPermisosConsultor()
{
    this->canSendBackToIEDD = true;
    this->canApproveSyllabus = true;

    this->canSendToConsultor = false;
    this->canMakeRevision = false;
    this->canMakePrerevision = false;
    this->canSendToIEDD = false;
    this->canLoadSyllabus = false;
}

void Usuario::setPermisosDirectorODecano()
{
    // SOLO VISUALIZA
    this->canMakePrerevision = false;
    this->canSendToConsultor = false;
    this->canLoadSyllabus = false;
    this->canSendToIEDD = false;
    this->canMakeRevision = false;
    this->canApproveSyllabus = false;
    this->canSendBackToIEDD = false;
}

#endif // USUARIO_H
