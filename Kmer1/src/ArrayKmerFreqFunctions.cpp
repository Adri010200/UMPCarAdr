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
    for(int i = initialPos; i<= finalPos && !encontrado; i++){
        if (kmer.toString() == array[i].getKmer().toString()){
            encontrado = true;
            pos = i; //Si lo encuentra varias veces se queda con la primera
        }
    }
    if(!encontrado){
        return -1;
    }
    else{
        return pos;
    }
}



void NormalizeArrayKmerFreq(KmerFreq array[], int nElements, 
        string validNucleotides){ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
          // index = Position of array[i].getKmer() in the subarray that begins
          //         at position 0 and ends at position i-1
          // If array[i].getKmer() was found in the the subarray from 0 to i-1 
               // Accumulate the frequencies of the kmers at positions 
               //    index and i in the kmer at position index
               // Delete from the array, the kmer at position i 
}

