#include "disciplina.hpp"

#include <fstream>

// Implementação dos métodos da classe Disciplina
Disciplina::Disciplina(int codigo, const std::string& nome, int cargaHoraria) {
    this->codigo = codigo;
    this->nome = nome;
    this->cargaHoraria = cargaHoraria;
}

int Disciplina::getCodigo() const {
    return codigo;
}

std::string Disciplina::getNome() const {
    return nome;
}

int Disciplina::getCargaHoraria() const {
    return cargaHoraria;
}

void Disciplina::setCodigo(int novoCodigo) {
    codigo = novoCodigo;
}

void Disciplina::setNome(const std::string& novoNome) {
    nome = novoNome;
}

void Disciplina::setCargaHoraria(int novaCargaHoraria) {
    cargaHoraria = novaCargaHoraria;
}

float Disciplina::calcularMedia(float nota1, float nota2, float nota3, float nota4) const {
    return (nota1 + nota2 + nota3 + nota4) / 4;
}

void Disciplina::appendToFile(const std::string& fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);

    file << '\n'
         << getCodigo() << ',' << getNome() << ',' << getCargaHoraria() << ',' << 0 << ',' << 0;

    file.close();
}

// Implementação dos métodos da classe DisciplinaPratica
DisciplinaPratica::DisciplinaPratica(int codigo, const std::string& nome, int cargaHoraria,
                                     int cargaHorariaPratica)
    : Disciplina(codigo, nome, cargaHoraria), cargaHorariaPratica(cargaHorariaPratica) {}

int DisciplinaPratica::getCargaHorariaPratica() const {
    return cargaHorariaPratica;
}

void DisciplinaPratica::setCargaHorariaPratica(int novaCargaHorariaPratica) {
    cargaHorariaPratica = novaCargaHorariaPratica;
}

float DisciplinaPratica::calcularMedia(float nota1, float nota2, float nota3, float nota4) const {
    return (nota1 + (nota2 * 2) + nota3 + (nota4 * 2)) / 6;
}

void DisciplinaPratica::appendToFile(const std::string& fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);

    file << '\n'
         << getCodigo() << ',' << getNome() << ',' << getCargaHoraria() << ',' << 1 << ','
         << getCargaHorariaPratica();

    file.close();
}
