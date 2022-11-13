#ifndef DIRETOR_H
#define DIRETOR_H

#include "Funcionario.h"


class Diretor : public Funcionario
{
    public:
        Diretor();
        void setSup(std::string supervision);
        std::string getSup();
        void setForm(std::string formation);
        std::string getForm();

    protected:

    private:
        std::string areaSup;
        std::string areaForm;
};

#endif // DIRETOR_H
