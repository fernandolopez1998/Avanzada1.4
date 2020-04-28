#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FID3Lib.h"
#include <ElementoNoFuzzy.h>
#include <Fuzzificador.h>

using namespace FID3Lib;
//	using namespace std;

int main()
{
	/*

	int opcion;

	do {
		system("cls");        // Para limpiar la pantalla

		// Texto del menú que se verá cada vez

		cout << "\n\nMenu de Opciones" << endl;
		cout << "1. Opcion 1" << endl;
		cout << "2. Mostrar Data Set" << endl;
		cout << "3. Mostrar Datos no Fuzzy" << endl;
		cout << "4. Opcion 4" << endl;
		cout << "5. SALIR" << endl;

		cout << "\nIngrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			// Lista de instrucciones de la opción 1  

			system("pause>nul"); // Pausa
			break;

		case 2:
			// Lista de instrucciones de la opción 2    

			system("pause>nul"); // Pausa
			break;

		case 3:
			// Lista de instrucciones de la opción 3                

			system("pause>nul"); // Pausa            
			break;

		case 4:
			// Lista de instrucciones de la opción 4                

			system("pause>nul"); // Pausa                
			break;
		}
	} while (opcion != 5);            // En vez de 5 pones el número de la opción de SALIDA        
	return 0;
	*/
	
	
	
	FID3 objetoFID3 = FID3();
	//FID3 objetoFID3 = FID3( 0.8, 0.1 ); //FID3(thetarR, thetaN)

	//---------------
	// Inserta Clases
	//---------------
	objetoFID3.agregaClase("AHORRAR");
	objetoFID3.agregaClase("NOAHORRAR");
	
	
	std::ifstream ip("DatosNoFuzzy.csv");
	if (!ip.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;
	std::string Temperatura;
	std::string Caudal;
	std::string Nivel;
	std::string lluvia;

	double temperaturaN;
	double caudalN;
	double nivelN;
	double lluviaN;

	ElementoNofuzzy elementonofuzzy = ElementoNofuzzy();
	Elemento elemento1 = Elemento();
	std::map<std::string, double> atributosNoFuzzy;
	std::map<std::string, double> atributosFuzzy;
	std::vector<ElementoNofuzzy> vecElementos;
	std::vector<Elemento> vecElementosfuzzy;
	Fuzzificador fuzy = Fuzzificador();
	AtributoDifuso atributoD;
	std::vector<double> vecFuzycado;
	while (ip.good())
	{
		getline(ip, Temperatura, ',');
		getline(ip, Caudal, ',');
		getline(ip, Nivel, ',');
		getline(ip, lluvia, '\n');


		temperaturaN = stod(Temperatura);
		caudalN = stod(Caudal);
		nivelN = stod(Nivel);
		lluviaN = stod(lluvia);
		//---------
		// fuzzyficar las variables
		//---------

		std::cout << "--------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Fuzzificador de: " << "Temperatura, " << " Nivel del Caudal, " << " Volumen Embalsado, " << " Precipitaciones |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------" << std::endl;
		


		vecFuzycado = fuzy.fuzzificadorTemperatura(temperaturaN);
		atributosFuzzy = { {"Caliente:",vecFuzycado[0]},{"Templado:",vecFuzycado[1]},{"Frio:",vecFuzycado[2]} };
		atributoD= AtributoDifuso("Temperatura", atributosFuzzy);
		elemento1.setValoresDifusos(atributoD);
		std::cout <<"Temperatura:      |\n" <<"Caliente: "<<vecFuzycado[0]<<"       |"<< "\nTemplado: "<< vecFuzycado[1]<<"       |"<< "\nFrio: " << vecFuzycado[2]<<"           |"<< "\n";
		std::cout << "-------------------" << std::endl;
		vecFuzycado.clear();


		vecFuzycado = fuzy.fuzzificadorCaudal(caudalN);
		atributosFuzzy = { {"Alto nivel:",vecFuzycado[0]},{"Bajo nivel:",vecFuzycado[1]}};
		atributoD = AtributoDifuso("Nivel Caudal", atributosFuzzy);
		elemento1.setValoresDifusos(atributoD);
		std::cout << "Nivel Caudal:     |\n" << "Alto: " << vecFuzycado[0]<<"           |"<< "\nBajo: " << vecFuzycado[1]<<"           |"<< "\n";
		std::cout << "-------------------" << std::endl;
		vecFuzycado.clear();

		vecFuzycado = fuzy.fuzzificadorNivelEmbalsado(nivelN);
		atributosFuzzy = { {"Alto Volumen: ",vecFuzycado[0]},{"Bajo Volumen: ",vecFuzycado[1]} };
		atributoD = AtributoDifuso("Volumen Embalsado", atributosFuzzy);
		elemento1.setValoresDifusos(atributoD);
		std::cout << "Volumen Embalsado:|\n" << "Alto: " << vecFuzycado[0]<<"           |" << "\nBajo: " << vecFuzycado[1]<<"        |"<< "\n";
		std::cout << "-------------------" << std::endl;
		vecFuzycado.clear();

		vecFuzycado = fuzy.fuzzificadorPresipitacion(lluviaN);
		atributosFuzzy = { {"Altas Precipitaciones:",vecFuzycado[0]},{"Bajas Precipitaciones:",vecFuzycado[1]} };
		atributoD = AtributoDifuso("Precipitaciones", atributosFuzzy);
		elemento1.setValoresDifusos(atributoD);
		std::cout << "Precipitaciones:  |\n" << "Altas: " << vecFuzycado[0]<<"          |"<< "\nBajas: " << vecFuzycado[1]<<"          |"<< "\n";
		std::cout << "-------------------" << std::endl;
		vecFuzycado.clear();

		vecElementosfuzzy.insert(vecElementosfuzzy.end(), elemento1);
		elemento1.clear();

	}
	ip.close();

	
	std::ifstream ip2("SetDeEntrenamiento.csv");
	if (!ip2.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;


	//Temperatura
	std::string Caliente;
	std::string Templado;
	std::string Frio;
	double temp_cal;
	double temp_tem;
	double temp_frio;


	//Nivel del caudal
	std::string Caudal_alto;
	std::string Caudal_bajo;
	double temp_Calto;
	double temp_Cbajo;


	//Volumen Embalsado
	std::string Volumen_alto;
	std::string Volumen_bajo;
	double temp_Valto;
	double temp_Vbajo;


	//Precipitaciones
	std::string Precip_Alta;
	std::string Precip_Baja;
	double Temp_Palta;
	double Temp_Pbaja;
	//clase
	std::string clase;
	Elemento elemento = Elemento();
	std::map<std::string, double> fuzzyTypes;
	while (ip2.good())
	{
		getline(ip2, Caliente, ',');
		getline(ip2, Templado, ',');
		getline(ip2, Frio, ',');

		getline(ip2, Caudal_alto, ',');
		getline(ip2, Caudal_bajo, ',');


		getline(ip2, Volumen_alto, ',');
		getline(ip2, Volumen_bajo, ',');

		getline(ip2, Precip_Alta, ',');
		getline(ip2, Precip_Baja, ',');


		getline(ip2, clase, '\n');

		temp_cal = stod(Caliente);
		temp_tem = stod(Templado);
		temp_frio = stod(Frio);

		temp_Calto = stod(Caudal_alto);
		temp_Cbajo = stod(Caudal_bajo);

		temp_Valto = stod(Volumen_alto);
		temp_Vbajo = stod(Volumen_bajo);

		Temp_Palta = stod(Precip_Alta);
		Temp_Pbaja = stod(Precip_Baja);

		//---------
		// Elemento
		//---------
		elemento.setClase(clase);

		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Set de Entrenamiento: " << "Temperatura " << std::endl;
		std::cout << "-----------------------------------------" << std::endl;

		//Temperatura
		fuzzyTypes = { {"Caliente: ",temp_cal}, {"Templado: ",temp_tem}, {"Frio: ",temp_tem} };
		elemento.setValoresDifusos(AtributoDifuso("Temperatura", fuzzyTypes));


		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Set de Entrenamiento: " << "Nivel del Caudal " << std::endl;
		std::cout << "---------------------------------------------" << std::endl;


		//Nivel Caudal
		fuzzyTypes = { {"Alto nivel: ",temp_Calto}, {"Bajo nivel: ",temp_Cbajo} };
		elemento.setValoresDifusos(AtributoDifuso("Nivel Caudal", fuzzyTypes));

		std::cout << "----------------------------------------------" << std::endl;
		std::cout << "Set de Entrenamiento: " << "Volumen Embalsado " << std::endl;
		std::cout << "----------------------------------------------" << std::endl;

		//Volumen Embalsado
		fuzzyTypes = { {"Alto Volumen: ",temp_Valto}, {"Bajo Volumen: ",temp_Vbajo} };
		elemento.setValoresDifusos(AtributoDifuso("Volumen Embalsado", fuzzyTypes));


		std::cout << "--------------------------------------------" << std::endl;
		std::cout << "Set de Entrenamiento: " << "Precipitaciones " << std::endl;
		std::cout << "--------------------------------------------" << std::endl;

		//Precipitaciones
		fuzzyTypes = { {"Altas Precipitaciones: ",Temp_Palta}, {"Bajas Precipitaciones: ",Temp_Pbaja} };
		elemento.setValoresDifusos(AtributoDifuso("Precipitaciones", fuzzyTypes));



		objetoFID3.agregaElemento(elemento);

		elemento.clear();
		//std::cout << "--------------" << std::endl;
	}
	ip2.close();
	
	//--------------------------------------------------------------------------
	// Genera arbol FID3 (con los datos de entrenamiento previamente ingresados)
	//--------------------------------------------------------------------------

	objetoFID3.generaArbolFID3(); //lo crea en memoria principal

	//----------------------------------------------------------------------
	// Clasificacion del arbol
	//----------------------------------------------------------------------

	// 
	/*Elemento jugador = Elemento();
	std::vector<Elemento> equipo = { elemento, elemento };
	objetoFID3.recorreArbolFID3(elemento);
	for (int i = 0; i < equipo.size(); i++) {
		// FALTA IMPLEMENTAR
		// Escribir un archivo
	}*/

	//std::cout << "Libreria FID3" << std::endl;*/
}