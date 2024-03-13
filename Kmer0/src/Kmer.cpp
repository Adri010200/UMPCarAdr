/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 24 October 2023, 14:00
 */

#include "Kmer.h"
using namespace std;

Kmer::Kmer(int k){
        if(k<=0){
            throw invalid_argument("K no debe ser menor a 0");
        }
        else{
            this->_text="";
            for(int i = 0; i< k; i++){
                this->_text += this->MISSING_NUCLEOTIDE;
            }
        }
    }
Kmer::Kmer(const string& text){
    if(text.size() == 0){
        throw invalid_argument("El texto pasado no debe estar vacío");
    }
    else{
        this->_text = text;
    }
}
int Kmer::getK() const{
    return this->toString().size();
}
int Kmer::size() const{
    return this->toString().size();
}
string Kmer::toString() const{
    return this->_text;
}

const char& Kmer::at(int index) const{
    if(index >= 0 && index <= this->getK()-1){
        const char& c = this->toString().at(index);
        return c;
    }
    else{
        throw out_of_range("El índice buscado debe estar entre 0 y la longitud del string");
    }
}
char& Kmer::at(int index){
    if(index >= 0 && index <= this->getK()-1){
        char& c = this->toString().at(index);
        return c;
    }
    else{
        throw out_of_range("El índice buscado debe estar entre 0 y la longitud del string");
    }
}
void Kmer::normalize(const std::string& validNucleotides){
    //Poner todos los caracteres en mayúscula
    ToUpper(*this);
    //Sustituir por _
    bool pertenece0;
    char c;
    for(int i=0; i<this->size(); i++){
        c = this->toString()[i];
        pertenece0 = IsValidNucleotide(c, validNucleotides);
        //Si el carácter no pertenece a validNucleotides:
        if(!pertenece0){
            _text[i] = MISSING_NUCLEOTIDE;
        }
    }
}
Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const{
    Kmer complementarykmer;
    complementarykmer._text="";
    if(nucleotides.size() != complementaryNucleotides.size()){
        throw invalid_argument("Los argumentos pasados a complementary son incorrectos");
    }
    else{
        for(int i = 0; i<this->getK(); i++){
            for(int j = 0; j<complementaryNucleotides.size();j++){
                if(nucleotides[j] == this->at(i)){
                    complementarykmer._text += complementaryNucleotides[j];
                }
            }
        }
    }
    return complementarykmer;
}
bool IsValidNucleotide(char nucleotide, const string& validNucleotides){
    bool pertenece=false;
    int s = validNucleotides.size();
        for(int j =0; j< s; j++){
            if(nucleotide == validNucleotides[j]){
                pertenece=true;
            }
        }
    return pertenece;
}
void ToUpper(Kmer& kmer){
    for(int i=0; i< kmer.toString().size(); i++){
        //La diferencia entre una letra y su mayúscula en ASCII es 32
        if(kmer.at(i) >= 'a' && kmer.at(i) <= 'z'){
            kmer.set(i, kmer.at(i) -32);
        }
        else{
            kmer.set(i, kmer.at(i));
        }
    }
}

void ToLower(Kmer& kmer){
    for(int i=0; i< kmer.toString().size(); i++){
        //La diferencia entre una letra y su mayúscula en ASCII es 32
        if(kmer.at(i) >= 'A' && kmer.at(i) <= 'Z'){
            kmer.set(i, kmer.at(i) +32);
        }
        else{
            kmer.set(i, kmer.at(i));
        }
    }
}

/*Método añadido por necesidad*/
void Kmer::set(int index, char caracter){
    this->_text[index] = caracter;
}