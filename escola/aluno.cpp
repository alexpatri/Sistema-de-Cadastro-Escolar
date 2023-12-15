#include "aluno.hpp"

// Construtor
Aluno::Aluno(int codigo, const std::string& nome) : codigo(codigo), nome(nome) {}

// Métodos de acesso
int Aluno::getCodigo() const {
    return codigo;
}

std::string Aluno::getNome() const {
    return nome;
}

// Métodos de modificação
void Aluno::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Aluno::setNome(const std::string& nome) {
    this->nome = nome;
}

void Aluno::appendToFile(const std::string& fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);

    file << '\n' << getCodigo() << ',' << getNome();

    file.close();
}
