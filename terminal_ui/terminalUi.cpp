#include "terminalUi.hpp"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Diretor.h"
#include "Gerente.h"
#include "Presidente.h"
#include "database_manager.hpp"
#include "string_utils.hpp"

TerminalUi::TerminalUi() {
  int opcao;

  std::cout << "\tGerenciador de funcionarios V1.0\n";
  while (true) {
    std::cout << "Escolha uma opcao: \n";
    std::cout << "0. Sair\n";
    std::cout << "1. Adicionar funcionario\n";
    std::cout << "2. Modificar funcionario\n";
    std::cout << "3. Excluir Funcionario\n";
    std::cout << "4. Exibir lista de funcionarios\n";
    std::cout << "5. Exibir lista de funcionarios por tipo\n";

    std::cin >> opcao;
    std::cin.ignore();

    if (opcao == 0) {
      break;
    } else if (opcao == 1) {
      this->criarFuncionario();
    } else if (opcao == 2) {
      this->atualizarFuncionario();
    } else if (opcao == 3) {
      this->excluirFuncionario();
    } else if (opcao == 4) {
      this->exibirFuncionarios();
    } else if (opcao == 5) {
      this->exibirFuncionariosPorTipo();
    }
  }
}

void TerminalUi::imprimirFuncionario(Funcionario *funcionario) {
  std::cout << "----------------------------------------\n";
  std::cout << "Codigo: " << funcionario->getCodigo() << "\n";
  std::cout << "Nome: " << funcionario->getNome() << "\n";
  std::cout << "Endereco: " << funcionario->getEndereco() << "\n";
  std::cout << "Telefone: " << funcionario->getTelefone() << "\n";
  std::cout << "Data de Ingresso: " << funcionario->getDataIngresso() << "\n";
  std::cout << "Designacao: " << funcionario->getDesig() << "\n";

  if (funcionario->getTipo() == 2) {
    std::cout << "Area de supervisao: " << dynamic_cast<Gerente *>(funcionario)->getSup()
              << "\n";
  } else if (funcionario->getTipo() == 3) {
    std::cout << "Area de supervisao: " << dynamic_cast<Diretor *>(funcionario)->getSup()
              << "\n";
    std::cout << "Area de formacao: " << dynamic_cast<Diretor *>(funcionario)->getForm()
              << "\n";
  } else if (funcionario->getTipo() == 4) {
    std::cout << "Area de formacao: "
              << dynamic_cast<Presidente *>(funcionario)->getForm() << "\n";
    std::cout << "Formacao academica maxima: "
              << dynamic_cast<Presidente *>(funcionario)->getMax() << "\n";
  }

  std::cout << "Salario: R$" << std::fixed << std::setprecision(2)
            << funcionario->getSalario() << "\n";

  std::cout << "----------------------------------------\n";
}

void TerminalUi::criarFuncionario() {
  Funcionario *funcionario;
  int codigo, tipo, dia, mes, ano;
  std::string nome, endereco, telefone, desig;
  float salario;

  std::cout << "Digite o codigo do funcionario: ";
  std::cin >> codigo;
  std::cin.ignore();

  std::cout << "Digite o nome do funcionario: ";
  std::getline(std::cin, nome);

  std::cout << "Digite o endereco do funcionario: ";
  std::getline(std::cin, endereco);

  std::cout << "Digite o telefone do funcionario: ";
  std::getline(std::cin, telefone);

  std::cout << "Digite o dia de ingresso: ";
  std::cin >> dia;
  std::cin.ignore();

  std::cout << "Digite o mes de ingresso: ";
  std::cin >> mes;
  std::cin.ignore();

  std::cout << "Digite o ano de ingresso: ";
  std::cin >> ano;
  std::cin.ignore();

  std::cout << "Digite o salario: ";
  std::cin >> salario;
  std::cin.ignore();

  std::cout << "Digite o tipo do funcionario: \n";
  std::cout << "1. Operador\n";
  std::cout << "2. Gerente\n";
  std::cout << "3. Diretor\n";
  std::cout << "4. Presidente\n";
  std::cout << "> ";
  std::cin >> tipo;
  std::cin.ignore();

  if (tipo == 1) {
    funcionario = new Funcionario(tipo);
  } else if (tipo == 2) {
    funcionario = new Gerente();
    std::string areaSup;

    std::cout << "Digite a area de supervisao: ";
    std::getline(std::cin, areaSup);

    dynamic_cast<Gerente *>(funcionario)->setSup(areaSup);
  } else if (tipo == 3) {
    funcionario = new Diretor();
    std::string areaSup;
    std::string areaForm;

    std::cout << "Digite a area de supervisao: ";
    std::getline(std::cin, areaSup);

    std::cout << "Digite a area de formacao: ";
    std::getline(std::cin, areaForm);

    dynamic_cast<Diretor *>(funcionario)->setSup(areaSup);
    dynamic_cast<Diretor *>(funcionario)->setForm(areaForm);
  } else if (tipo == 4) {
    funcionario = new Presidente();
    std::string areaFormacao, areaFormacaoMax;

    std::cout << "Digite a area de formacao: ";
    std::getline(std::cin, areaFormacao);

    std::cout << "Digite a area maxima de formacao academica: ";
    std::getline(std::cin, areaFormacaoMax);

    dynamic_cast<Presidente *>(funcionario)->setForm(areaFormacao);
    dynamic_cast<Presidente *>(funcionario)->setMax(areaFormacaoMax);
  }

  funcionario->setCodigo(codigo);
  funcionario->setNome(nome);
  funcionario->setEndereco(endereco);
  funcionario->setTelefone(telefone);
  funcionario->setDataIngresso(dia, mes, ano);
  funcionario->setSalario(salario);

  DatabaseManager::saveData(funcionario);
  delete funcionario;
}

