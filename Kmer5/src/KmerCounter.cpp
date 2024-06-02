/*
 * Metodología de la Programación: Kmer5
 * Curso 2023/2024
 */

/** 
 * @file KmerCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 22 December 2023, 10:00
 */

#include "KmerCounter.h"
#include <cmath>
using namespace std;

/**
 * DEFAULT_VALID_NUCLEOTIDES is a c-string that contains the set of characters
 * that will be considered as valid nucleotides. 

 * The constructor of the class KmerCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const KmerCounter::DEFAULT_VALID_NUCLEOTIDES="ACGT";

std::string KmerCounter::toString() const{
    string outputString = _allNucleotides + " " + to_string(_k) + "\n";
    
    for(int row=0; row<this->getNumRows(); row++){
        for(int col=0; col<this->getNumCols(); col++){
            outputString += to_string((*this)(row,col)) + " ";
        }
        outputString += "\n";
    }
    
    return outputString;
}

int KmerCounter::getIndex(const std::string& kmer) const{
    int index = 0;
    int base = 1;

    for (size_t i = 0; i < kmer.size(); i++) {
        size_t pos = _allNucleotides.find(kmer[kmer.size()-i-1]);
        if (pos == string::npos)
            return -1;
        index += pos * base;
        base *= _allNucleotides.size();
    }
    return index;
}

string KmerCounter::getInvertedIndex(int index, int nCharacters) const {
    string result(nCharacters, Kmer::MISSING_NUCLEOTIDE);

    for (int i = result.size(); i > 0; i--) {
        result[i - 1] = _allNucleotides[index % _allNucleotides.size()];
        index = index / _allNucleotides.size();
    }
    return result;
}

KmerCounter::KmerCounter(const int k=5, 
       const std::string validNucleotides = DEFAULT_VALID_NUCLEOTIDES){
    this->_k = k;
    this->_validNucleotides = validNucleotides;
    this->_allNucleotides = Kmer::MISSING_NUCLEOTIDE + validNucleotides;
    int** _frequency = new int[k];
    _frequency[0] = new int[k*k];
    for(int i = 1; i<k; i++){
        _frequency[i] = _frequency[i-1]+k;
    }
    for(int i = 0; i<k; i++){
        for(int j = 0; j<k; j++){
            _frequency[i][j] =0;
        }
    }
}
KmerCounter::KmerCounter(const KmerCounter &orig){
    *this = orig;
}
KmerCounter::~KmerCounter(){
    delete[] this->_frequency[0];
    delete[] _frequency;
}
const int KmerCounter::getNumNucleotides() const{
    return _allNucleotides.size();
}
const int KmerCounter::getK() const{
    return _k;
}
const int KmerCounter::getNumKmers() const{
    return pow(getNumNucleotides(),getK());
}
const int KmerCounter::getNumberActiveKmers(int &aux) const{
    for(int i =0; i<getK(); i++){
        for(int j= 0 0; j<getK(); j++){
            if(_frequency[i][j] > 0)
                aux++;
        }
    }
    return aux;
}
void KmerCounter::increaseFrequency(const Kmer kmer,const int frequency = 1){
    
}
const int KmerCounter::getNumRows() const{
    return pow(getNumNucleotides(),(static_cast<float>(getK()+1))/2);
}
const int KmerCounter::getNumCols() const{
    return pow(getNumNucleotides(),getK()-((static_cast<float>(getK()+1))/2));
}
void KmerCounter::getRowColumn(const Kmer kmer, int row, int column){
    row = column = 0;
    int pos = getIndex(kmer.toString());
    while(pos> getK()){
        column++;
        pos-= getNumNucleotides();
    };
    row = pos;
}