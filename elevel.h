#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flux_calc.cpp"
//#include "csvinterator.cpp"

#ifndef ELEVEL_H
#define ELEVEL_H

using namespace std;

struct Elevel{
    public:
        std::vector<Slab> fluxcross;
        float eval; //energy level in eV
        std::string sigmadirec; //path to energy-specific sigma directory
        std::string densdirec; //path to energy-specific density directory

};

#endif /* ELEVEL_H */