

#include<vector>
#include<fstream>
#include<iostream>

namespace FID3Lib
{
	class Fuzzificador
	{
	private:
		double x;
		std::vector<double> arregloFuzificado;


	public:
		Fuzzificador();
		// Atributos a fuzzificar//
		std::vector<double> fuzzificadorTemperatura(double);
		std::vector<double> fuzzificadorPresipitacion(double);
		std::vector<double> fuzzificadorCaudal(double);
		std::vector<double> fuzzificadorNivelEmbalsado(double);

		// funciones de pertenecia trapesoidales//
		double funcionPertenenciaNivelInferior(double, int, int);
		double funcionPertenenciaNivelCentral(double, int, int, int, int);
		double funcionPertenenciaNivelSuperior(double, int, int);
	};

}