#ifndef MATRICULA_HPP
#define MATRICULA_HPP
#include <iostream>
#include <string>

#include "aluno.hpp"
#include "disciplina.hpp"

class Matricula {
   private:
    long anoLetivo;
    std::string serie;
    Aluno* aluno;
    Disciplina* disciplina;
    double nota1;
    double nota2;
    double nota3;
    double nota4;

   public:
    // Construtor
    Matricula(long ano, std::string serie, Aluno* aluno, Disciplina* disciplina, double nota1,
              double nota2, double nota3, double nota4);

    // Métodos de acesso (Getters)
    long getAnoLetivo() const;
    std::string getSerie() const;
    Aluno* getAluno() const;
    Disciplina* getDisciplina() const;
    double getNota1() const;
    double getNota2() const;
    double getNota3() const;
    double getNota4() const;

    // Métodos de modificação (Setters)
    void setAnoLetivo(long ano);
    void setSerie(std::string serie);
    void setAluno(const Aluno& aluno);
    void setDisciplina(const Disciplina& disciplina);
    void setNota1(double nota);
    void setNota2(double nota);
    void setNota3(double nota);
    void setNota4(double nota);

    void AppendToFile(const std::string& filename);
};

#endif  // MATRICULA_HPP
