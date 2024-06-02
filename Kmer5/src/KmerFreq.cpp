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


std::ostream& operator<<(std::ostream& os,const KmerFreq k){
    os<<k.toString();
    return os;
}
std::istream& operator>>(std::istream& is, KmerFreq &k){
    string s;
    int f;
    is>>s >> f;
    Kmer aux(s);
    k.setKmer(aux);
    k.setFrequency(f);
    return is;
}

bool KmerFreq::operator<(const KmerFreq& k) const{
    if(this->getFrequency() < k.getFrequency())
    { return true; }
    else
    { return false; }
}
bool KmerFreq::operator>(const KmerFreq& k) const{
    if(this->getFrequency() > k.getFrequency() || (this->getFrequency() == k.getFrequency() && this->getKmer() < k.getKmer()))
    { return true; }
    else
    { return false; }
}
bool KmerFreq::operator<=(const KmerFreq& k) const{
    if(*this<k || *this == k)
    { return true; }
    else
    { return false; }
}
bool KmerFreq::operator>=(const KmerFreq& k) const{
    if(*this>k || *this == k)
    { return true; }
    else
    { return false; }
}
bool KmerFreq::operator!=(const KmerFreq& k) const{
    return !(*this == k);
}
bool KmerFreq::operator==(const KmerFreq& k) const{
    if(this->getFrequency() == k.getFrequency() && this->getKmer() == k.getKmer())
    { return true; } 
    else
    { return false; }
}