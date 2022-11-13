#ifndef GERENTE_H
#define GERENTE_H

#include "Funcionario.h"


class Gerente : public Funcionario
{
    public:
        Gerente();
        void setSup(std::string supervision);
        std::string getSup();

    protected:

    private:
        std::string areaSup;
};

#endif // GERENTE_H
