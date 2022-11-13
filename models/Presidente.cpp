#include "Presidente.h"

Presidente::Presidente() : Funcionario(4)
{
    areaForm = " ";
    formMax = " ";
}

void Presidente::setForm(std::string formation){
    areaForm = formation;
}

std::string Presidente::getForm(){
    return areaForm;
}

void Presidente::setMax(std::string maxForm){
    formMax = maxForm;
}

std::string Presidente::getMax(){
    return formMax;
}
