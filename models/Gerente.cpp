#include "Gerente.h"

#include <iostream>

Gerente::Gerente() : Funcionario(2)
{
    areaSup = " ";
}

void Gerente::setSup(std::string supervision){
    areaSup = supervision;
}

std::string Gerente::getSup(){
    return areaSup;
}
