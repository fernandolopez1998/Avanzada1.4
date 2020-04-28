#include "AtributoDifuso.h"


namespace FID3Lib {
	AtributoDifuso::AtributoDifuso()
	{
	}
	AtributoDifuso::AtributoDifuso(std::string _nombre, std::map<std::string, double> _tipos)
	{
		nombre  = _nombre;
		tipos   = _tipos;
	}

	std::string AtributoDifuso::getNombre()
	{
		return nombre;
	}
	
	std::map<std::string, double> AtributoDifuso::getTipos()
	{
		return tipos;
	}

}
