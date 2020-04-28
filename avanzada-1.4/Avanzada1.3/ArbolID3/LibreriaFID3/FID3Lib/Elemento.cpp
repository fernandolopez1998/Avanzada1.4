#include "Elemento.h"

namespace FID3Lib {

	Elemento::Elemento() 
	{
	
	}
	Elemento::Elemento(std::vector<AtributoDifuso> _valores)
	{
		atributosDifusos = _valores;
	}

	Elemento::Elemento(std::vector<AtributoDifuso> _valores, std::string _clase)
	{
		atributosDifusos = _valores;
		clase   = _clase;
	}

	Elemento::Elemento(std::vector<AtributoDifuso> _valores, std::string _clase, std::map<std::string, double> _clases)
	{
		atributosDifusos = _valores;
		clase = _clase;
		clases = _clases;
	}

	Elemento::Elemento(std::string _nombre, std::vector<AtributoDifuso> _valores, std::string _clase, std::map<std::string, double> _clases)
	{
		nombre = _nombre;
		atributosDifusos = _valores;
		clase = _clase;
		clases = _clases;
	}

	void Elemento::setClase(std::string _clase)
	{
		clase = _clase;
	}

	void Elemento::setClases(std::string _clase, double valor)
	{
		Elemento::getClases()[_clase] = valor;
	}

	void Elemento::setValoresDifusos(AtributoDifuso _atributoDifuso)
	{
		atributosDifusos.insert(atributosDifusos.end(), _atributoDifuso);
	}

	std::string Elemento::getClase()
	{
		return clase;
	}
	std::map<std::string, double> Elemento::getClases() {
		
		return clases;
	}
	std::string Elemento::getNombre() {
		return nombre;
	}

	std::vector<AtributoDifuso> Elemento::getAtributosDifusos()
	{
		return atributosDifusos;
	}
	
	std::string Elemento::imprimir() {

		std::string tupla;
		tupla = Elemento::getNombre();
		std::map<std::string, double>::iterator it = Elemento::getClases().begin();
		while (it != Elemento::getClases().end())
		{
			tupla = tupla + std::to_string(it->second);

			it++;
		}
		return tupla;
		
	}
	// Nuevo metodo para clasificar
	double Elemento::getValorDifuso(std::string atributoDifuso) {
		for (int i = 0; i < atributosDifusos.size(); i++) {
			if (atributosDifusos[i].getNombre() == atributoDifuso) {
				double valor = (atributosDifusos[i].getTipos())[atributoDifuso];
				return valor;
			}
			else {
				return 1;
			}
		}
	}

	void Elemento::clear()
	{
		atributosDifusos.clear();
	}
}