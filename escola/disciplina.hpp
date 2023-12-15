#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include <fstream>
#include <string>

class Disciplina {
   private:
    int codigo;
    std::string nome;
    int cargaHoraria;

   public:
    // Construtor
    Disciplina(int codigo, const std::string& nome, int cargaHoraria);

    // M�todos p�blicos para acessar e modificar os atributos
    int getCodigo() const;
    std::string getNome() const;
    int getCargaHoraria() const;
    void setCodigo(int novoCodigo);
    void setNome(const std::string& novoNome);
    void setCargaHoraria(int novaCargaHoraria);

    // M�todo para calcular a m�dia
    virtual float calcularMedia(float nota1, float nota2, float nota3, float nota4) const;
    void appendToFile(const std::string& fileName);
};

class DisciplinaPratica : public Disciplina {
   private:
    int cargaHorariaPratica;

   public:
    // Construtor
    DisciplinaPratica(int codigo, const std::string& nome, int cargaHoraria,
                      int cargaHorariaPratica);

    // M�todo p�blico para acessar o atributo espec�fico da subclasse
    int getCargaHorariaPratica() const;

    // M�todo p�blico para modificar o atributo espec�fico da subclasse
    void setCargaHorariaPratica(int novaCargaHorariaPratica);
    // M�todo para calcular a m�dia da pratica
    float calcularMedia(float nota1, float nota2, float nota3, float nota4) const override;

    void appendToFile(const std::string& fileName);
};

#endif  // DISCIPLINA_HPP