void TerminalUi::atualizarFuncionario() {
  std::vector<Funcionario *> funcionarios = DatabaseManager::listData();

  Funcionario *funcionario;
  int codigo, tipo, dia, mes, ano;
  std::string nome, endereco, telefone, desig;
  float salario;

  std::cout << "Digite o codigo do funcionario a ser alterado: ";
  std::cin >> codigo;
  std::cin.ignore();

  for (size_t i = 0; i < funcionarios.size(); i++) {
    if (funcionarios[i]->getCodigo() == codigo) {
      funcionario = funcionarios[i];
      break;
    }
  }

  std::cout << "Digite o novo codigo do funcionario [-1 para nao alterar]: ";
  std::cin >> codigo;
  std::cin.ignore();

  if (codigo == -1) {
    codigo = funcionario->getCodigo();
  }

  std::cout << "Digite o nome do funcionario [Vazio para nao alterar]: ";
  std::getline(std::cin, nome);

  if (nome.empty()) {
    nome = funcionario->getNome();
  }

  std::cout << "Digite o endereco do funcionario [Vazio para nao alterar]: ";
  std::getline(std::cin, endereco);

  if (endereco.empty()) {
    endereco = funcionario->getEndereco();
  }

  std::cout << "Digite o telefone do funcionario [Vazio para nao alterar]: ";
  std::getline(std::cin, telefone);

  if (telefone.empty()) {
    telefone = funcionario->getTelefone();
  }

  std::vector<std::string> data =
      StringUtils::parseString(funcionario->getDataIngresso(), '/');

  std::cout << "Digite o dia de ingresso [-1 para nao alterar]: ";
  std::cin >> dia;
  std::cin.ignore();

  if (dia == -1) {
    dia = std::stoi(data[0]);
  }

  std::cout << "Digite o mes de ingresso [-1 para nao alterar]: ";
  std::cin >> mes;
  std::cin.ignore();

  if (mes == -1) {
    mes = std::stoi(data[1]);
  }

  std::cout << "Digite o ano de ingresso [-1 para nao alterar]: ";
  std::cin >> ano;
  std::cin.ignore();

  if (ano == -1) {
    ano = std::stoi(data[1]);
  }

  std::cout << "Digite o salario [-1 para nao alterar]: ";
  std::cin >> salario;
  std::cin.ignore();

  if (salario == -1) {
    salario = funcionario->getSalario();
  }

  std::cout << "Digite o tipo do funcionário [-1 para nao alterar]: \n";
  std::cout << "1. Operador\n";
  std::cout << "2. Gerente\n";
  std::cout << "3. Diretor\n";
  std::cout << "4. Presidente\n";
  std::cout << "> ";
  std::cin >> tipo;
  std::cin.ignore();

  if (tipo != -1) {
    if (funcionario->getTipo() == 1) {
      funcionario = new Funcionario(funcionario->getTipo());
    } else if (funcionario->getTipo() == 2) {
      funcionario = new Gerente();
      std::string areaSup;

      std::cout << "Digite a area de supervisao: ";
      std::getline(std::cin, areaSup);

      dynamic_cast<Gerente *>(funcionario)->setSup(areaSup);
    } else if (funcionario->getTipo() == 3) {
      funcionario = new Diretor();
      std::string areaSup;
      std::string areaForm;

      std::cout << "Digite a area de supervisao: ";
      std::getline(std::cin, areaSup);

      std::cout << "Digite a area de formacao: ";
      std::getline(std::cin, areaForm);

      dynamic_cast<Diretor *>(funcionario)->setSup(areaSup);
      dynamic_cast<Diretor *>(funcionario)->setForm(areaForm);
    } else if (funcionario->getTipo() == 4) {
      funcionario = new Presidente();
      std::string areaFormacao, areaFormacaoMax;

      std::cout << "Digite a area de formacao: ";
      std::getline(std::cin, areaFormacao);

      std::cout << "Digite a area maxima de formacao academica: ";
      std::getline(std::cin, areaFormacaoMax);

      dynamic_cast<Presidente *>(funcionario)->setForm(areaFormacao);
      dynamic_cast<Presidente *>(funcionario)->setMax(areaFormacaoMax);
    }
  } else {
    if (tipo == 2) {
      std::string areaSup;

      std::cout << "Digite a area de supervisao [Vazio para não alterar]: ";
      std::getline(std::cin, areaSup);

      if (areaSup.empty()) {
        areaSup = dynamic_cast<Gerente *>(funcionario)->getSup();
      }

      dynamic_cast<Gerente *>(funcionario)->setSup(areaSup);
    } else if (tipo == 3) {
      std::string areaSup;
      std::string areaForm;

      std::cout << "Digite a area de supervisao [Vazio para não alterar]: ";
      std::getline(std::cin, areaSup);

      if (areaSup.empty()) {
        areaSup = dynamic_cast<Diretor *>(funcionario)->getSup();
      }

      std::cout << "Digite a area de formacao [Vazio para não alterar]: ";
      std::getline(std::cin, areaForm);

      if (areaForm.empty()) {
        areaForm = dynamic_cast<Diretor *>(funcionario)->getForm();
      }

      dynamic_cast<Diretor *>(funcionario)->setSup(areaSup);
      dynamic_cast<Diretor *>(funcionario)->setForm(areaForm);
    } else if (tipo == 4) {
      std::string areaFormacao, areaFormacaoMax;

      std::cout << "Digite a area de formacao [Vazio para não alterar]: ";
      std::getline(std::cin, areaFormacao);

      if (areaFormacao.empty()) {
        areaFormacao = dynamic_cast<Presidente *>(funcionario)->getForm();
      }

      std::cout << "Digite a area maxima de formacao academica [Vazio para não "
                   "alterar]: ";
      std::getline(std::cin, areaFormacaoMax);

      if (areaFormacaoMax.empty()) {
        areaFormacaoMax = dynamic_cast<Presidente *>(funcionario)->getMax();
      }

      dynamic_cast<Presidente *>(funcionario)->setForm(areaFormacao);
      dynamic_cast<Presidente *>(funcionario)->setMax(areaFormacaoMax);
    }
  }

  funcionario->setCodigo(codigo);
  funcionario->setNome(nome);
  funcionario->setEndereco(endereco);
  funcionario->setTelefone(telefone);
  funcionario->setDataIngresso(dia, mes, ano);
  funcionario->setSalario(salario);

  DatabaseManager::updateData(funcionario);
  delete funcionario;
}

