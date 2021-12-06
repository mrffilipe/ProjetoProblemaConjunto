#include "conjunto.h"

namespace minhaNamespace {
Conjunto::Conjunto(int tamanho):
    tamanho(0),
    indiceDeUso(0),
    array(0)
{
    if(tamanho < 0) throw QString("O tamanho do conjunto não pode ser <= 0!");

    try {
        this->tamanho = tamanho;
        array = new int[tamanho];
    }  catch (std::bad_alloc const&) {
        throw QString("Erro na alocação de memória!");
    }
}

Conjunto::~Conjunto(){
    if(array) delete[] array;
}

int Conjunto::getTamanho() const
{
    return tamanho;
}

int Conjunto::getIndiceDeUso() const
{
    return indiceDeUso;
}

bool Conjunto::encontrarElemento(int elemento) const{
    for(int i = 0; i < this->indiceDeUso; i++){
        if(array[i] == elemento) return true;
    }
    return false;
}

void Conjunto::setElemento(int elemento) {
    if(this->indiceDeUso == this->tamanho) throw QString("O conjunto está em seu tamanho máximo definido!");

    if(encontrarElemento(elemento)) throw QString("O elemento já existe!");

    this->array[this->indiceDeUso] = elemento;
    this->indiceDeUso++;
}

QString Conjunto::getConjunto() const{
    QString saida = "[ ";

    for(int i = 0; i < this->indiceDeUso; i++){
        saida += QString::number(array[i]);
        if(i != indiceDeUso - 1) saida += ", ";
    }
    return saida += " ]";
}

Conjunto *Conjunto::uniao(Conjunto const * const objeto) const{
    try {
        int tamanho = this->indiceDeUso + objeto->indiceDeUso;

        Conjunto *aux = new Conjunto(tamanho);

        for(int i = 0; i < this->indiceDeUso; i++){
            aux->array[i] = this->array[i];
        }

        aux->indiceDeUso = this->indiceDeUso;
        for(int i = 0; i < objeto->indiceDeUso; i++){
            if(!this->encontrarElemento(objeto->array[i])){
                aux->array[aux->indiceDeUso] = objeto->array[i];
                aux->indiceDeUso++;
            }
        }
        return aux;
    }  catch (std::bad_alloc const&) {
        throw QString("Erro na alocação de memória!");
    }
}

Conjunto *Conjunto::intersecao(Conjunto const * const objeto) const{
    try {
        int tamanho = objeto->indiceDeUso;

        if(this->indiceDeUso < objeto->indiceDeUso) tamanho = this->indiceDeUso;

        Conjunto *aux = new Conjunto(tamanho);

        for(int i = 0; i < this->indiceDeUso; i++){
            for(int j = 0; j < objeto->indiceDeUso; j++){
                if(this->array[i] == objeto->array[j]){
                    aux->array[aux->indiceDeUso] = objeto->array[j];
                    aux->indiceDeUso++;
                }
            }
        }
        return aux;
    }  catch (std::bad_alloc const&) {
        throw QString("Erro na alocação de memória!");
    }
}

Conjunto *Conjunto::diferenca(Conjunto const * const objeto) const{
    try {
        int tamanho = this->indiceDeUso;

        Conjunto *aux = new Conjunto(tamanho);

        for(int i = 0; i < this->indiceDeUso; i++){
            if(!objeto->encontrarElemento(this->array[i])){
                aux->array[aux->indiceDeUso] = this->array[i];
                aux->indiceDeUso++;
            }
        }
        return aux;
    }  catch (std::bad_alloc const&) {
        throw QString("Erro na alocação de memória!");
    }
}

float Conjunto::calcularMediaAritmetica() const{
    int contagem = 0;
    for(int i = 0; i < this->indiceDeUso; i++){
        contagem += this->array[i];
    }
    return contagem/this->indiceDeUso;
}

int Conjunto::calcularAmplitude() const{
    int maiorElemento = this->array[0];
    int menorElemento = this->array[0];
    for(int i = 0; i < this->indiceDeUso; i++){
        if(this->array[i] > maiorElemento) maiorElemento = this->array[i];
        if(this->array[i] < menorElemento) menorElemento = this->array[i];
    }
    return maiorElemento - menorElemento; // checar quando o menor for negativo
}

bool Conjunto::eSubConjunto(Conjunto const * const objeto) const{
    if(this->indiceDeUso > objeto->indiceDeUso) return false;

    for(int i = 0; i < this->indiceDeUso; i++){
        if(!(this->intersecao(objeto)->encontrarElemento(this->array[i]))) return false;;
    }
    return true;
}

bool Conjunto::eIdentico(Conjunto const * const objeto) const{
    if(this->indiceDeUso != objeto->indiceDeUso) return false;

    for(int i = 0; i < this->indiceDeUso; i++){
        if(!(this->encontrarElemento(objeto->array[i]))) return false;;
    }
    return true;
}

bool Conjunto::eDisjunto(const Conjunto *const objeto) const{
    for(int i = 0; i < this->indiceDeUso; i++){
        if(this->encontrarElemento(objeto->array[i])) return false;
    }
    return true;
}

bool Conjunto::eVazio() const{
    if(this->indiceDeUso == 0) return true;
    return false;
}

}
