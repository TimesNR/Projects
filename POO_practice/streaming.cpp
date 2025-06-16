/*
-------------------------------------------------------

Alan Uriel Merlan Esquivel

7/06/2022-13/06/2022

Version 4
*/
#include <fstream>
#include <vector>
#include "Serie.h"
#include "Peliculas.h"
#ifndef _Video_
#define _Video_
#include "Video.h"
#endif
using namespace std;

int main()
{
    string myText;
    ifstream MyReadFile("movieDB.txt");
    vector<Video> videosDB;
    vector<Serie> listaDeSeries;
    vector<Peliculas> listaDePelis;
    vector<Serie> seriesFiltrados;
    vector<Video> peliculasFiltrados;
    int noDeSerie = -1;
    bool filtroPrevio = false;
    string input = "";
    while (getline(MyReadFile, myText)){ //Lee el archivo linea por linea


        if (myText[0] == '-') //Identifica los elementos que son series
        {
            myText.erase(0,1); //Borra el primer elemento
            //Separa el texto en los datos relevantes
            int elId = std::stoi(myText.substr(0, myText.find(",")));
            myText = myText.substr(myText.find(",")+1, myText.length());

            string elNombre = myText.substr(0, myText.find(","));
            myText = myText.substr(myText.find(",")+1, myText.length());

            string elGenero = myText.substr(0,myText.length());

            //Crea y mete al vector una serie
            Serie s1(elId,elNombre,elGenero);
            listaDeSeries.push_back(s1);
            videosDB.push_back(s1);
            noDeSerie++;
        }
        else if (myText[0] == '*') //Distingue los episodios de la serie
        {
            myText.erase(0,1);//Borra el identificador
            //Separa el texto end datos relevantes
            string elTitulo = myText.substr(0, myText.find(","));
            myText = myText.substr(myText.find(",")+1, myText.length());

            int laTemporada = std::stoi(myText.substr(0, myText.find(",")));
            myText = myText.substr(myText.find(",")+1, myText.length());

            float laCalif = std::stof(myText.substr(0, myText.length()));
            //agrega el episodio
            listaDeSeries[noDeSerie].agregarEpisodio(elTitulo,laTemporada,laCalif);
        }
        else{
            //Separa datos importantes para la creación de pelicuals
            int elId = std::stoi(myText.substr(0, myText.find(",")));
            myText = myText.substr(myText.find(",")+1, myText.length());

            string elNombre = myText.substr(0, myText.find(","));
            myText = myText.substr(myText.find(",")+1, myText.length());

            float laDuracion = std::stof(myText.substr(0, myText.length()));
            myText =myText.substr(myText.find(",")+1, myText.length());

            string elGenero = myText.substr(0,myText.find(","));
            myText = myText.substr(myText.find(",")+1, myText.length());

            float laCalif = std::stof(myText.substr(0, myText.length()));
            //Los agrega a los vectores correspondientes
            Peliculas plantillaPeli(elId,elNombre,laDuracion,elGenero,laCalif);
            listaDePelis.push_back(plantillaPeli);
            videosDB.push_back(plantillaPeli);
     
        }   
    }
    MyReadFile.close();
    //Menu introducción

    cout << "*************************************************************" << endl;
    cout << "                       Bienvenido :)                         " <<endl;
    cout << "  Esta aplicacion le permetira agregar videos al catalogo    "<< endl;
    cout << "     Asi como ver, algunos videos especificos                " << endl;
    cout << " Presione los botones correspondientes para las acciones     " << endl;
    cout << "                         adecuadas.                          "<<endl;
    cout << "*************************************************************" << endl;
    //Menu que corre durante el jeugo
    while (input!="E") //Permite que el programa sea continuo
    {
        cout << "          1 Ver Datos Generales de los videos               " << endl;
        cout << "                2 Filtrar por serie                         "<<endl;   
        cout << "              3 Filtrar por calificacion                    "<<endl;
        cout << "                 4 Filtrar por genero                       "<<endl;
        cout << "          5 Filtrar por serie y calificacion                "<<endl;
        cout << "                6 Agregar pelicula                          "<<endl;
        cout << "                  7 Agregar serie                           "<<endl;
        cout << "               8  Agregar episodio                         "<<endl;
        cout << "               E Terminar el programa                       "<<endl;
        cout << "*************************************************************" << endl;
        cin >> input ;
        if (input == "1"){ //Muestra datos generales de pelis y series
            cout <<"*                                  PELICULAS                               *"<<endl;
            //Muestra datos generales de peliculas
            for (int i = 0; i < listaDePelis.size(); i++)
            {
                listaDePelis[i].toStr();
            }
            cout <<"*                                  SERIES                               *"<<endl;
            //Muestra datos generales de series
            for (int i = 0; i < listaDeSeries.size(); i++)
            {
                listaDeSeries[i].toStr();
                listaDeSeries[i].mostrarTodosEpisodios();
            }
            
        }
        if (input =="2")//Seleccion de filtrado por serie
        {
                int apariciones=0;
                std::string nombreSerie;
                cout <<"Cuál es el nombre de la serie: "<<endl;
                cin >> nombreSerie;
                vector<Serie> copia; 
                //Muestra todos los episodios de la serie seleccionada
                for (int i = 0; i < listaDeSeries.size(); i++)
                {
                    if(listaDeSeries[i].getNombreSerie() == nombreSerie )
                    {
                        cout <<"Esta serie cuenta con estos episodios"<<endl;
                        listaDeSeries[i].mostrarTodosEpisodios();
                        apariciones++;
                    }
                }
                //Verifica que la serie exista
                if (apariciones ==0)
                {
                    cout << "Verifique que puso bien el nombre de la serie." << endl;
                }     
        }
        if (input =="3") //filtra por calificación
        {
            int noCalif;
            cout << "Ponga la calificacion minima para iniciar la busqueda: "<< endl;
            cout << "*************************************************************" << endl;
            cin >> noCalif;
            //Comprueba las calificaciones de las pelis
            for (int i = 0; i < listaDePelis.size(); i++)
            {
                if (listaDePelis[i].getCalificacion() >=noCalif)
                {
                    peliculasFiltrados.push_back(listaDePelis[i]);
                }
                
            }
            //Comprueba las calificaciones por series y leugo por episodios
            for (int i = 0; i < listaDeSeries.size(); i++)
            {
                for (int j = 0; j < listaDeSeries[i].getNoDeEpisodios(); j++)
                {
                    if (listaDeSeries[i].califEpisodio(j)>=noCalif)
                    {
                        cout << listaDeSeries[i].getNombreSerie() << endl;
                        listaDeSeries[i].mostrarEpisodio(j) ;
                    }
                    
                }
                
            }
            //Muestra los objetos que cumplan los criterios
            for (int i = 0; i < peliculasFiltrados.size(); i++)
            {
                peliculasFiltrados[i].toStr();
            }
            peliculasFiltrados.clear();
        }   
        if (input =="4")
        {
            cout << "Ponga el genero: "<< endl;
            std::string strGenero;
            cin >> strGenero;
            //Comprueba los generos de las peliculas
            for (int i = 0; i < listaDePelis.size(); i++)
            {
                if (listaDePelis[i].getGenero() ==strGenero)
                {
                    peliculasFiltrados.push_back(listaDePelis[i]);
                }
                
            }
            //Comprueba los generos de las serie y las imprime si cumplen las condicones
            for (int i = 0; i < listaDeSeries.size(); i++)
            {
                if (listaDeSeries[i].getGenero()==strGenero)
                {
                    listaDeSeries[i].toStr();
                }    
            }
            //Muestra las peliculas que cumplieron las condiciones
            for (int i = 0; i < peliculasFiltrados.size(); i++)
            {
                peliculasFiltrados[i].toStr();
            }
            peliculasFiltrados.clear();
        }    
        if (input =="6") { //Pide datos necesarios para hacer una pelicula
            int elId;
            std::string elNombre;
            float laDuracion;
            std::string elGenero;
            float calificacion;
            cout <<"El id:" << endl;
            cin>> elId;
            cout <<"El nombre: " << endl;
            cin>> elNombre;    
            cout <<"La duracion: " << endl;
            cin>> laDuracion;                     
            cout <<"El genero:" << endl;
            cin>> elGenero;
            cout <<"La calificacion(1 al 5)" << endl;
            cin>> calificacion; 
            Peliculas peliPrueba(elId,elNombre,laDuracion,elGenero,calificacion);           
            listaDePelis.push_back(peliPrueba);
            cout << "*************************************************************" << endl;
        }
        if (input == "7"){//Pide los datos necesarios para hacer una serie
           int idProvicional;
            string nombreProvicional;
            string generoProvicional;
            cout <<"El id: " << endl;
            cin>> idProvicional;
            cout <<"El nombre: " << endl;
            cin>> nombreProvicional;
            cout <<"El Genero: " << endl;
            cin>> generoProvicional;            
            Serie templateSerie(idProvicional,nombreProvicional,generoProvicional);
             listaDeSeries.push_back(templateSerie);
        }
        if (input == "8"){
            //Pide los datos necesarios para el procedimiento
            string nombreSerieProvicionaL;
            std::string tituloSerieProviciona;
            int temporadaDeEpisodioProvicional;
            float calificacionEpisodioProvicional; 
            cout<< "A que serie se lo quiere agregar:" << endl;
            cin >>nombreSerieProvicionaL;   
            cout<< "Titulo: " << endl;
            cin >>tituloSerieProviciona;
            cout<< "Temporada: " << endl;
            cin >>temporadaDeEpisodioProvicional;
            cout<< "Calificacion: " << endl;
            cin >>calificacionEpisodioProvicional;
            Episodios eProvicional(tituloSerieProviciona,temporadaDeEpisodioProvicional,calificacionEpisodioProvicional);
            //Busca la serie a la que se quiere agregar episodios
            for(int i = 0; i < listaDeSeries.size(); i++)
            {
                //Agrega el episodio
               if (listaDeSeries[i].getNombreSerie () == nombreSerieProvicionaL)
               {
                    listaDeSeries[i] + eProvicional;
               }
               
            }
            
    
        }  
        if (input == "5"){//Filtro por serie y calificacion
            //Pedir datos generales
            cout <<"De que serie quiere que se busque: " << endl;
            string nombreSerie;
            cin >> nombreSerie;
            cout <<"A partir de que calificación quiere que se busque: " << endl;
            float noCalif;
            cin >> noCalif;
            bool a = false;
            //Explora todas las series disponibles
            for (int i = 0; i < listaDeSeries.size(); i++)
            {
                //Busca la serie especifica
                if (listaDeSeries[i].getNombreSerie() == nombreSerie)
                {

                    a=true;
                    //Busca dentro de todos los episodios
                    for (int j = 0; j < listaDeSeries[i].getNoDeEpisodios(); j++)
                    {
                        //Filtra los episodios que cuenten con la calificaion requerida y los imrpima
                        if (listaDeSeries[i].califEpisodio(j)>=noCalif)
                        {
                            cout << listaDeSeries[i].getNombreSerie() << endl;
                            listaDeSeries[i].mostrarEpisodio(j) ;
                            cout << "*************************************************************" << endl;
                            a=true;
                        }
                        
                    }                   
                }
                //Maneja si no existen las calificaione o si el nombre no es correccto
                if (a==false)
                {
                    cout <<"No hay episodios con esa calificacion o el nombre no es correcto" << endl;
                }
                
            }
        }
    }      
}