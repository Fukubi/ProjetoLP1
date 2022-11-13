#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#include <iostream>
#include <string>

class Funcionario {
 public:
  Funcionario();
  Funcionario(int newType);
  virtual ~Funcionario();

  int getCodigo();
  virtual std::string getNome();
  std::string getEndereco();
  std::string getTelefone();
  std::string getDataIngresso();
  std::string getDesig();  // switch(tipo) return designacao
  int getTipo();
  float getSalario();

  void setCodigo(int code);
  void setNome(std::string name);
  void setEndereco(std::string address);
  void setTelefone(std::string telephone);
  void setDataIngresso(
      int day, int month,
      int year);  // a data sera uma string contendo essas variaveis
  void setDataIngresso(std::string data);
  void setSalario(float salary);
  void setTipo(int tipo);

 protected:
 private:
  int codigo, tipo;
  std::string nome, endereco, dIngresso, telefone, desig;
  float salario;
};

#endif  // FUNCIONARIO_H
