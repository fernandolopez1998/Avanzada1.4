#ifndef ELEMENTONOFUZZY_H
#define ELEMENTONOFUZZY_H

#include <vector>
#include <map>
#include <string>

namespace FID3Lib {

	class ElementoNofuzzy
	{
	private:
		std::string nombre;
		std::map<std::string, double> atributosNoFuzzy;
	public:
		ElementoNofuzzy();
		ElementoNofuzzy(std::map<std::string, double> _atributosNoFuzzy);
		ElementoNofuzzy(std::string name, std::map<std::string, double> _atributosNoFuzzy);
		void SetAtributos(std::map<std::string, double> _atributosNoFuzzy);
		void clear();
	};

}
#endif