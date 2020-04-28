#include "Fuzzificador.h"
#include <vector>

namespace FID3Lib {


	Fuzzificador::Fuzzificador() {

		//consructor
	}
	double Fuzzificador::funcionPertenenciaNivelInferior(double valor, int c, int d)
	{
		double valorInferior = 0;
		if (valor > d) {
			valorInferior = 0;
		}
		else if ((c <= valor) && (valor <= d)) {
			valorInferior = (d - valor) / (d - c);
		}
		else if (valor < c) {
			valorInferior = 1;
		}
		return valorInferior;
	}

	double Fuzzificador::funcionPertenenciaNivelCentral(double valor, int a, int b, int c, int d)
	{
		double valorCentral = 0;
		if ((valor < a) || (valor > d)) {
			valorCentral = 0;
		}
		else if ((a <= valor) && (valor <= b)) {
			valorCentral = (valor - a) / (b - a);
		}
		else if ((b <= valor) && (valor <= c)) {
			valorCentral = 1;
		}
		else if ((c <= valor) && (valor <= d)) {
			valorCentral = (d - valor) / (d - c);
		}
		return valorCentral;
	}

	double Fuzzificador::funcionPertenenciaNivelSuperior(double valor, int a, int b)
	{
		double valorInferior;
		if (valor < a) {
			valorInferior = 0;
		}
		else if ((a <= valor) && (valor <= b)) {
			valorInferior = (valor - a) / (b - a);
		}
		else if (valor > b) {
			valorInferior = 1;
		}
		return valorInferior;
	}

	std::vector<double> Fuzzificador::fuzzificadorTemperatura(double temperatura)
	{
		x = temperatura;
		arregloFuzificado.clear();
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelInferior(x, 0, 15));
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelCentral(x, 0, 20, 30, 35));
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelSuperior(x, 25, 35));
		return arregloFuzificado;

	}
	std::vector<double> Fuzzificador::fuzzificadorPresipitacion(double lluvia)
	{
		x = lluvia;
		arregloFuzificado.clear();
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelInferior(x, 30, 50));
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelSuperior(x, 30, 70));
		return arregloFuzificado;

	}
	std::vector<double> Fuzzificador::fuzzificadorCaudal(double caudal)
	{
		x = caudal;
		arregloFuzificado.clear();
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelInferior(x, 10000, 20000));
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelSuperior(x, 10000, 30000));
		return arregloFuzificado;

	}

	std::vector<double> Fuzzificador::fuzzificadorNivelEmbalsado(double embalse)
	{
		x = embalse;
		arregloFuzificado.clear();
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelInferior(x, 0.8, 1.5));
		arregloFuzificado.insert(arregloFuzificado.end(), funcionPertenenciaNivelSuperior(x, 0.8, 2.0));
		return arregloFuzificado;
	}

}