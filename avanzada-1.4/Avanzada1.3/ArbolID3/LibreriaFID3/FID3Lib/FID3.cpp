#include "FID3.h"
#include "ArbolDinamico.h"
#include <iostream>
#include <cmath>
#include <stack>   

namespace FID3Lib {

	FID3::FID3()
	{
		thetaR = 1; //tope superior para dejar de expandir el nodo
		thetaN = 0; //tope inferior para dejar de expandir el nodo
	}

	FID3::FID3(double _thetaR, double _thetaN)
	{
		thetaR = _thetaR; //tope superior para dejar de expandir el nodo
		thetaN = _thetaN; //tope inferior para dejar de expandir el nodo
	}

	void FID3::agregaElemento(Elemento _elemento)
	{
		elementos.insert(elementos.end(), _elemento);
	}

	void FID3::agregaClase(std::string _clase)
	{
		clases.insert(clases.end(), _clase);
	}

	double FID3::entropiaDeClases(std::vector<Elemento> vecElementos)
	{
		double total = vecElementos.size();
		std::vector<double> probabilidadClase;
		std::vector<double> log2ProbabilidadClase;
		for (unsigned int i = 0; i < clases.size(); ++i)
		{
			int contadorClase = 0;
			for (unsigned int j = 0; j < vecElementos.size(); ++j)
			{
				if (clases[i] == vecElementos[j].getClase())
				{
					contadorClase++;
				}
			}
			double probAux = (contadorClase / total);
			probabilidadClase.insert(probabilidadClase.end(), probAux);
			log2ProbabilidadClase.insert(log2ProbabilidadClase.end(), -1 * log2(probAux));
		}
		double entropiaDeClases = 0;
		for (unsigned int i = 0; i < probabilidadClase.size(); ++i)
		{
			entropiaDeClases += probabilidadClase[i] * log2ProbabilidadClase[i];
		}
		return entropiaDeClases;
	}

	double FID3::gananciaAtributo(std::string _nombreAtributo, std::map<std::string, double>  _tipos, std::vector<Elemento> vecELementos)
	{
		double entropiaConjuntoAtributo;
		double HAtributo;
		double entropiaConjuntoTotal = 0;
		double HTotal = 0;
		for (std::map<std::string, double>::const_iterator it = _tipos.begin(); it != _tipos.end(); it++)
		{
			std::string nombreDifuso = it->first;
			entropiaConjuntoTotal += entropiaAtributoDifuso(_nombreAtributo, nombreDifuso, vecELementos)[1];
		}
		for (std::map<std::string, double>::const_iterator it = _tipos.begin(); it != _tipos.end(); it++)
		{
			std::string nombreDifuso = it->first;
			double* temp = entropiaAtributoDifuso(_nombreAtributo, nombreDifuso, vecELementos);
			HAtributo = temp[0];
			entropiaConjuntoAtributo = temp[1];
			HTotal += HAtributo * (entropiaConjuntoAtributo / entropiaConjuntoTotal);
		}
		std::cout << "HTotal de " << _nombreAtributo << " : " << HTotal << std::endl;
		return (entropiaDeClases(vecELementos) - HTotal);
	}

	std::map<std::string, double> FID3::proporcionClases(std::string nombreAtributo, std::string _tipoDifuso)
	{
		std::map<std::string, double> proporcionClases;
		for (unsigned int i = 0; i < clases.size(); ++i)
		{
			proporcionClases[clases[i]] = 0;
		}
		double totalClases = 0;
		for (unsigned int i = 0; i < elementos.size(); ++i)
		{
			std::vector<AtributoDifuso> atributosDifusos = elementos[i].getAtributosDifusos();
			for (unsigned int j = 0; j < atributosDifusos.size(); ++j)
			{
				if (atributosDifusos[j].getNombre() == nombreAtributo)
				{
					std::map<std::string, double> _tiposAtrib = atributosDifusos[j].getTipos();
					for (std::map<std::string, double>::const_iterator it = _tiposAtrib.begin(); it != _tiposAtrib.end(); it++)
					{
						std::string nombreDifuso = it->first;
						double valor = it->second;
						if (nombreDifuso == _tipoDifuso)
						{
							proporcionClases[elementos[i].getClase()] += valor;
							totalClases += valor;
						}
					}
				}
			}
		}
		for (std::map<std::string, double>::const_iterator it = proporcionClases.begin(); it != proporcionClases.end(); it++)
		{
			std::string nombreClase = it->first;
			//double valor = it->second;
			proporcionClases[nombreClase] /= totalClases;
		}
		return proporcionClases;
	}

