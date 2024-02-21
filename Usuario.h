#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string.h>

using std::string;

class Usuario{
    string name;
    string pass;


    // permisos
    bool canPrerevise;
    bool canAssignConsultor;
    bool canSendRevision;
    bool canLoadSyllabus;

    /*
    - [ ] Directores - solo Visualización
    - [ ] Decanos - solo Visualización
    ???
    */

    bool canLoadRevisions;

};


#endif // USUARIO_H
