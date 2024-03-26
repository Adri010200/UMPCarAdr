/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file ArrayKmerFreqFunctions.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 27 October 2023, 12:00
 */


#include "ArrayKmerFreqFunctions.h"
using namespace std;

void ReadArrayKmerFreq(KmerFreq array[], const int dim, int nElements){
    cin<<nElements;
    if (nElements < 0){
        nElements = 0;
    }
    else if(nElements > dim){
        nElements = dim;
    }
    string s;
    int t;
    for(int i = 0; i < nElements; i++){
        cin<<s;
        Kmer kmero(s);
        array[i].setKmer(kmero);
        cin<<t;
        array[i].setFrequency(t);
    }
}

void PrintArrayKmerFreq(const KmerFreq array[], const int nElements){
    cout<<to_string(nElements)<<endl;
    for(int i = 0; i < nElements; i++){
        cout<<array[i].toString()<<endl;
    }
}

void SwapElementsArrayKmerFreq(KmerFreq array[], const int nElements, const int first,
                const int second){
    if(first > nElements || second > nElements){
        throw out_of_range(string("Alguno de los elementos que se desean intercambiar excede el rango utilizado del array"));
    }
    KmerFreq aux = array[first];
    array[first] = array[second];
    array[second] = aux;
}

int FindKmerInArrayKmerFreq(const KmerFreq array[], const Kmer kmer,
        const int initialPos, const int finalPos){
    bool encontrado = false;
    int pos;
    for(int i = initialPos; i<= finalPos && !encontrado; i++){ //Se queda con el primero que encuentra
        if (kmer.toString() == array[i].getKmer().toString()){
            encontrado = true;
            pos = i; 
        }
    }
    if(!encontrado){
        return -1;
    }
    else{
        return pos;
    }
}

void SortArrayKmerFreq(KmerFreq array[], const int nElements){
    //algoritmo de ordenación por selección
    int max = 0;
    for(int i = 0; i< nElements; i++){
        int j = i+1;
        for(j; j<nElements; j++){
            if(array[max] > array[j]){
                max=j;
            }
        }
        KmerFreq aux = array[max];
        array[max] = array[j];
        array[j] = aux;
    }
}

void NormalizeArrayKmerFreq(KmerFreq array[],int& nElements, 
        const string validNucleotides){ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    string str;
    for(int i = 0; i<nElements; i++){
        str = array[i].getKmer().toString();
        Kmer kmero(str);
        kmero.normalize(validNucleotides);
        array[i].setKmer(kmero);
    }
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
          // index = Position of array[i].getKmer() in the subarray that begins
          //         at position 0 and ends at position i-1
          // If array[i].getKmer() was found in the the subarray from 0 to i-1 
               // Accumulate the frequencies of the kmers at positions 
               //    index and i in the kmer at position index
               // Delete from the array, the kmer at position i 
    bool HayMasKmerIguales = true;
    for(int i = 0; i <nElements-1; i++){
        do{
            int pos2 = FindKmerInArrayKmerFreq(array[],array[i].getKmer(),i+1,nElements);
            if (pos2 != -1){
                array[i].setFrequency(array[i].getFrequency() + array[pos2].getFrequency());
                DeletePosArrayKmerFreq(array[], nElements, pos2);
            }
            else{
                HayMasKmerIguales = false;
            }
        }while(HayMasKmerIguales);
        HayMasKmerIguales = true;
    }
}

void DeletePosArrayKmerFreq(KmerFreq array[], int& nElements, const int pos){
        array[pos] = array[--nElements]; 
        //guardo el último KmerFreq del array en pos y disminuyo en 1 el número de elementos.
        //De esta forma el último elemento queda como basura pues paso nElements por referencia.
}

void ZipArrayKmerFreq(KmerFreq array[], int& nElements,  //El array pasado debe estar normalizado
        bool deleteMissing=false, int lowerBound=0){
    Kmer kmeraux; //Para acceder a Missing_Nucleotide "_" (Podría hacerlo con array[0].getKmer().MissingNucleotide 
                  //pero sería un error si el array estubiera vacío.)
    for(int i = 0; i<nElements; i++){
        
        if(array[i].getFrequency() <= lowerBound){
            deleteMissing = true; //No es sensato pero agiliza el proceso, no veo necesario hacer otra variable
        }
        for(int j = 0; j < array[i].getKmer().size() && !deleteMissing; j++){
            if(array[i].getKmer().at(j) == kmeraux.MISSING_NUCLEOTIDE){
                deleteMissing= true;
            }
        }
        
        if(deleteMissing){
            DeletePosArrayKmerFreq(array[], nElements, i); //Este método ya modifica el nElements
        }
        deleteMissing = false;
    }
}