/*
 * Metodología de la Programación: Kmer2
 * Curso 2023/2024
 */

/** 
 * @file Profile.h
 * @author Carlos Manuel Pérez Molina <cperezmolina@correo.ugr.es>
 * @author Adrián Ros Moya <adri0102rm@correo.ugr.es>
 */

#ifndef PROFILE_H
#define PROFILE_H


#include <iostream>
#include "KmerFreq.h"

/**
 * @class Profile
 * @brief It defines a model (profile) for a given biological species. It 
 * contains a vector of pairs Kmer-frequency (objects of the class KmerFreq) 
 * and an identifier (string) of the profile.
 */
class Profile {
public:

    /**
     * @brief Base constructor. It builds a Profile object with "unknown" as
     * identifier, and an empty vector of pairs Kmer-frequency. 
     */
    Profile();

   
    /**
     * @brief It builds a Profile object with "unknown" as
     * identifier, and a vector with a size of @p size pairs Kmer-frequency. 
     * Each pair will be initialized as Kmer::MISSING_NUCLEOTIDE for the Kmer
     * and 0 for the frequency.
     * @throw std::out_of_range Throws a std::out_of_range exception if
     * @p size<0 or @p size > @p DIM_VECTOR_KMER_FREQ
     * @param size The size for the vector of kmers in this Profile. 
     * Input parameter
     */
    Profile(const int size);

    /**
     * @brief Copy constructor
     * @param orig the Profile object used as source for the copy. Input 
     * parameter
     */
    Profile(const Profile &orig);

    /**
     * @brief Destructor
     */
    ~Profile();
    
    /* @brief Overloading of the assignment operator for Profile class.
     * Modifier method
     * @param orig the Profile object used as source for the assignment. Input
     * parameter
     * @return A reference to this object
     */
    Profile& operator=(const Profile &orig);

    /**
     * @brief Returns the identifier of this profile object.
     * Query method
     * @return A const reference to the identifier of this profile object
     */
    const std::string &getProfileId() const;

    /**
     * @brief Sets a new identifier for this profile object.
     * Modifier method
     * @param id The new identifier. Input parameter
     */
    void setProfileId(const std::string id);


    /**
     * @brief Gets a const reference to the KmerFreq at the given position 
     * of the vector in this object.
     * Query method
     * @param index the position to consider. Input parameter
     * @throw std::out_of_range Throws an std::out_of_range exception if the 
     * given index is not valid
     * @return A const reference to the KmerFreq at the given position
     */
    const KmerFreq *at(const int index) const; 

    /**
     * @brief Gets a reference to the KmerFreq at the given position of the 
     * vector in this object
     * Query and modifier method
     * @param index the position to consider. Input parameter
     * @throw std::out_of_range Throws an std::out_of_range exception if the 
     * given index is not valid
     * @return A reference to the KmerFreq at the given position
     */
    KmerFreq *at(const int index); //Para la sobrecarga de operadores

    /**
     * @brief Gets the number of KmerFreq objects.
     * Query method
     * @return The number of KmerFreq objects 
     */
    const int getSize() const;
    
    /**
     * @brief Gets the capacity of the vector of KmerFreq objects.
     * Query method
     * @return The capacity of the vector of KmerFreq objects
     */
    const int getCapacity() const;
    
    /**
     * @brief Searchs the given kmer in the list of kmers in this
     * Profile, but only in positions from initialPos to finalPos 
     * (both included). If found, it returns the position where it was found. 
     * If not, it returns -1. We consider that position 0 is the first kmer in 
     * the list of kmers and this->getSize()-1 the last kmer.
     * Query method
     * @param kmer A kmer. Input parameter
     * @param initialPos initial position where to do the search. Input parameter
     * @param finalPos final position where to do the search. Input parameter
     * @return If found, it returns the position where the kmer 
     * was found. If not, it returns -1
     */
    const int findKmer(const Kmer kmer, const int initialPos, const int finalPos) const;
    
    /**
     * @brief Searchs the given kmer in the list of kmers in this
     * Profile. If found, it returns the position where it was found. If not,
     * it returns -1. We consider that position 0 is the first kmer in the 
     * list of kmers and this->getSize()-1 the last kmer.
     * Query method
     * @param kmer A kmer. Input parameter
     * @return If found, it returns the position where the kmer 
     * was found. If not, it returns -1
     */
    const int findKmer(const Kmer kmer) const;

    /**
     * @brief Obtains a string with the following content:
     * - In the first line, the profile identifier of this Profile
     * - In the second line, the number of kmers in this Profile  
     * - In the following lines, each one of the pairs kmer-frequency 
     * (separated by a whitespace).
     * Query method
     * @return A string with the number of kmers and the list of pairs of
     * kmer-frequency in the object
     */
    const std::string toString() const;

    /**
     * @brief Sorts the vector of KmerFreq in decreasing order of frequency.
     * If two KmerFreq objects have the same frequency, then the alphabetical 
     * order of the kmers of those objects will be considered (the object 
     * with a kmer that comes first alphabetically will appear first).
     * Modifier method
     */
    void sort();

