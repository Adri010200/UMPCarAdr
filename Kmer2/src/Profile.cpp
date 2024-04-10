/*
 * Metodología de la Programación: Kmer2
 * Curso 2023/2024
 */

/** 
 * @file Profile.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */


#include "Profile.h"

using namespace std;

const string Profile::MAGIC_STRING_T="MP-KMER-T-1.0";

Profile::Profile(){
    _profileId="unknown";
    _size=0;
}
Profile::Profile(int size){
    _profileId="unknown";
    _size=size;
    KmerFreq zero;
    Kmer kmer(1);
    zero.setKmer(kmer);
    zero.setFrequency(0);
    for(int i = 0; i< size; i++){
        _vectorKmerFreq[i] = zero;
    }
}
const std::string& Profile::getProfileId(){
    return const _profileId&;
}
void Profile::setProfileId(const string id){
    _profileId = id;
}
const KmerFreq& Profile::at(const int index){
    return const _vectorKmerFreq[index]&;
}
KmerFreq& Profile::at(const int index){
    return _vectorKmerFreq[index]&;
}
const int Profile::getSize(){
    return const _size;
}
const int Profile::getCapacity(){
    return DIM_VECTOR_KMER_FREQ;
}
const int Profile::findKmer(const Kmer kmer, const int initialPos, const int finalPos){
    int pos;
    bool encontrado = false;
    for(int i = initialPos; i<=finalPos && !encontrado; i++){
        if(kmer.toString() == _vectorKmerFreq[i].getKmer().toString()){
            encontrado = true;
            pos = i;
        }
    }
    if(!encontrado){
        pos = -1;
    }
    return const pos;
}
const int Profile::findKmer(const Kmer kmer){
    int pos;
    bool encontrado = false;
    for(int i = 0; i<= getSize() && !encontrado; i++){
        if(kmer.toString() == _vectorKmerFreq[i].getKmer().toString()){
            encontrado = true;
            pos = i;
        }
    }
    if(!encontrado){
        pos = -1;
    }
    return const pos;
}
const string Profile::toString(){
    string s = "";
    s += to_string(_profileId) + "\n";
    s += to_string(_size);
    for(int i = 0; i < getSize(); i++){
        s += "\n" + _vectorKmerFreq[i].getKmer().toString() + " " + to_string(_vectorKmerFreq[i].getFrequency());
    }
    return const s;
}
void Profile::sort(){
    //algoritmo de ordenación por selección
    int max = 0;
    for(int i = 0; i< getSize(); i++){
        int j = i+1;
        max = _vectorKmerFreq[i].getFrequency(); //Tal vez esta linea está mal
        for(j; j<getSize(); j++){
            if(_vectorKmerFreq[max].getFrequency() < _vectorKmerFreq[j].getFrequency()){
                max=j;
            }
        }
        if(max != i){ //Si encontró un nuevo máximo
            KmerFreq aux = _vectorKmerFreq[i];
            _vectorKmerFreq[i] = _vectorKmerFreq[max];
            _vectorKmerFreq[max] = aux;
        }
    }
    
    for(int i = 0;i < getSize(); i++ ){
        if(_vectorKmerFreq[i].getFrequency() == _vectorKmerFreq[i+1].getFrequency()){
            //Al comprobar el orden de dos strings c++ lo hace alfabéticamente
            if(_vectorKmerFreq[i].getKmer().toString() < _vectorKmerFreq[i+1].getKmer().toString()){
                KmerFreq aux = _vectorKmerFreq[i];
                _vectorKmerFreq[i] = _vectorKmerFreq[i+1];
                _vectorKmerFreq[i+1] = aux;
            }
        }
    }
}

/*include <cassert>
 *freopen(cadena, "r", stdin) para introducir un fichero
 *freopen(cadena,"w", stdout) para escribir un fichero
 * 
 * Método del de prácticas:Ej:
 * fopen(argv[2], "r")
 * usar fclose y feof.
 */
void save(char fileName[]){
    if(!freopen(fileName, "w",stdout)){
        throw ios_base::failure("Ha habido un error a la hora de guardar el archivo");
    }
    cout<<toString();
}
void load(const char fileName[]){
    
}