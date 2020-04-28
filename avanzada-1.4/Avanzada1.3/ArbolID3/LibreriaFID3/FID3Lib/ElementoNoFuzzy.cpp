#include "ElementoNoFuzzy.h"


namespace FID3Lib{

	ElementoNofuzzy::ElementoNofuzzy()
	{
	}

	ElementoNofuzzy::ElementoNofuzzy(std::map<std::string, double> _atributosNoFuzzy)
	{
		atributosNoFuzzy = _atributosNoFuzzy;
	}

	ElementoNofuzzy::ElementoNofuzzy(std::string name, std::map<std::string, double> _atributosNoFuzzy)
	{
		nombre = name;
		atributosNoFuzzy = _atributosNoFuzzy;
	}
	void ElementoNofuzzy::SetAtributos(std::map<std::string, double> _atributosNoFuzzy) {
		atributosNoFuzzy = _atributosNoFuzzy;
	}
	void ElementoNofuzzy::clear()
	{
		atributosNoFuzzy.clear();
	}
}
