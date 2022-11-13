#ifndef TERMINALUI_HPP
#define TERMINALUI_HPP

#include "Funcionario.h"

class TerminalUi {
 private:
  void imprimirFuncionario(Funcionario *funcionario);

 public:
  TerminalUi();

  void criarFuncionario();
  void atualizarFuncionario();
  void excluirFuncionario();
  void exibirFuncionarios();
  void exibirFuncionariosPorTipo();
};

#endif