void TerminalUi::excluirFuncionario() {
  int codigoFuncionario;
  char resposta;

  std::cout << "Digite o codigo do funcionario para excluir: ";
  std::cin >> codigoFuncionario;
  std::cin.ignore();

  while (true) {
    std::cout << "Realmente deseja excluir esse funcionario [s/n]: ";
    std::cin >> resposta;
    std::cin.ignore();

    if (resposta == 's' || resposta == 'S' || resposta == 'n' ||
        resposta == 'N') {
      break;
    }

    std::cout << "Resposta invalida\n";
  }

  if (resposta == 's' || resposta == 'S') {
    DatabaseManager::deleteData(codigoFuncionario);
  }
}

void TerminalUi::exibirFuncionarios() {
  std::vector<Funcionario *> funcionarios = DatabaseManager::listData();

  for (Funcionario *funcionario : funcionarios) {
    this->imprimirFuncionario(funcionario);
  }

  for (size_t i = 0; i < funcionarios.size(); i++) {
    delete funcionarios[i];
  }
}

void TerminalUi::exibirFuncionariosPorTipo() {
  std::vector<Funcionario *> funcionarios = DatabaseManager::listData();
  int tipo;

  std::cout << "Digite o tipo que deseja listar: \n";
  std::cout << "1. Operador\n";
  std::cout << "2. Gerente\n";
  std::cout << "3. Diretor\n";
  std::cout << "4. Presidente\n";
  std::cin >> tipo;
  std::cin.ignore();

  for (Funcionario *funcionario : funcionarios) {
    if (funcionario->getTipo() == tipo) {
      this->imprimirFuncionario(funcionario);
    }
  }

  for (size_t i = 0; i < funcionarios.size(); i++) {
    delete funcionarios[i];
  }
}