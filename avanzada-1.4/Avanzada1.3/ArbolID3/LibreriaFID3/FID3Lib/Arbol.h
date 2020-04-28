#ifndef Arbol_H
#define Arbol_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#include <map>

#include <queue>

namespace FID3Lib {

    struct Nodo
    {
        std::string nombreAtributo;
        std::string nombreRamaPadre;
        bool esHoja = false;
        std::vector<Nodo*> hijo;
        std::map<std::string, double> clases;
    };

    Nodo* nuevoNodo(std::string nombreAtributo, bool esHoja, std::map<std::string, double> _clases)
    {
        Nodo* temp = new Nodo;
        temp->nombreAtributo = nombreAtributo;
        temp->esHoja = esHoja;
        temp->clases = _clases;
        return temp;
    }
    // Modifico esta función para agregar nombreRamaPadre por tanto hay dos maneras de crear un nuevo nodo
    Nodo* nuevoNodo(std::string nombreAtributo, std::string nombreRamaPadre, bool esHoja, std::map<std::string, double> _clases)
    {
        Nodo* temp = new Nodo;
        temp->nombreAtributo = nombreAtributo;
        temp->nombreRamaPadre = nombreRamaPadre;
        temp->esHoja = esHoja;
        temp->clases = _clases;
        return temp;
    }

    Nodo* buscaNodo(std::string valor, Nodo* nodo)
    {
        if (valor == nodo->nombreAtributo)
            return nodo;
        for (unsigned int i = 0; i < (nodo->hijo).size(); i++) {
            Nodo* temp = buscaNodo(valor, (nodo->hijo[i]));
            if (temp != NULL) {
                return temp;
            }
        }
        return NULL;
    }

    void eliminaNodoDeRaiz(Nodo* condicion, Nodo* raiz)
    {
        bool nodoEliminado = false;
        for (unsigned int i = 0; i < (raiz->hijo).size(); i++) {
            if (nodoEliminado == false) {
                if (raiz->hijo[i]->nombreAtributo == condicion->nombreAtributo) {
                    (raiz->hijo).erase((raiz->hijo).begin() + i);
                    nodoEliminado = true;
                }
            }
        }
    }

    bool nodoRepetido(Nodo* raiz, std::string condicion)
    {
        for (unsigned int i = 0; i < (raiz->hijo).size(); i++) {
            if (raiz->hijo[i]->nombreAtributo == condicion) {
                return true;
            }
        }
        return false;
    }

    void agregaCondicionANodo(Nodo* condicion, std::string consecuencia, Nodo* raiz)
    {
        bool nodoPosicionado = false;
        for (unsigned int i = 0; i < (raiz->hijo).size(); i++) {
            if (nodoPosicionado == false) {
                if (raiz->hijo[i]->nombreAtributo == consecuencia) {
                    if (!nodoRepetido(raiz->hijo[i], condicion->nombreAtributo)) {
                        raiz->hijo[i]->esHoja = false;
                        (raiz->hijo[i]->hijo).push_back(condicion);
                    }
                    nodoPosicionado = true;
                }
                else {
                    agregaCondicionANodo(condicion, consecuencia, raiz->hijo[i]);
                }
            }
        }
    }

    void agregaCondicionANodoForward(Nodo* condicion, Nodo* consecuencia, Nodo* raiz)
    {
        bool nodoPosicionado = false;
        for (unsigned int i = 0; i < (raiz->hijo).size(); i++) {
            if (nodoPosicionado == false) {
                if (raiz->hijo[i]->nombreAtributo == condicion->nombreAtributo) {
                    raiz->hijo[i]->esHoja = false;
                    (raiz->hijo[i]->hijo).push_back(consecuencia);
                    nodoPosicionado = true;
                }
                else {
                    agregaCondicionANodoForward(condicion, consecuencia, raiz->hijo[i]);
                }
            }
        }
    }

    void recorreArbol(Nodo* p, std::ofstream& outfile)
    {
        char comilla = '"';
        std::string padre = p->nombreAtributo;
        for (unsigned int i = 0; i < p->hijo.size(); i++)
        {
            outfile << comilla << padre << comilla << "->";
            outfile << comilla << p->hijo[i]->nombreAtributo << comilla << std::endl;
            recorreArbol(p->hijo[i], outfile);
        }
    }


}

#endif