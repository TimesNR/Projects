#ifndef _Video_
#include "Video.h"
#define _Video_
#endif
#include "Episodios.h"
class Serie : public Video
{
    std::vector<Episodios> listaDeEpisodios;
    int idSerie;
    std::string nombreSerie;
    std::string generoSerie; 
    public:
    Serie(int elId, std::string elNombre,std::string elGenero) : Video(elId,elNombre,elGenero)
    {
        idSerie = elId;
        nombreSerie = elNombre;
        generoSerie = elGenero;
    }
    Serie(){}
    void operator +( Episodios obj){
        this->listaDeEpisodios.push_back(obj);
    }
    void agregarEpisodio(Episodios  elEpisodio){
        listaDeEpisodios.push_back(elEpisodio);
    }
    void mostrarTodosEpisodios(){
        int contador = -1;
        std::cout << "*************************************************************" << std::endl;
        std::cout << nombreSerie << std::endl;
        if (listaDeEpisodios.size()==0)
        {
            std::cout << "No hay episodios." <<std::endl;
            std::cout << "*************************************************************" << std::endl;
        }
        else{
            for (int i = 0; i < listaDeEpisodios.size(); i++)
            {
                listaDeEpisodios[i].toStr();
            }
            
            std::cout << "*************************************************************" << std::endl;
        }

    }
    void mostrarEpisodio(int i){
        listaDeEpisodios[i].toStr();
    }
    void mostrarEpisodio(int inicio,int final){
        for (int i = inicio; i < final; i++)
        {
           listaDeEpisodios[i].toStr();
        }
    }    
    void agregarTemporada(int cantidadDeEpisodios){ //Agrega una serie de episodios
        std::string t;
        int tempo;       
        tempo = listaDeEpisodios[listaDeEpisodios.size()-1].getTemporada()+1;
        int calif;
        for (int i = 0; i < cantidadDeEpisodios; i++)
        {
            std::cout << "Titulo: " << std::endl;
            std::cin >> t ;
            std::cout << "Calificacion: " << std::endl;
            std::cin >> calif;            
            Episodios piloto(t,tempo,calif);
            listaDeEpisodios.push_back(piloto);
        }
    };
    void agregarEpisodio(std::string titulo,int temp, int calif){
        int contador = 0;
        Episodios e1(titulo,temp,calif);
        listaDeEpisodios.push_back(e1);
    }
    float califEpisodio(int no){
       return listaDeEpisodios[no].getCalificacion();
    }
    std::string getNombreSerie(){
        return nombreSerie;
    };
    int getNoDeEpisodios(){ //Devuelve cuantos episodios hay
        return listaDeEpisodios.size();
    }
    Episodios getEpisodioEspecifico(int n){
        return listaDeEpisodios[n];
    }
    void toStr(){//Imprime daos generales
        std::cout << "*************************************************************" << std::endl;
        std::cout << "El id: " << idSerie << std::endl;
        std::cout << "El nombre: " << nombreSerie << std::endl;   
        std::cout << "El genero es: " << generoSerie << std::endl;
        std::cout << "*************************************************************" << std::endl;
    };
};