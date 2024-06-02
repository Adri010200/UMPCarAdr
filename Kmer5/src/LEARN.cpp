/*
 * Metodología de la Programación: Kmer5
 * Curso 2023/2024
 */

/** 
 * @file Profile.h
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 */



/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "ERROR in LEARN parameters" << endl;
    outputStream << "Run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-k kValue] [-n nucleotidesSet] [-p profileId] [-o outputFilename] <file1.dna> [<file2.dna> <file3.dna> .... ]" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-k kValue: number of nucleotides in a kmer (5 by default)" << endl;
    outputStream << "-n nucleotidesSet: set of possible nucleotides in a kmer (ACGT by default). " 
                 << "Note that the characters should be provided in uppercase" << endl;
    outputStream << "-p profileId: profile identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.prf by default)" << endl;
    outputStream << "<file1.dna> <file2.dna> <file3.dna> ....: names of the input files (at least one is mandatory)" << endl;
    outputStream << endl;
    outputStream << "This program learns a profile model from a set of "<< 
            "input DNA files <file1.dna> <file2.dna> <file3.dna> ...." << endl;
    outputStream << endl;
}

/**
 * This program learns a Profile model from a set of input DNA files (file1.dna,
 * file2.dna, ...). The learned Profile object is then zipped (kmers with any 
 * missing nucleotide or with frequency equals to zero will be removed) 
 * and ordered by frequency and saved in 
 * the file outputFilename (or output.prf if the output file is not provided).
 * 
 * Running sintax:
 * > LEARN [-t|-b] [-k kValue] [-n nucleotidesSet] [-p profileId] [-o outputFilename] <file1.dna> [<file2.dna> <file3.dna> ....]
 * 
 * Running example:
 * > LEARN -k 2 -p bug -o /tmp/unknownACGT.prf ../Genomes/unknownACGT.dna
 * 
 * > cat /tmp/unknownACGT.prf
MP-KMER-T-1.0
bug
7
GG 2
AC 1
AG 1
AT 1
CC 1
GA 1
TA 1
 * 
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {   
    // Process the main() arguments
    
    string fprofile;
    string n;
    string outputfile;
    int k;
    int restantes;
    int pos=1;
    bool fin=false;
    string* sarray;
    while ((pos<argc) && (!fin)) {
        if (argv[pos][0]=='-’)
            if (strlen(argv[pos])==2) { // Se necesita una letra
                if (argv[pos][1]=='p' && (pos+1<argc)) {
                    fprofile = argv[pos+1];//
                    pos+=2;
                }
                else if(argv[pos][1] == 'k' && (pos+1<argc)){
                    k = static_cast<int>(argv[pos+1]);
                    pos+=2;
                }
                else if (argv[pos][1] == 'n' && (pos+1<argc)){
                    n = argv[pos+1];
                    pos +=2;
                }
                else if(argv[pos][1] == 'o' && (pos+1<argc)){
                    outputfile = argv[pos+1];
                    pos +=2;
                }
                // ...
            } else {
            // Error, se ha puesto solo ‘-’ 
            fin=true;
            }
        else{
        // Aquí comienza lista de ficheros de entrada. 
            fin=true;
            if(outputfile == ""){
                outputfile = argv[pos];
                pos++;
            }
            restantes = argc-pos;
            sarray = new string[restantes];
            for(int i = 0; i<restantes ; i++){
                sarray[i] = argv[pos];
                pos++;
            }
        }
    }
    
    // Loop to calculate the kmer frecuencies of the input genome files using 
    // a KmerCounter object
    if(k != 0 && n != ""){
        KmerCounter kc(k, n);
    }
    else{
        KmerCounter kc;
    }
    for(int i = 0; i<restantes; i++){
        kc.calculateFrequencies(sarray[i]);
    }
    // Obtain a Profile object from the KmerCounter object
    Profile p = kc.toProfile();
    if(fprofile != ""){
        p.setProfileId(fprofile);
    }
    
    // Zip the Profile object
    p.zip();
    // Sort the Profile object
    p.sort();
    // Save the Profile object in the output file
    p.save(outputfile);
}

