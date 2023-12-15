#include "matricula.hpp"

#include <iostream>
#include <string>
// Construtor
Matricula::Matricula(long ano, std::string serie, Aluno* aluno, Disciplina* disciplina,
                     double nota1, double nota2, double nota3, double nota4) {
    this->anoLetivo = ano;
    this->serie = serie;
    this->aluno = aluno;
    this->disciplina = disciplina;
    this->nota1 = nota1;
    this->nota2 = nota2;
    this->nota3 = nota3;
    this->nota4 = nota4;
}

// Métodos de acesso (Getters)
long Matricula::getAnoLetivo() const {
    return anoLetivo;
}

std::string Matricula::getSerie() const {
    return serie;
}

Aluno* Matricula::getAluno() const {
    return aluno;
}

Disciplina* Matricula::getDisciplina() const {
    return disciplina;
}

double Matricula::getNota1() const {
    return nota1;
}

double Matricula::getNota2() const {
    return nota2;
}

double Matricula::getNota3() const {
    return nota3;
}

double Matricula::getNota4() const {
    return nota4;
}

// Métodos de modificação (Setters)
void Matricula::setAnoLetivo(long ano) {
    anoLetivo = ano;
}

void Matricula::setSerie(std::string serie) {
    this->serie = serie;
}

void Matricula::setAluno(const Aluno& aluno) {
    this->aluno = new Aluno(aluno);
}

void Matricula::setDisciplina(const Disciplina& disciplina) {
    this->disciplina = new Disciplina(disciplina);
}

void Matricula::setNota1(double nota) {
    nota1 = nota;
}

void Matricula::setNota2(double nota) {
    nota2 = nota;
}

void Matricula::setNota3(double nota) {
    nota3 = nota;
}

void Matricula::setNota4(double nota) {
    nota4 = nota;
}

void Matricula::AppendToFile(const std::string& filename) {
    std::ofstream file;
    file.open(filename, std::ios::app);

    file << '\n'
         << getAluno()->getCodigo() << "," << getDisciplina()->getCodigo() << "," << getAnoLetivo()
         << "," << getSerie() << "," << getNota1() << "," << getNota2() << "," << getNota3() << ","
         << getNota4();

    file.close();
};
