#include "Diretor.h"

Diretor::Diretor() : Funcionario(3)
{
    areaSup = " ";
    areaForm = " ";
}

void Diretor::setSup(std::string supervision){
    areaSup = supervision;
}

std::string Diretor::getSup(){
    return areaSup;
}

void Diretor::setForm(std::string formation){
    areaForm = formation;
}

std::string Diretor::getForm(){
    return areaForm;
}
