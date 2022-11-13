#ifndef FILE_UTIL_HPP
#define FILE_UTIL_HPP

#include <string>
#include <vector>

#include "Funcionario.h"

#define FILE_NAME "data.csv"

class DatabaseManager {
 private:
  // Variável estática e constante para o nome do arquivo
  static const std::string FUNCIONARIO_FILENAME;
  static const std::string GERENTE_FILENAME;
  static const std::string DIRETOR_FILENAME;
  static const std::string PRESIDENTE_FILENAME;

  /**
    Função para criar o cabeçalho para o arquivo
  */
  static void initializeData();

  /// @brief Verifica se um arquivo existe ou não
  /// @param filePath Caminho do arquivo para ser verificado
  /// @return Retorna true se o arquivo existir e false se não existir
  static bool checkIfFileExists(std::string filePath);

 public:
  /**
    Função para salvar um funcionário no arquivo

    @param funcionario Funcionário para ser salvo
  */
  static void saveData(
      Funcionario *funcionario,
      std::string filename = DatabaseManager::FUNCIONARIO_FILENAME);

  /**
    Função para listar todos os funcionários do arquivo

    @return Retorna um vetor com todos os funcionários salvos
  */
  static std::vector<Funcionario *> listData();

  /**
    Função para atualizar um funcionário no arquivo.
    Essa função atualiza o funcionário que tiver o mesmo código
    do funcionário enviado como parâmetro

    @param funcionario Funcionário e seus dados para ser atualizado
  */
  static void updateData(Funcionario *funcionario);

  /**
    Função para deletar um funcionário no arquivo

    @param codigoFuncionario O código do funcionário para ser deletado
  */
  static void deleteData(int codigoFuncionario);
};

#endif  // !FILE_UTIL_HPP