	double* FID3::entropiaAtributoDifuso(std::string nombreAtributo, std::string nombreDifuso, std::vector<Elemento> vecELementos)
	{
		double entropiaAtributo = 0;
		double entropiaConjunto = 0;
		std::vector<double> contadorClases;
		for (unsigned int i = 0; i < clases.size(); ++i)
		{
			contadorClases.insert(contadorClases.end(), 0);
		}
		for (unsigned int i = 0; i < vecELementos.size(); ++i)
		{
			std::vector<AtributoDifuso> atributosDifusos = vecELementos[i].getAtributosDifusos();
			for (unsigned int j = 0; j < atributosDifusos.size(); ++j)
			{
				if (atributosDifusos[j].getNombre() == nombreAtributo)
				{
					std::map<std::string, double>  tiposAtrib = atributosDifusos[j].getTipos();
					for (unsigned int k = 0; k < tiposAtrib.size(); ++k)
					{
						if (tiposAtrib.find(nombreDifuso) != tiposAtrib.end()) {
							for (unsigned int l = 0; l < clases.size(); ++l)
							{
								if (vecELementos[i].getClase() == clases[l])
								{
									contadorClases[l] += tiposAtrib[nombreDifuso];
									entropiaConjunto += tiposAtrib[nombreDifuso];
								}
							}
						}
					}
				}
			}

		}
		double parcial = 0;
		for (unsigned int m = 0; m < clases.size(); ++m)
		{
			parcial = contadorClases[m] / entropiaConjunto;
			entropiaAtributo += (parcial * -1 * log2(parcial));
		}
		double entropias[2] = { entropiaAtributo, entropiaConjunto };
		return entropias;
	}

	std::vector<Elemento> FID3::reduceElementos(std::string nombreAtributo, std::string  nombreDifuso, std::vector<Elemento> elementos)
	{
		std::vector<Elemento> vecELementos = elementos;
		//Eliminamos aquellos elementos en los cuales el valor de pertenecia del atributo sea 0
		for (unsigned int i = 0; i < vecELementos.size(); ++i)
		{
			std::vector<AtributoDifuso> atributosDifusos = vecELementos[i].getAtributosDifusos();
			for (unsigned int x = 0; x < atributosDifusos.size(); ++x)
			{
				if (atributosDifusos[x].getNombre() == nombreAtributo)
				{
					std::map<std::string, double>  tiposAtrib2 = atributosDifusos[x].getTipos();
					if (tiposAtrib2[nombreDifuso] == 0) {
						vecELementos.erase(vecELementos.begin() + i);
					}
				}
			}
		}
		return vecELementos;
	}

	void FID3::insertaHijosFID3(Nodo* nodo, std::vector<AtributoDifuso> _atributosDifusos, AtributoDifuso atribDifSeleccionado, std::vector<Elemento> vecELementos)
	{
		//---------------------------------
		// Calcula proporción de cada clase 
		//---------------------------------
		std::map<std::string, double> _tiposADif = atribDifSeleccionado.getTipos();
		std::string nombreAtributo = atribDifSeleccionado.getNombre();
		for (std::map<std::string, double>::const_iterator it = _tiposADif.begin(); it != _tiposADif.end(); it++)
		{
			double proporcionMayor = 0;
			std::vector<AtributoDifuso> atributosDifusos = _atributosDifusos;
			std::string nombreDifuso = it->first;
			std::map<std::string, double> proporcionClase = proporcionClases(nombreAtributo, nombreDifuso);
			std::cout << "Clase AHORRAR  " << nombreAtributo << "->" << nombreDifuso <<": " <<proporcionClase["AHORRAR"]<<std::endl;
			std::cout << "Clase NO AHORRAR  " << nombreAtributo << "->" << nombreDifuso <<": " <<proporcionClase["NOAHORRAR"] << std::endl;
			//obtener la clase con mayor proporción
			double valorMayor = 0;
			std::string claseMayor;
			for (std::map<std::string, double>::const_iterator it = proporcionClase.begin(); it != proporcionClase.end(); it++)
			{
				if (it->second > valorMayor) {
					valorMayor = it->second;
					claseMayor = it->first;
				}
			}

			std::cout << "atributosDifusos.size(): " << atributosDifusos.size() << std::endl;
			if ( valorMayor>thetaR || atributosDifusos.size() == 0) {// || proporcionAtributoEnDataset(nombreAtributo)< thetaN
				//el nombreAtributo en las hojas es el nombre de la clase mayor
				//Nodo* nodoS = nuevoNodo(claseMayor,true, proporcionClase);
				Nodo *nodoS = nuevoNodo(claseMayor, nombreDifuso,true, proporcionClase); // Lo modifique, incorporo ramaNombrePadre
				(nodo->hijo).insert((nodo->hijo).end(), nodoS);
				std::cout << "-----------------------------\n";
				std::cout << "Hoja " << nombreAtributo <<", clase mayor(nombre de esta hoja): "<< claseMayor << std::endl;
				std::cout << "-----------------------------\n";
			}
			else if (valorMayor <= thetaR && atributosDifusos.size() > 0) { 
				//--------------------------------------------------------
				// Busca atributo de mayor ganancia entre los que quedan!!  
				//--------------------------------------------------------
				std::cout << "-----------------------------\n";
				std::cout << "Clase: " << claseMayor <<": "<<valorMayor << std::endl;
				std::cout << "-----------------------------\n";
				//atributosDifusos
				double mayorGanancia = 0;
				std::string atributoSeleccionado;
				std::map<std::string, double> atributosDifSeleccionados;
				std::vector<AtributoDifuso> atributosDifusosR = atributosDifusos;//atributos restantes
				std::vector<Elemento> elementosParcial = reduceElementos(nombreAtributo, nombreDifuso, vecELementos);
				for (unsigned int i = 0; i < atributosDifusosR.size(); ++i) {
					double ganancia;
					ganancia = gananciaAtributo(atributosDifusosR[i].getNombre(), atributosDifusosR[i].getTipos(),elementosParcial);
					if (ganancia > mayorGanancia)
					{
						mayorGanancia = ganancia;
						atributoSeleccionado = atributosDifusosR[i].getNombre();
						atributosDifSeleccionados = atributosDifusosR[i].getTipos();
					}
					std::cout << "ganancia de " << atributosDifusosR[i].getNombre() << ": " << ganancia << std::endl;
				}
				AtributoDifuso atribDifSeleccionado = AtributoDifuso(atributoSeleccionado, atributosDifSeleccionados);
				std::cout << "- - - - - - - - - - - - - - - -" << std::endl;
				std::cout << "Seleccionado: " << atributoSeleccionado << std::endl;
				for (unsigned int i = 0; i < atributosDifusos.size(); ++i) {
					if (atributosDifusos[i].getNombre() == atributoSeleccionado)
					{
						std::cout << atributosDifusos[i].getNombre() << std::endl;
						atributosDifusos.erase(atributosDifusos.begin() + i);
					}
				}

				Nodo* nodoS = nuevoNodo(atributoSeleccionado, nombreDifuso,false, proporcionClase);
				(nodo->hijo).insert((nodo->hijo).end(), nodoS);
				insertaHijosFID3((nodo->hijo).back(), atributosDifusos, atribDifSeleccionado, elementosParcial);
			}
			
		}

	}

