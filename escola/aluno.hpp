#ifndef ALUNO_HPP
#define ALUNO_HPP

#include <fstream>
#include <string>
#include <vector>

class Aluno {
   private:
    int codigo;
    std::string nome;

   public:
    // Construtor
    Aluno(int codigo, const std::string& nome);

    // M�todos de acesso
    int getCodigo() const;
    std::string getNome() const;

    // M�todos de modifica��o
    void setCodigo(int codigo);
    void setNome(const std::string& nome);

    void appendToFile(const std::string& fileName);
};

#endif  // ALUNO_HPP
