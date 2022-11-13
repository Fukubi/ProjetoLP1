#ifndef PRESIDENTE_H
#define PRESIDENTE_H

#include "Funcionario.h"


class Presidente : public Funcionario
{
    public:
        Presidente();
        void setForm(std::string formation);
        std::string getForm();
        void setMax(std::string maxForm);
        std::string getMax();

    protected:

    private:
        std::string areaForm;
        std::string formMax;
};

#endif // PRESIDENTE_H
