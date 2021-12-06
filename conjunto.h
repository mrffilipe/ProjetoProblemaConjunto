#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <QString>

namespace minhaNamespace {

class Conjunto
{
private:
    int tamanho;
    int indiceDeUso;
    int *array;

    bool encontrarElemento(int elemento) const;
public:
    Conjunto(int tamanho);
    ~Conjunto();

    int getTamanho() const;
    int getIndiceDeUso() const;
    void setElemento(int elemento);
    QString getConjunto() const;
    Conjunto *uniao(Conjunto const * const objeto) const;
    Conjunto *intersecao(Conjunto const * const objeto) const;
    Conjunto *diferenca(Conjunto const * const objeto) const;
    int calcularAmplitude() const;
    float calcularMediaAritmetica() const;
    bool eSubConjunto(Conjunto const * const objeto) const;
    bool eIdentico(Conjunto const * const objeto) const;
    bool eDisjunto(Conjunto const * const objeto) const;
    bool eVazio() const;
};
}

#endif // CONJUNTO_H
