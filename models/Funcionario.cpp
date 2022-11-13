#include "Funcionario.h"

Funcionario::Funcionario() {
  // ctor
}

Funcionario::Funcionario(int newType) {
  this->tipo = newType;
  switch (newType) {
    case 1:
      tipo = 1;  // Operador
      break;
    case 2:
      tipo = 2;  // Gerente
      break;
    case 3:
      tipo = 3;  // Diretor
      break;
    case 4:
      tipo = 4;  // Presidente
      break;
    default:
      tipo = 0;  // Indefinido
      break;
  }
}

Funcionario::~Funcionario() {}

std::string Funcionario::getDesig() {
  switch (tipo) {
    case 1:
      return "Operador";
    case 2:
      return "Gerente";
    case 3:
      return "Diretor";
    case 4:
      return "Presidente";
    default:
      return "Indefinido";
  }
}

void Funcionario::setTipo(int tipo) {
  if (tipo < 0 || tipo > 4) {
    return;
  }

  this->tipo = tipo;
}

int Funcionario::getTipo() { return this->tipo; }

void Funcionario::setCodigo(int code) { codigo = code; }

int Funcionario::getCodigo() { return codigo; }

void Funcionario::setNome(std::string name) { nome = name; }

std::string Funcionario::getNome() { return nome; }

void Funcionario::setEndereco(std::string adress) { endereco = adress; }

std::string Funcionario::getEndereco() { return endereco; }

void Funcionario::setTelefone(std::string telephone) { telefone = telephone; }

std::string Funcionario::getTelefone() { return telefone; }

void Funcionario::setDataIngresso(int day, int month, int year) {
  dIngresso = std::to_string(day) + '/' + std::to_string(month) + '/' +
              std::to_string(year);
}

void Funcionario::setDataIngresso(std::string data) {
  if (data.empty()) {
    return;
  }

  this->dIngresso = data;
}

std::string Funcionario::getDataIngresso() { return dIngresso; }

void Funcionario::setSalario(float salary) { salario = salary; }

float Funcionario::getSalario() { return salario; }
