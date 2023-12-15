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

    // Métodos públicos para acessar e modificar os atributos
    int getCodigo() const;
    std::string getNome() const;
    int getCargaHoraria() const;
    void setCodigo(int novoCodigo);
    void setNome(const std::string& novoNome);
    void setCargaHoraria(int novaCargaHoraria);

    // Método para calcular a média
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

    // Método público para acessar o atributo específico da subclasse
    int getCargaHorariaPratica() const;

    // Método público para modificar o atributo específico da subclasse
    void setCargaHorariaPratica(int novaCargaHorariaPratica);
    // Método para calcular a média da pratica
    float calcularMedia(float nota1, float nota2, float nota3, float nota4) const override;

    void appendToFile(const std::string& fileName);
};

#endif  // DISCIPLINA_HPP
