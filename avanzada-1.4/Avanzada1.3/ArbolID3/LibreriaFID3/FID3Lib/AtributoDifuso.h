#ifndef ATRIBUTODIFUSO_H
#define ATRIBUTODIFUSO_H

#include <vector>
#include <map>
#include <string>

namespace FID3Lib {

    class AtributoDifuso
    {
    private:
        std::string nombre;
        std::map<std::string, double> tipos;

    public:
        AtributoDifuso();
        AtributoDifuso(std::string nombre, std::map<std::string, double> tipos);
        std::map<std::string, double> getTipos();
        std::string getNombre();
    };

}

#endif