	void FID3::generaArbolFID3() {
		//--------------------------------------------------------
		// Encuentra el atributo con mayor ganancia de información 
		//--------------------------------------------------------
		double mayorGanancia = 0;
		std::string atributoSeleccionado;
		std::map<std::string,double> atributosDifSeleccionados;
		std::vector<AtributoDifuso> atributosDifusos = elementos[0].getAtributosDifusos();
		for (unsigned int i = 0; i < atributosDifusos.size(); ++i) {
			double ganancia;
			ganancia = gananciaAtributo(atributosDifusos[i].getNombre(), atributosDifusos[i].getTipos(),elementos);
			if (ganancia > mayorGanancia) 
			{
				mayorGanancia = ganancia;
				atributoSeleccionado = atributosDifusos[i].getNombre();
				atributosDifSeleccionados = atributosDifusos[i].getTipos();
			}
			std::cout << "ganancia de " << atributosDifusos[i].getNombre() << ": " << ganancia << std::endl;
		}
		AtributoDifuso atribDifSeleccionado = AtributoDifuso(atributoSeleccionado, atributosDifSeleccionados);
		std::cout << "- - - - - - - - - - - - - - - -" << std::endl;
		std::cout << "Seleccionado: " << atributoSeleccionado << std::endl;
		for (unsigned int i = 0; i < atributosDifusos.size(); ++i) {
			if (atributosDifusos[i].getNombre() == atributoSeleccionado)
			{
				std::cout << atributosDifusos[i].getNombre() << std::endl;
				atributosDifusos.erase(atributosDifusos.begin()+i);
			}
		}
		std::map<std::string, double> _clases;
		//raiz = nuevoNodo(atributoSeleccionado, false, _clases);
		raiz = nuevoNodo(atributoSeleccionado," ", false, _clases);
		insertaHijosFID3(raiz,atributosDifusos,atribDifSeleccionado,elementos);
		
	}

	void FID3::recorrePreOrden(Nodo* raiz, Elemento elemento, std::stack<double> ambiguedad, double min) {

		if ((*raiz).esHoja) {
			std::cout << (*raiz).nombreAtributo + std::to_string(min) << std::endl;
			ambiguedad.push(elemento.getValorDifuso((*raiz).nombreRamaPadre));
			if (ambiguedad.top() < min) {
				min = ambiguedad.top();
			}
			if (elemento.getClases()[(*raiz).nombreAtributo] < min) {
				elemento.setClases((*raiz).nombreAtributo, min);
			}
			ambiguedad.pop();
		}

		if (!(*raiz).esHoja) {
			for (int i = 0; i < (*raiz).hijo.size(); i++) {
				ambiguedad.push(elemento.getValorDifuso((*raiz).nombreRamaPadre));
				std::cout << ambiguedad.top() << std::endl;
				if (ambiguedad.top() < min) {
					min = ambiguedad.top();
				}
				recorrePreOrden(((*raiz).hijo[i]), elemento, ambiguedad, min);
			}

		}
		
	}


	void FID3::recorreArbolFID3(Elemento elemento) {
		
		//--------------------------------------------------------
		// Recorre el arbol
		//--------------------------------------------------------
	
		std::cout << raiz << std::endl;
		std::stack<double> ambiguedad;
		double min = 1.;
		recorrePreOrden(raiz, elemento, ambiguedad, min);
		

	}
}

