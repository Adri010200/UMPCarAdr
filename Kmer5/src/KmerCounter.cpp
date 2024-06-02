/*
 * Metodología de la Programación: Kmer5
 * Curso 2023/2024
 */

/** 
 * @file Profile.h
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
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

KmerCounter::KmerCounter(const int k, 
       const std::string validNucleotides){
    this->_k = k;
    this->_validNucleotides = validNucleotides;
    this->_allNucleotides = Kmer::MISSING_NUCLEOTIDE + validNucleotides;
    
    allocate();
    initFrequencies();
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
int KmerCounter::getK() const{
    return _k;
}
const int KmerCounter::getNumKmers() const{
    return pow(getNumNucleotides(),getK());
}
const int KmerCounter::getNumberActiveKmers() const{
    int aux;
    for(int i =0; i<getK(); i++){
        for(int j= 0; j<getK(); j++){
            if(_frequency[i][j] > 0)
                aux++;
        }
    }
    return aux;
}
void KmerCounter::increaseFrequency(const Kmer kmer,const int frequency){
    int auxrow, auxcol;
    getRowColumn(kmer, auxrow, auxcol);
    _frequency[auxrow][auxcol] += frequency;
}
const int KmerCounter::getNumRows() const{
    if(getK()%2 != 0)
        return pow(getNumNucleotides(),(getK()+1)/2);
    else
        return pow(getNumNucleotides(),getK()/2);
}
const int KmerCounter::getNumCols() const{
    if(getK()%2 != 0)
        return pow(getNumNucleotides(),(getK()-1)/2);
    else
        return pow(getNumNucleotides(),getK()/2);
}
void KmerCounter::getRowColumn(const Kmer kmer, int& row, int& column) const{
    row = column = 0;
    int pos = getIndex(kmer.toString());
    while(pos> getNumCols()){
        column++;
        pos-= getNumCols();
    };
    row = pos;
}
KmerCounter& KmerCounter::operator=(const KmerCounter& orig){
    if(this != &orig){
        delete[] this->_frequency[0];
        delete[] _frequency;
        _k= orig.getK();
        _validNucleotides = orig._validNucleotides;
        _allNucleotides = orig._allNucleotides;
        allocate();
        for(int i = 0; i<getNumRows(); i++){
            for(int j = 0; j<getNumCols(); j++){
                _frequency[i][j] = orig._frequency[i][j];
            }
        }
    }
    return *this;
}
void KmerCounter::allocate(){
    int** _frequency = new int*[getNumRows()];
    _frequency[0] = new int[getNumKmers()];
    for(int i = 1; i<getNumRows(); i++){
        _frequency[i] = _frequency[i-1] + getNumCols();
    }
}
KmerCounter& KmerCounter::operator+=(const KmerCounter& kc){
    for(int i = 0; i<getNumRows(); i++){
        for(int j = 0; j<getNumCols(); j++){
            _frequency[i][j] += kc(i,j);
        }
    }
}
const Kmer KmerCounter::getKmer(const int row,const int column) const{
    int index = row*getNumCols() + column;
    string s = getInvertedIndex(index,getK());
    return Kmer(s);
}
void KmerCounter::initFrequencies(){
    for(int i = 0; i<getNumRows(); i++){
        for(int j = 0; j<getNumCols(); j++){
            _frequency[i][j] =0;
        }
    }
}
const int KmerCounter::operator()(int row, int column) const{
    return _frequency[row][column];
}
int KmerCounter::operator()(int row, int column){
    return _frequency[row][column];
}
Profile KmerCounter::toProfile() const{
    Profile p;
    KmerFreq aux;
    for(int i = 0; i<getNumRows(); i++){
        for(int j = 0; j<getNumCols(); j++){
            if((i,j) > 0){
                aux.setFrequency((i,j));
                aux.setKmer(getKmer(i,j));
                p.append(aux);
            }
        }
    }
    return p;
}
void KmerCounter::calculateFrequencies(const char* fileName){
    Profile p;
    p.load(fileName);
    p.normalize(KmerCounter::DEFAULT_VALID_NUCLEOTIDES);
    initFrequencies();
    for(int i = 0; i<p.getSize(); i++){
        increaseFrequency(p.at(i).getKmer(), p.at(i).getFrequency());
    }
}