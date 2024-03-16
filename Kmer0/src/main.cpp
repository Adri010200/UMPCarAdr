/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/* 
 * File:   main.cpp
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 * 
 */

#include <iostream>
#include <string>

#include "Kmer.h"

using namespace std;

/**
 * This program first reads from the standard input an integer k (length of Kmer)
 * and a string with a genetic sequence. Then, it obtains from the genetic 
 * sequence, the list of kmers (of length k) and saves them in the array kmers. 
 * Then, the kmers are normalized. After that, the complementary kmers, 
 * converted to lowercase, are saved in the array complementaryKmers. Finally 
 * the kmers in the arrays kmers and complementaryKmers are shown in the 
 * standard output.
 * See the next example:
 * 
 * Running example:
 * > kmer0 < data/easyDNA5_missing.k0in
6
GCGCC<-->cgcgg
CGCCC<-->gcggg
GCCC_<-->cggg_
CCC_G<-->ggg_c
CC_G_<-->gg_c_
C_G_G<-->g_c_c
 */
int main(int argc, char* argv[]) {
    // This string contains the list of nucleotides that are considered as
    // valid within a genetic sequence. The rest of characters are considered as
    // unknown nucleotides 
    const string VALID_NUCLEOTIDES = "ACGT";
    
    // This string contains the list of complementary nucleotides for each
    // nucleotide in validNucleotides
    const string COMPLEMENTARY_NUCLEOTIDES = "TGCA";

    // This is a constant with the dimension of the array kmers
    const int DIM_ARRAY_KMERS = 100;
    
    // This is the array where the kmers of the input genetic sequence will be
    // saved
    Kmer kmers[DIM_ARRAY_KMERS];
    
    // This is the array where the complementary kmers will be
    // saved
    Kmer complementaryKmers[DIM_ARRAY_KMERS];
    
    // Read K (integer) and a string with the input nucleotides list

    // Obtain the kmers: find the kmers in the input string and put them in an array of Kmers
    
    // Normalize each Kmer in the array

    // Obtain the complementary kmers and turn them into lowercase

    // Show the list of kmers and complementary kmers as in the example
    
    cout<<"Dame un número k y un string:\n";
    int k, i = 0;
    string st="", aux = "";
    cin>>k;
    cin>>st;
    cout<<"Tu número es: "<<k<<" y tu string es "<<st<<"\n";
    for(i; i<st.size()-(k-1); i++){ 
        for(int j = 0; j<k;j++){
            aux += st[j+i];
        }
        Kmer kmer(aux);
        kmer.normalize(VALID_NUCLEOTIDES);
        kmers[i] = kmer;
        aux="";
    }
    for(int j = 0; j<i; j++){
        Kmer kmer = kmers[j].complementary(VALID_NUCLEOTIDES, COMPLEMENTARY_NUCLEOTIDES);
        ToLower(kmer);
        complementaryKmers[j] = kmer;
    }
    for(int j=0; j<i;j++){
        cout<<kmers[j].toString()<<"<-->"<<complementaryKmers[j].toString()<<endl;
    }
    return 0;
     
}

