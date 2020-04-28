#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <vector>
#include <map>
#include <string>
#include "AtributoDifuso.h"

namespace FID3Lib {

    class Elemento
    {
    private:
		
        std::string nombre;
        std::vector<AtributoDifuso> atributosDifusos;
        std::string clase;
        //std::vector<std::string> clases;
        std::map<std::string, double> clases;
        
    public:
        Elemento();
        Elemento(std::vector<AtributoDifuso> _valores);
        Elemento(std::vector<AtributoDifuso> _valores, std::string clase);
        Elemento(std::vector<AtributoDifuso> _valores, std::string clase, std::map<std::string, double> clases);
        Elemento(std::string _nombre, std::vector<AtributoDifuso> _valores, std::string _clase, std::map<std::string, double> _clases);
        void setClase(std::string _clase);
        void setClases(std::string _clase, double valor);
        void setValoresDifusos(AtributoDifuso _atributoDifuso);
        std::string getNombre();
        std::string getClase();
        std::vector<AtributoDifuso> getAtributosDifusos();
        

        // NUEVO METODO
        double getValorDifuso(std::string atributoDifuso);
        std::map<std::string, double> getClases();
        std::string imprimir();

        void clear();
        //void calculaPolivalencia(jugador);
    };

}

#endif