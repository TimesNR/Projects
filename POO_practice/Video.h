#include <iostream>
#include <vector>
class Video{
    int id;
    std::string nombre;
    float duracion;
    std::string genero;
    float calificacion;
    public:
    //Constructores
    Video(int elId, std::string elNombre, float laDuracion){
        id = elId;
        nombre = elNombre;
        duracion = laDuracion;
        genero = "Desconocido";
        calificacion = 3;
    };
    Video(int elId, std::string elNombre, float laDuracion,std::string elGenero,float laCalificacion ){
        id = elId;
        nombre = elNombre;
        duracion = laDuracion;
        genero = elGenero;
        calificacion = laCalificacion;
    };
    Video(int elIde, std::string elNombre, std::string elGenero)
    {
        id = elIde;
        nombre = elNombre;
        genero = elGenero;
        duracion = 0;
        calificacion = 0;

    }
    Video(){}
    virtual void toStr(){ //Muestra datos generales
        std::cout << "*************************************************************" << std::endl;
        std::cout << "El id: " << id << std::endl;
        std::cout << "El nombre: " << nombre << std::endl;   
        if (duracion != 0)
        {
            std::cout << "La duracion: " << duracion << std::endl;
        }
        if (calificacion != 0)
        {
            std::cout << "La calificacion: " << calificacion << std::endl;
        }
        std::cout << "El genero es: " << calificacion << std::endl;
        std::cout << "*************************************************************" << std::endl;
    };
    float getCalificacion(){
        return calificacion;
    }
    std::string getGenero(){
        return genero;
    }
};