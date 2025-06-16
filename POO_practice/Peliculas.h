#ifndef _Video_
#include "Video.h"
#define _Video_
#endif
class Peliculas : public Video
{
    public:
    //Para haer el constructor primero, se necesita que sea heredado,
    Peliculas(int elId, std::string elNombre, float laDuracion,std::string elGenero,float laCalificacion ) : Video (elId,elNombre,laDuracion,elGenero,laCalificacion){}
};