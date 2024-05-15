/*
 * Metodología de la Programación: Kmer2
 * Curso 2023/2024
 */

/** 
 * @file Profile.cpp
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 */


#include "Profile.h"

using namespace std;

const string Profile::MAGIC_STRING_T="MP-KMER-T-1.0";

Profile::Profile(){
    this->setProfileId("unknown");
    _size=0;
    _vectorKmerFreq = new kmerFreq[INITIAL_CAPACITY];
    _capacity = INITIAL_CAPACITY;
}
Profile::Profile(const int size){
    this->setProfileId("unknown");
    if(size < 0){
        throw out_of_range("En el constructor, el tamaño " + to_string(_size) +
                "debe ser mayor o igual a 0");
    }
    if(size > INITIAL_CAPACITY){
        //Reservar más memoria y establecer capacidad
    }
    else{
        _vectorKmerFreq = new kmerFreq[INITIAL_CAPACITY];
        _capacity = INITIAL_CAPACITY;
    }
    _size=size;
    
    KmerFreq zero;
    Kmer kmer(1);
    zero.setKmer(kmer);
    zero.setFrequency(0);
    for(int i = 0; i< size; i++){
        _vectorKmerFreq[i] = zero;
    }
}
Profile::Profile(Profile orig):_profileId(orig.getProfileId()), _size(orig.getSize()),_capacity(orig.getCapacity()) {
    //Intentar usar el operador = 
    /*_vectorKmerFreq = new kmerFreq[orig.getCapacity()];
    for(int i = 0; i < orig._size; i++){
        _vectorKmerFreq[i] = orig.
    }*/
}
Profile::~Profile(){
    //Las variables estáticas se destruirán automáticamente
    delete[] _vectorKmerFreq;
}

const string &Profile::getProfileId() const{
    return  _profileId;
}
void Profile::setProfileId(const string id){
    _profileId = id;
}
const KmerFreq *Profile::at(const int index) const{
    if(index < 0 || index > DIM_VECTOR_KMER_FREQ){
        throw out_of_range("En el método at, el índice " + to_string(index) +
                "debe estar entre 0 y " + to_string(_size));
    }
    
    return &(_vectorKmerFreq[index]);
}
KmerFreq *Profile::at(const int index){
    if(index < 0 || index > DIM_VECTOR_KMER_FREQ){
        throw out_of_range("En el método at, el índice " + to_string(index) +
                "debe estar entre 0 y " + to_string(_size));
    }
    return &_vectorKmerFreq[index];
}
const int Profile::getSize() const{
    return _size;
}
const int Profile::getCapacity() const{
    return DIM_VECTOR_KMER_FREQ;
}
const int Profile::findKmer(const Kmer kmer, const int initialPos, const int finalPos) const{
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
    return pos;
}
const int Profile::findKmer(const Kmer kmer) const{
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
    return pos;
}
const string Profile::toString() const{
    string s = "";
    s += _profileId + "\n";
    s += to_string(_size);
    for(int i = 0; i < getSize(); i++){
        s += "\n" + _vectorKmerFreq[i].getKmer().toString() + " " + to_string(_vectorKmerFreq[i].getFrequency());
    }
    return s;
}
void Profile::sort(){
    //algoritmo de ordenación por selección
    int max = 0;
    for(int i = 0; i< getSize(); i++){
        int j = i+1;
        max = i;
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
    
    for(int i = 0;i < getSize()-1; i++ ){
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
void Profile::save(const char fileName[]) const{
    if(!freopen(fileName, "w",stdout)){
        throw ios_base::failure("Ha habido un error a la hora de guardar el archivo");
    }
    cout<<MAGIC_STRING_T<<endl;
    cout<<toString();
}
void Profile::load(const char fileName[]){
    string s;
    int num;
    if(!freopen(fileName, "r", stdin)){
        throw ios_base::failure("El archivo dado no pudo abrirse.");
    }
    cin>>s; //Correspondiente al Magic_String
    cin>>s;//Correspondiente a el nombre
    _profileId = s;
    cin>>num; //Correspondiente al número de kmerfreqs
    if(num < 0 || num > DIM_VECTOR_KMER_FREQ){
        throw out_of_range ("La cantidad de kmers del archivo que se está " 
                "leyendo excede los límites de la capacidad de profile");
    }
    _size = num;
    KmerFreq kf;
    for(int i = 0; i<_size; i++){
        cin>>s; //Correspondiente al kmer
        Kmer k(s);
        kf.setKmer(k);
        cin>>num;//Correspondiente a la frecuencia
        kf.setFrequency(num);
        _vectorKmerFreq[i] = kf;
    }
}
void Profile::append(const KmerFreq &kmerFreq){ 
    bool apears = false;
    for(int i =0; i< _size; i++){
        if(_vectorKmerFreq[i].getKmer().toString() == kmerFreq.getKmer().toString()){
            apears = true;
            int fq = _vectorKmerFreq[i].getFrequency() + kmerFreq.getFrequency();
            _vectorKmerFreq[i].setFrequency(fq);
        }
    }
    if(!apears){
        _vectorKmerFreq[_size++] = kmerFreq;
    }
}
void Profile::normalize(const string validNucleotides){
    Kmer aux;
    for(int i = 0; i<_size; i++){
        aux = _vectorKmerFreq[i].getKmer();
        aux.normalize(validNucleotides);
        _vectorKmerFreq[i].setKmer(aux);
    }
    int findk;
    for(int i = 0; i<_size; i++){
        findk = findKmer(_vectorKmerFreq[i].getKmer(), i+1, _size-1);
        if(findk != -1){
            _vectorKmerFreq[i].setFrequency(_vectorKmerFreq[i].getFrequency() + _vectorKmerFreq[findk].getFrequency());
            deletePos(findk);
            i--;
        }
    }
}
void Profile::deletePos(const int pos){
    if(pos < 0 || pos >= _size){
        throw out_of_range("No se puede eliminar el KmerFreq de la posición " + to_string(pos) + 
                ", esta posición no es válida ya que excede el rango del vector usado");
    }
    for (int i = pos; i < _size-1; i++) {
        _vectorKmerFreq[i] = _vectorKmerFreq[i + 1];
    }
    _size--;
}
void Profile::zip(bool deleteMissing=false, const int lowerBound = 0){
    for(int i = 0; i<_size; i++){
        for(int j = 0; j < _vectorKmerFreq[i].getKmer().size(); j++){
            if(_vectorKmerFreq[i].getKmer().at(j) == Kmer::MISSING_NUCLEOTIDE){
                deleteMissing = true;
            }
        }
        if(_vectorKmerFreq[i].getFrequency() <= lowerBound || deleteMissing){
            deletePos(i);
            i--;
        }
        deleteMissing = false;
    }
}
void Profile::join(const Profile& profile){
    for(int i = 0; i< profile.getSize(); i++){
        append(profile._vectorKmerFreq[i]);
    }
}
const double Profile::getDistance (const Profile otherProfile) const{
    double resultado =0;
    int rank = 0;
    bool aparece = false;
    for(int i = 0; i<this->getSize(); i++){
        rank = 0;
        for(int j = 0; j< otherProfile.getSize() && !aparece; j++){
            if(otherProfile.at(j)->getKmer().toString() == this->at(i)->getKmer().toString()){
                if( j>=i){
                    rank = j-i;
                }
                else{
                    rank = i-j;
                }
                aparece = true;
            }
        } 
        if(!aparece){
            rank = otherProfile.getSize();
        }
        resultado+=rank;
        aparece = false;
    }
    resultado /= this->getSize()*otherProfile.getSize();
    return resultado;
}