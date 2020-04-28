#ifndef FID3_H
#define FID3_H

#include <vector>
#include <string>
#include <stack>
#include "AtributoDifuso.h"
#include "Elemento.h"
#include "ArbolDinamico.h"

namespace FID3Lib {

    class FID3
    {
    private:
        Nodo* raiz;
        std::vector<std::string> clases;
        std::vector<Elemento> elementos;
        double thetaR;//también beta, es la proporción superior de probabilidades para detener la expansión
        double thetaN;//porcentaje mínimo de elementos respecto al dataset

    public:
        FID3();
        FID3(double thetaR, double thetaN);
        void agregaElemento(Elemento _elemento);
        void agregaClase(std::string clase);
        void insertaHijosFID3(Nodo* nodo, std::vector<AtributoDifuso> atributosDifusos, AtributoDifuso atributoSeleccionado,std::vector<Elemento> vecELementos);
        double entropiaDeClases(std::vector<Elemento> vecElementos);
        double *entropiaAtributoDifuso(std::string nombreAtributo, std::string nombreDifuso, std::vector<Elemento> vecELementos);
        double gananciaAtributo(std::string nombreAtributo, std::map<std::string, double>  tipos, std::vector<Elemento> vecELementos);
        std::map<std::string, double> proporcionClases(std::string nombreAtributo, std::string tipoDifuso);
        std::vector<Elemento> reduceElementos(std::string nombreAtributo, std::string  nombreDifuso, std::vector<Elemento> elementos);
        void generaArbolFID3();
        void recorrePreOrden(Nodo* nodo, Elemento elemento, std::stack <double> ambiguedades, double min);
        void recorreArbolFID3(Elemento elemento);
    };

}

#endif