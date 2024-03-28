/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file KmerFreq.cpp
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 * 
 */

#include "KmerFreq.h"
using namespace std;
KmerFreq::KmerFreq(){
    Kmer kmer(1);
    _kmer = kmer;
    _frequency = 0;
}
const Kmer& KmerFreq::getKmer() const{ //No sé para que sirve el segundo const pero parece necesario
    const Kmer& kmero = this->_kmer;
    return kmero;
}
int KmerFreq::getFrequency(){
    return _frequency;
}
void KmerFreq::setKmer(Kmer kmer){
    _kmer = kmer;
}
void KmerFreq::setFrequency(int frequency){
    if(frequency < 0){
        throw out_of_range(string("La frecuencia debe ser mayor o igual a 0"));
    }
    else{
        _frequency = frequency;
    }
}
string KmerFreq::toString(){
    string s = _kmer.toString();
    s += " ";
    s += to_string(_frequency);
    return s;
}