    /**
     * @brief Saves this Profile object in the given file. 
     * Query method
     * @param fileName A c-string with the name of the file where this Profile 
     * object will be saved. Input parameter
     * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
     * if the given file cannot be opened or if an error occurs while writing
     * to the file
     */
    void save(const char fileName[]) const;

    /**
     * @brief Loads into this object the Profile object stored in the given 
     * file. Note that this method should remove any Kmer-frequency pairs that 
     * this object previously contained.
     * Modifier method
     * @param fileName A c-string with the name of the file where the Profile 
     * will be stored. Input parameter
     * @throw std::out_of_range Throws a std::out_of_range exception if the 
     * number of kmers in the given file, cannot be allocated in this Profile
     * because it exceeds the maximum capacity or if the number of kmers read 
     * from the given file is negative.
     * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
     * if the given file cannot be opened or if an error occurs while reading
     * from the file
     * @throw throw std::invalid_argument Throws a std::invalid_argument if
     * an invalid magic string is found in the given file
     */
    void load(const char fileName[]);
     
    /**
     * @brief Appends a copy of the given KmerFreq to this Profile object.
     * If the kmer is found in this object, then its frequency is increased
     * with the one of the given KmerFreq object. If not, a copy of the 
     * given KmerFreq object is appended to the end of the list of
     * KmerFreq objects in this Profile.
     * Modifier method
     * @thow std::out_of_range Throws a std::out_of_range exception in case
     * that a new element must be appended to the end of the array and the
     * number of elements in the array of KmerFreq is equals to the capacity
     * of that array. In that case, the array is full, and no more elements
     * can be appended to the array.
     * @param kmerFreq The KmerFreq to append to this object. Input paramether
     */
    void append(const KmerFreq &kmerFreq);
    
    /**
     * @brief Normalizes the Kmers of the vector of KmerFreq in this object. 
     * That is, for each Kmer in the vector, all its characters are converted 
     * to uppercase. Then, invalid characters are replaced by the 
     * MISSING_NUCLEOTIDE value.
     * 
     * If after the previous normalization process of every kmer, identical kmers 
     * are obtained, these will be merged into the first identical kmer by 
     * adding their frequencies. 
     * For example, suposse the following list of kmers:
4
Ct 5
hG 4
nG 1
cT 4
     * 
     * After the process of normalization of every kmer, we obtain the following 
     * list of kmers:
     * 
4
CT 5
_G 4
_G 1
CT 4
     * 
     * The final step will transform the list into:
2
CT 9
_G 5
     * 
     * Modifier method
     * @param validNucleotides a string with the list of characters (nucleotides) 
     * that should be considered as valid. Input parameter
     */
    void normalize(const std::string validNucleotides);

    /**
     * @brief Deletes the KmerFreq object from the vector of KmerFreq in this
     * object at the position @p pos. We consider that the first element has
     * position 0, and the last element position size()-1.
     * Modifier method
     * @param pos The index of the position to be deleted. Input parameter
     * @throw std::out_of_range Throws an std::out_of_range exception if @p pos 
     * is not in the range from 0 to size()-1 (both included).
     */
    void deletePos(const int pos);

    /**
     * @brief Deletes the KmerFreq objects from the vector of KmerFreq in this
     * object which verifies one the following two criteria:
     *  -# The argument deleteMissing is true and the Kmer contains an unknown 
     * nucleotide 
     *  -# The frequency is less or equals to @p lowerBound. 
     * 
     * Note that the number of elements in the argument array could be modified.
     * Modifier method
     * @param deleteMissing A bool value that indicates whether kmers with any 
     * unknown nucleotide should be removed. This parameter is false by default.
     * Input parameter
     * @param lowerBound An integer value that defines which KmerFreq objects 
     * should be deleted from the vector of KmerFreq in this object. 
     * KmerFreq objects with a frequency less or equals to this value, are 
     * deleted. This parameter has zero as default value.
     * Input parameter
     */
    void zip(bool deleteMissing, const int lowerBound);
    
    /**
     * @brief Appends to this Profile object, the list of pairs  
     * kmer-frequency objects contained in the Profile @p profile. This
     * method uses the method append(const KmerFreq& kmerFreq) to
     * append the pairs kmer-frequency contained in the argument 
     * Profile @p profile
     * Modifier method
     * @param profile A Profile object. Input parameter
     */
    void join(const Profile& profile);
    
    
/**
 * 
 * 
 * 
 * 
   **/
    const double getDistance (const Profile otherProfile) const;
    
    //Método para reservar memoria:
    void reservaMemoria (const int size);
    
private:
    std::string _profileId; ///< Profile identifier
    KmerFreq* _vectorKmerFreq; ///< Dynamic array of KmerFreq
    int _size; ///< Number of used elements in the dynamic array _vectorKmerFreq
    int _capacity; ///< Number of reserved elements in the dynamic array _vectorKmerFreq

    static const int INITIAL_CAPACITY=10; ///< Default initial capacity for the dynamic array _vectorKmerFreq. Should be a number >= 0
    static const int BLOCK_SIZE=20; ///< Size of new blocks in the dynamic array _vectorKmerFreq 

    static const std::string MAGIC_STRING_T; ///< A const string with the magic string for text files
};

#endif /* PROFILE_H */