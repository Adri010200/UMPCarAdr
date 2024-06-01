/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file KmerFreq.cpp
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 */

#include "KmerFreq.h"
using namespace std;
const Kmer& KmerFreq::getKmer() const{ 
    return _kmer;
}
const int KmerFreq::getFrequency() const{
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
string KmerFreq::toString() const {
    return _kmer.toString()+ " " + to_string(_frequency);
}