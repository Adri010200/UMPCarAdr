/*
 * Metodología de la Programación: Kmer4
 * Curso 2023/2024
 */

/**
 * @file main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 *
 * Created on 17 November 2023, 12:45
 */

#include <iostream>

#include "Profile.h"

using namespace std;


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "ERROR in Kmer4 parameters" << endl;
    outputStream << "Run with the following parameters:" << endl;
    outputStream << "kmer4 [-t min|max] <file1.prf> <file2.prf> [ ... <filen.prf>]" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t min | -t max: search for minimun distances or maximum distances (-t min by default)" << endl;
    outputStream << "<file1.prf>: source profile file for computing distances" << endl;
    outputStream << "<file2.prf> [ ... <filen.prf>]: target profile files for computing distances" << endl;  
    outputStream << endl;
    outputStream << "This program computes the distance from profile <file1.prf> to the rest" << endl;
    outputStream << endl;
}

/**
 * This program reads an undefined number of Profile objects from the set of 
 * files passed as parameters to main(). All the Profiles object, except the 
 * first one, must be stored in a dynamic array of Profile objects. Then, 
 * for each Profile in the dynamic array, this program prints to the 
 * standard output the name of the file of that Profile and the distance from 
 * the first Profile to the current Profile. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Profile with the minimum|maximum  distance to the Profile 
 * of the first file and its profile identifier.
 * 
 * At least, two Profile files are required to run this program.
 * 
 * This program assumes that the profile files are already normalized and 
 * sorted by frequency. This is not checked in this program. Unexpected results
 * will be obtained if those conditions are not met.
 * 
 * Running sintax:
 * > kmer4 [-t min|max] <file1.prf> <file2.prf> [  ... <filen.prf>] 
 * 
 * Running example:
 * > kmer4 ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Nearest profile file: ../Genomes/mouse1.prf
Identifier of the nearest profile: mus musculus
 * 
 * Running example:
 * > kmer4 -t max ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Farthest profile file: ../Genomes/worm1.prf
Identifier of the farthest profile: worm
 */
int main(int argc, char* argv[]) {
    
    // Process the main() arguments
    
    // Allocate a dynamic array of Profiles
    
    // Load the input Profiles
    
    // Calculate and print the distance from the first Profile to the rest
    
    // Print name of the file and identifier that takes min|max distance to the first one

    // Deallocate the dynamic array of Profile
    bool argop = false;
    if(argv[1] == "-t"){
        argop=true;
    }
    
    Profile* parray;
    double* distarray;
    if(!argop){
        parray = new Profile[argc-1]; //en argv[0] se encuentra el nombre del proyecto
        distarray = new double[argc-2];
        for(int i = 0; i< argc-1; i++){
            parray[i].load(argv[i+1]);
        }
        for(int i=0; i<argc-2; i++){ //No contamos el nombre del programa
            distarray[i] = parray[0].getDistance(parray[i+1]);
        }
        for(int i=0; i<argc-2; i++){
            cout<<"Distancia entre " <<argv[1]<<" y "<<argv[i+2]<<": "<< distarray[i]<<endl;
        }
        
        //Búsqueda del mínimo:
        double min = 1;
        int pmin;
        for(int i= 0; i<argc-2; i++){
            if(distarray[i] < min){
                min = distarray[i];
                pmin = i;
            }
        }
        cout<<endl<<"Distancia mínima: "<< min << " del archivo: "<< argv[pmin+2];
    }
    else{
        parray = new Profile[argc-3];
        distarray = new double[argc-4];
        for(int i = 0; i<argc-3; i++){
            parray[i].load(argv[i+3]);
        }
        for(int i = 0; i<argc-4; i++){
            distarray[i] = parray[0].getDistance(parray[i+1]);
        }
        for(int i=0; i<argc-4; i++){
            cout<<"Distancia entre " <<argv[3]<<" y "<<argv[i+4]<<": "<< distarray[i]<<endl;
        }
        
        //Calculamos el mínimo y el máximo y luego vemos cual enseñamos.
        
        double min = 1, max = 0;//Sabemos que estará entre uno y cero
        int pmin, pmax;
        for(int i= 0; i<argc-4; i++){
            if(distarray[i] < min){
                min = distarray[i];
                pmin = i;
            }
            if(distarray[i] > max){
                max = distarray[i];
                pmax = i;
            }
        }
        if(argv[2] == "max"){
            cout<<endl<<"Distancia máxima: "<< max << " del archivo: "<< argv[pmax+4];
        }
        else{
            cout<<endl<<"Distancia mínima: "<< min << " del archivo: "<< argv[pmin+4];
        }
    }
    delete[] parray;
    delete[] distarray;
    return 0;
}

