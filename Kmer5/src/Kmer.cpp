/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 */

#include "Kmer.h"
using namespace std;

Kmer::Kmer(int k){
        if(k<=0){
            throw invalid_argument(string("K no debe ser menor o igual a 0, k = " + to_string(k)));
        }
        else{
            _text = string(k, MISSING_NUCLEOTIDE);
        }
    }

Kmer::Kmer(const string& text){
    if(text.size() == 0){
        throw invalid_argument(string("El texto pasado no debe estar vacío"));
    }
    else{
        _text = text;
    }
}

int Kmer::getK() const{
    return size();
}

int Kmer::size() const{
    return _text.size();
}

string Kmer::toString() const{
    return _text;
}

const char& Kmer::at(int index) const{
    if(index >= 0 && index <= this->getK()-1){
        return this -> _text.at(index);
    }
    else{
        throw out_of_range(string("El índice buscado debe estar entre 0 y la longitud del string"));
    }
}

char& Kmer::at(int index){
    if(index >= 0 && index <= this->getK()-1){
        return this->_text.at(index);
    }
    else{
        throw out_of_range(string("El índice buscado debe estar entre 0 y la longitud del string"));
    }
}

void Kmer::normalize(const std::string& validNucleotides){
    //Poner todos los caracteres en mayúscula
    ToUpper(*this);
    //Sustituir por _
    for(int i=0; i<this->size(); i++){
        //Si el carácter no pertenece a validNucleotides:
        if(!IsValidNucleotide(_text[i], validNucleotides)){
            at(i) = MISSING_NUCLEOTIDE;
        }
    }
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const{
    Kmer complementarykmer;
    bool missingNucleotideBool = false;
    if(nucleotides.size() != complementaryNucleotides.size()){
        throw invalid_argument(string("Los argumentos pasados a complementary son incorrectos"));
    }
    else{
        for(int i = 0; i<getK(); i++){
            for(int j = 0; j<complementaryNucleotides.size();j++){
                if(nucleotides[j] == at(i)){
                    complementarykmer.at(i) = complementaryNucleotides[j];
                    missingNucleotideBool = true;
                }
            }
            if (!missingNucleotideBool){
                complementarykmer.at(i) = MISSING_NUCLEOTIDE;
            }
            missingNucleotideBool = false;
        }
    }
    return complementarykmer;
}

bool IsValidNucleotide(char nucleotide, const string& validNucleotides){
    for(int j =0; j< validNucleotides.size(); j++){
        if(nucleotide == validNucleotides[j]){
            return true;
        }
    }
    return false;
}

void ToUpper(Kmer& kmer){
    
    for(int i = 0; i<kmer.size(); i++){
        char v = toupper(kmer.at(i));
        kmer.at(i)=v;
    }
    
}

void ToLower(Kmer& kmer){
     for(int i = 0; i<kmer.size(); i++){
        char v = tolower(kmer.at(i));
        kmer.at(i)=v;
    }
}
void Kmer::toLower(){
    ToLower(*this);
}
void Kmer::toUpper(){
    ToUpper(*this);
}