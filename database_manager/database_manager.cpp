#include "database_manager.hpp"

#include <sys/stat.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "Diretor.h"
#include "Gerente.h"
#include "Presidente.h"
#include "string_utils.hpp"

const std::string DatabaseManager::FUNCIONARIO_FILENAME = "funcionarios.csv";
const std::string DatabaseManager::GERENTE_FILENAME = "gerente.csv";
const std::string DatabaseManager::DIRETOR_FILENAME = "diretor.csv";
const std::string DatabaseManager::PRESIDENTE_FILENAME = "presidente.csv";

void DatabaseManager::initializeData() {
  std::ofstream dataFile;

  if (!checkIfFileExists(DatabaseManager::FUNCIONARIO_FILENAME)) {
    dataFile.open(DatabaseManager::FUNCIONARIO_FILENAME);

    if (!dataFile.is_open()) {
      return;
    }

    dataFile << "codigo,nome,endereco,telefone,dataIngresso,designacao,salario";

    dataFile.close();
  }

  if (!checkIfFileExists(DatabaseManager::GERENTE_FILENAME)) {
    dataFile.open(DatabaseManager::GERENTE_FILENAME);

    if (!dataFile.is_open()) {
      return;
    }

    dataFile << "codigo,supervisao";

    dataFile.close();
  }

  if (!checkIfFileExists(DatabaseManager::DIRETOR_FILENAME)) {
    dataFile.open(DatabaseManager::DIRETOR_FILENAME);

    if (!dataFile.is_open()) {
      return;
    }

    dataFile << "codigo,supervisao,formacao";

    dataFile.close();
  }

  if (!checkIfFileExists(DatabaseManager::PRESIDENTE_FILENAME)) {
    dataFile.open(DatabaseManager::PRESIDENTE_FILENAME);

    if (!dataFile.is_open()) {
      return;
    }

    dataFile << "codigo,formacao,formacao_max";

    dataFile.close();
  }
}

bool DatabaseManager::checkIfFileExists(std::string filePath) {
  struct stat buffer;
  return (stat(filePath.c_str(), &buffer) == 0);
}

void DatabaseManager::saveData(Funcionario *funcionario, std::string filename) {
  DatabaseManager::initializeData();

  // Arquivo será aberto como append
  std::ofstream dataFile(filename, std::ios::app);

  if (!dataFile.is_open()) {
    return;
  }

  if (funcionario->getTipo() == 2) {
    Gerente *gerente = dynamic_cast<Gerente *>(funcionario);

    std::ofstream gerenteFile(DatabaseManager::GERENTE_FILENAME, std::ios::app);

    if (!gerenteFile.is_open()) {
      return;
    }

    gerenteFile << "\n" << gerente->getCodigo() << "," << gerente->getSup();

    gerenteFile.close();
  } else if (funcionario->getTipo() == 3) {
    Diretor *diretor = dynamic_cast<Diretor *>(funcionario);

    std::ofstream diretorFile(DatabaseManager::DIRETOR_FILENAME, std::ios::app);

    if (!diretorFile.is_open()) {
      return;
    }

    diretorFile << "\n"
                << diretor->getCodigo() << "," << diretor->getSup()
                << diretor->getForm();

    diretorFile.close();
  } else if (funcionario->getTipo() == 4) {
    Presidente *presidente = dynamic_cast<Presidente *>(funcionario);

    std::ofstream presidenteFile(DatabaseManager::PRESIDENTE_FILENAME,
                                 std::ios::app);

    if (!presidenteFile.is_open()) {
      return;
    }

    presidenteFile << "\n"
                   << presidente->getCodigo() << "," << presidente->getForm()
                   << "," << presidente->getMax();

    presidenteFile.close();
  }

  dataFile << "\n"
           << funcionario->getCodigo() << "," << funcionario->getNome() << ","
           << funcionario->getEndereco() << "," << funcionario->getTelefone()
           << "," << funcionario->getDataIngresso() << ","
           << funcionario->getTipo() << "," << funcionario->getSalario();

  dataFile.close();
}

