/*
 * Metodología de la Programación: Kmer1
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
            throw invalid_argument(string("K no debe ser menor o igual a 0, k = " + to_string(k)));
        }
        else{
            _text="";
            for(int i = 0; i< k; i++){
                _text += MISSING_NUCLEOTIDE;
            }
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
    bool pertenece0;
    char c;
    for(int i=0; i<this->size(); i++){
        c = toString()[i];
        pertenece0 = IsValidNucleotide(c, validNucleotides);
        //Si el carácter no pertenece a validNucleotides:
        if(!pertenece0){
            _text.at(i) = MISSING_NUCLEOTIDE;
        }
    }
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const{
    Kmer complementarykmer;
    complementarykmer._text="";
    bool missingNucleotideBool = false;
    if(nucleotides.size() != complementaryNucleotides.size()){
        throw invalid_argument(string("Los argumentos pasados a complementary son incorrectos"));
    }
    else{
        for(int i = 0; i<getK(); i++){
            for(int j = 0; j<complementaryNucleotides.size();j++){
                if(nucleotides[j] == at(i)){
                    complementarykmer._text += complementaryNucleotides[j];
                    missingNucleotideBool = true;
                }
            }
            if (!missingNucleotideBool){
                complementarykmer._text += MISSING_NUCLEOTIDE;
            }
            missingNucleotideBool = false;
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
