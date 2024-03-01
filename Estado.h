#ifndef ESTADO_H
#define ESTADO_H

enum Estado {
    // Cuando coordinador o jefe lo recibe
    Prerevision,

    // Cuando pasa a IEDD
    ListoRevision,

    // Tipos de aprobacion (Consultor)
    Aprobado,
    AprobadoCondicion,

    // Cambios

    // Cuando se le vuelve a pedir a Docente que modifique desde cero.
    SolicitudCambio,

    DevueltoAcademia,

    // Subidas despues de corregir (Consultor)
    Correcion,
    CorrecionMayor,
    CorrecionMenor



};

#endif // ESTADO_H