std::vector<Funcionario *> DatabaseManager::listData() {
  Funcionario *funcionario;

  DatabaseManager::initializeData();

  std::ifstream dataFile(DatabaseManager::FUNCIONARIO_FILENAME);
  std::string actualLine;
  std::vector<Funcionario *> funcionarios;

  if (!dataFile.is_open()) {
    return funcionarios;
  }

  bool isHeader = true;
  while (true) {
    std::getline(dataFile, actualLine);

    // O cabeçalho será pulado
    if (isHeader) {
      isHeader = false;
      continue;
    }

    std::vector<std::string> data = StringUtils::parseString(actualLine);

    int tipo = std::stoi(data[5]);
    int codigo = std::stoi(data[0]);

    if (tipo == 1) {
      funcionario = new Funcionario(tipo);
    } else if (tipo == 2) {
      funcionario = new Gerente();

      std::ifstream gerenteFile(DatabaseManager::GERENTE_FILENAME);
      std::string buffer;

      bool header = true;
      while (true) {
        getline(gerenteFile, buffer);

        if (header) {
          header = false;
          continue;
        }

        std::vector<std::string> gerenteDados =
            StringUtils::parseString(buffer);

        if (std::stoi(gerenteDados[0]) == codigo) {
          dynamic_cast<Gerente *>(funcionario)->setSup(gerenteDados[1]);
          break;
        }

        if (gerenteFile.eof()) {
          break;
        }
      }

      gerenteFile.close();
    } else if (tipo == 3) {
      funcionario = new Diretor();

      std::ifstream diretorFile(DatabaseManager::DIRETOR_FILENAME);
      std::string buffer;

      bool header = true;
      while (true) {
        getline(diretorFile, buffer);

        if (header) {
          header = false;
          continue;
        }

        std::vector<std::string> diretorDados =
            StringUtils::parseString(buffer);

        if (std::stoi(diretorDados[0]) == codigo) {
          dynamic_cast<Diretor *>(funcionario)->setSup(diretorDados[1]);
          dynamic_cast<Diretor *>(funcionario)->setForm(diretorDados[2]);
          break;
        }

        if (diretorFile.eof()) {
          break;
        }
      }

      diretorFile.close();
    } else if (tipo == 4) {
      funcionario = new Presidente();

      std::ifstream presidenteFile(DatabaseManager::PRESIDENTE_FILENAME);
      std::string buffer;

      bool header = true;
      while (true) {
        getline(presidenteFile, buffer);

        if (header) {
          header = false;
          continue;
        }

        std::vector<std::string> presidenteDados =
            StringUtils::parseString(buffer);

        if (std::stoi(presidenteDados[0]) == codigo) {
          dynamic_cast<Presidente *>(funcionario)->setForm(presidenteDados[1]);
          dynamic_cast<Presidente *>(funcionario)->setMax(presidenteDados[2]);
          break;
        }

        if (presidenteFile.eof()) {
          break;
        }
      }

      presidenteFile.close();
    }

    funcionario->setCodigo(codigo);
    funcionario->setNome(data[1]);
    funcionario->setEndereco(data[2]);
    funcionario->setTelefone(data[3]);
    funcionario->setDataIngresso(data[4]);
    funcionario->setTipo(tipo);
    funcionario->setSalario(std::stof(data[6]));

    funcionarios.push_back(funcionario);

    if (dataFile.eof()) {
      break;
    }
  }

  dataFile.close();

  return funcionarios;
}

void DatabaseManager::updateData(Funcionario *funcionario, int codigo) {
  std::vector<Funcionario *> funcionariosCadastrados =
      DatabaseManager::listData();

  for (size_t i = 0; i < funcionariosCadastrados.size(); i++) {
    if (funcionariosCadastrados[i]->getCodigo() != codigo) {
      continue;
    }

    if (funcionario->getTipo() == 1) {
      funcionariosCadastrados[i] = new Funcionario();
    } else if (funcionario->getTipo() == 2) {
      funcionariosCadastrados[i] = new Gerente();

      dynamic_cast<Gerente *>(funcionariosCadastrados[i])
          ->setSup(dynamic_cast<Gerente *>(funcionario)->getSup());
    } else if (funcionario->getTipo() == 3) {
      funcionariosCadastrados[i] = new Diretor();

      dynamic_cast<Diretor *>(funcionariosCadastrados[i])
          ->setSup(dynamic_cast<Diretor *>(funcionario)->getSup());
      dynamic_cast<Diretor *>(funcionariosCadastrados[i])
          ->setForm(dynamic_cast<Diretor *>(funcionario)->getForm());
    } else if (funcionario->getTipo() == 4) {
      funcionariosCadastrados[i] = new Presidente();

      dynamic_cast<Presidente *>(funcionariosCadastrados[i])
          ->setForm(dynamic_cast<Presidente *>(funcionario)->getForm());
      dynamic_cast<Presidente *>(funcionariosCadastrados[i])
          ->setMax(dynamic_cast<Presidente *>(funcionario)->getMax());
    }

    funcionariosCadastrados[i]->setCodigo(codigo);
    funcionariosCadastrados[i]->setNome(funcionario->getNome());
    funcionariosCadastrados[i]->setDataIngresso(funcionario->getDataIngresso());
    funcionariosCadastrados[i]->setEndereco(funcionario->getEndereco());
    funcionariosCadastrados[i]->setSalario(funcionario->getSalario());
    funcionariosCadastrados[i]->setTelefone(funcionario->getTelefone());
    funcionariosCadastrados[i]->setTipo(funcionario->getTipo());
  }

  remove(DatabaseManager::FUNCIONARIO_FILENAME.c_str());
  remove(DatabaseManager::DIRETOR_FILENAME.c_str());
  remove(DatabaseManager::GERENTE_FILENAME.c_str());
  remove(DatabaseManager::PRESIDENTE_FILENAME.c_str());

  for (Funcionario *f : funcionariosCadastrados) {
    DatabaseManager::saveData(f);
  }
}

void DatabaseManager::deleteData(int codigoFuncionario) {
  std::vector<Funcionario *> funcionariosCadastrados =
      DatabaseManager::listData();
  int index = -1;

  for (size_t i = 0; i < funcionariosCadastrados.size(); i++) {
    if (funcionariosCadastrados[i]->getCodigo() == codigoFuncionario) {
      if (funcionariosCadastrados[i]->getTipo() == 3 ||
          funcionariosCadastrados[i]->getTipo() == 4) {
        std::cerr << "Nao e permitido deletar um gerente ou presidente\n";
        break;
      }
      index = i;
      break;
    }
  }

  if (index != -1) {
    funcionariosCadastrados.erase(funcionariosCadastrados.begin() + index);

    remove(DatabaseManager::FUNCIONARIO_FILENAME.c_str());
    remove(DatabaseManager::DIRETOR_FILENAME.c_str());
    remove(DatabaseManager::GERENTE_FILENAME.c_str());
    remove(DatabaseManager::PRESIDENTE_FILENAME.c_str());

    for (Funcionario *f : funcionariosCadastrados) {
      DatabaseManager::saveData(f);
    }
  }
}
