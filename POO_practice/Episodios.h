
#include <string>
class Episodios
{
    //¿Agregar un limitador para que lo que se agregue tenga que ser consecutivo?
    std::string titulo;
    int temporada;
    float calificacion;
    public:
    Episodios(std::string elTitulo,int laTemporada, float laCalificacion){
        titulo =elTitulo;
        temporada = laTemporada;
        calificacion = laCalificacion;
    }
    void setTitulo(std::string elTitulo){
        titulo = elTitulo;
    }
    void setTemporada(int laTemporada){
        temporada = laTemporada;
    }
    std::string getTitulo(){
        return titulo;
    }
    int getTemporada(){
        return temporada;
    }
    int getCalificacion(){
        return calificacion;
    }
    void toStr(){ //Imprime datos generales
        std::cout << "S " << temporada << " ," << titulo << " ," << calificacion << " Estrellas " << std::endl; 
    }

};