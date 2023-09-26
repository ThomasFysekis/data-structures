
#ifndef ERGASIA_HASH_TABLE_H
#define ERGASIA_HASH_TABLE_H
#include <string> // std::string
#include <iostream> // std::cout
#include <chrono>
using namespace std::chrono;
using namespace std;
/**
 * Υπερφόρτωση του τελεστη % για την hash2
 * @param s λέξη που θέλω να κάνω hash
 * @param k μέγεθος πίνακα
 * @return την λέξη σε hash
 */
int operator%(string s,int k){
    int sum=0;
    for(int i=0;i<s.length();i++){
        sum+=s[i];
    }
    return sum%k;
}
/**
 * Υλοποίηση ενος ζευγαριού
 * @tparam dataType πλήθος επαναλήψεων της λέξης
 * @tparam keyType η λέξη
 */
template <typename dataType, typename keyType>
class myPair
{
public:
    myPair(dataType d, keyType k)
    {
        data=d;
        key=k;
    }
    dataType data;
    keyType key;
};
template <typename dataType, typename keyType>
class Hash_Table
{
private:
    int size;//μέγεθος πίνακα
    int elements;//πλήθος στοιχείων μέσα στον πίνακα
    myPair<dataType,keyType> **A;//δυναμικός πίνακας ζευγαριών
    void *deleted;//δείκτης που δείχνει οτι ένα αντικείμενο είναι διεγραμμένο
    unsigned int hash(const keyType &);//hashing 1
    unsigned int hash2(unsigned int );//hashing 2
    myPair<dataType,keyType> *& search(const keyType &);//αναζήτηση ζευγαριού
public:
    Hash_Table();//constructor
    Hash_Table(int n);//constructor με όρισμα το μέγεθος του πίνακα
    ~Hash_Table();//deconstructor
    bool insert(const dataType &, const keyType &);//εισαγωγή στοιχείου
    bool search(const keyType &, dataType &data);//αναζήτηση στοιχείου
    bool remove(const keyType &);//διαγραφή στοιχείου
    void searchQ(Hash_Table<dataType, keyType> n, string *Q);//αναζήτηση λέξεων του Q στην δομή
};
/**
 *  Άδειος constructor
 */
template <typename dataType, typename keyType>
Hash_Table<dataType,keyType>::Hash_Table()
{
    deleted = this;
    size=10;
    elements=0;
    A = new myPair<dataType,keyType> *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}
/**
 * Κατασκευαστής που δέχεται ως όρισμα το μέγεθος του πίνακα
 * @tparam dataType είδος τύπου του data του ζευγαριού
 * @tparam keyType είδος τύπου του key του ζευγαριού
 * @param n
 */
template <typename dataType, typename keyType>
Hash_Table<dataType,keyType>::Hash_Table(int n)
{
    deleted = this;
    size=n;
    elements=0;
    A = new myPair<dataType,keyType> *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}

/**
 * Καταστροφέας
 */
template <typename dataType, typename keyType>
Hash_Table<dataType,keyType>::~Hash_Table()
{
    delete[] A;
    A=nullptr;
    elements=0;
    size=0;
}
/**
 * Μέθοδος hashing , αποδοτική στις συγκρούσεις
 * @param d η λέξη που θέλω να κάνω hash
 * @return την λέξη σε hash
 */
template <typename dataType, typename keyType>
unsigned int Hash_Table<dataType,keyType>::hash(const keyType &d)
{
    unsigned long int hash = 5381; //https://stackoverflow.com/questions/7666509/hash-function-for-string

    for(auto x: d) //για κάθε γράμμα της λέξης
    {
        hash = ((hash << 5) + hash) + x; // xor : hash(i) = hash(i - 1) * 33 ^ str[i];
    }
    return (hash%size);


}
/**
 * Μέθοδος hashing, για την περίπτωση που η hash αποτύχει
 * @param d η λέξη που θέλω να κάνω hash
 * @return την λέξη σε hash
 */
template <typename dataType, typename keyType>
unsigned int Hash_Table<dataType,keyType>::hash2(unsigned int d)
{
    return (d+1) % size;
}
/** Μέθοδος αναζήτησης ενός key
 *
 * @param key το στοιχείο που ψάχνω
 * @return το ζευγάρι που περιέχει το στοιχείο που ψάχνω
 */
template <typename dataType, typename keyType>
myPair<dataType,keyType> *& Hash_Table<dataType,keyType>:: search(const keyType &key)
{
    unsigned int p = hash(key);
    while (A[p]!=nullptr && A[p]->key!=key)
        p = hash2(p);
    return A[p];
}
/**
 *  Μέθοδος αναζήτησης ενός ζευγαριού
 * @param key κλειδί ζευγαριού
 * @param data κενή μεταβλητή στην αρχή οπου αν βρεθεί το κλειδί παίρνει ως τιμή το δεδομένο του ζευγαριού
 * @return  true αν το ζευγάρι υπάρχει, false αν οχι
 */
template <typename dataType, typename keyType>bool Hash_Table<dataType,keyType>:: search(const keyType &key, dataType &data)
{
    myPair<dataType,keyType> *p = search(key);
    if (p==nullptr)
        return false;
    data = p->data;
    return true;
}

/**
 *Εισαγωγή νέου στοιχείου στον πίνακα
 * @param d δεδομένα στοιχείου
 * @param key κλειδί στοιχείου
 * @return true αν έγινε με επιτυχία η εισαγωγή, false αν το στοιχείο υπήρχε ήδη
 */
template <typename dataType, typename keyType>
bool Hash_Table<dataType,keyType>::insert (const dataType &d, const keyType &key)
{
    if (search(key)!=nullptr)
    {
        myPair<int,string> *p = search(key);
        p->data++;
        return false;
    }

    if (elements>=size/2)
    {
        myPair<dataType,keyType> **temp;
        size*=2;
        temp = new myPair<dataType,keyType>*[size];
        for(int i=0;i<size;i++)
            temp[i]=nullptr;
        for (int i=0;i<size/2;i++)
            if (A[i]!=nullptr)
            {
                unsigned int p = hash(A[i]->key);
                while (temp[p]!=nullptr)
                    p = hash2(p);
                temp[p]=A[i];
                A[i]=nullptr;
            }
        delete[]A;
        A=temp;
    }
    unsigned int p = hash(key);
    while (A[p]!=nullptr && A[p]!=deleted)
        p = hash2(p);
    A[p]=new myPair<dataType,keyType> (d,key);
    elements++;
    return true;
}
/**
 * Διαγραφή στοιχείου απο τον πίνακα
 * @param key κλειδί στοιχείου που θέλω να διαγράψω
 * @return true επιτυχία διαγραφής, false αποτυχία
 */
template <typename dataType, typename keyType>
bool Hash_Table<dataType,keyType>::remove(const keyType &key)
{
    myPair<dataType,keyType> * &p = search(key);
    if (p==nullptr)
        return false;
    elements--;
    delete p;
    p = (myPair<dataType,keyType> *) deleted;
    return true;
}
/**
 * Αναζήτηση λέξεων στην δομή
 * @param n ο πίνακας κατακερματισμού
 * @param Q πίνακας που περιέχει λέξεις που θέλω να ψάξω στην δομή
 */
template <typename dataType, typename keyType>
void  Hash_Table<dataType,keyType> ::searchQ(Hash_Table<dataType,keyType> n,string *Q){
    string key;
    int num[1000];

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {

        key = Q[i];
        int k;
        if(n.search(key,k)==1){
            num[i]=k;
        }

    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    ofstream file("HashTable.txt");
    file << "\n----------------------------HASH TABLE----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Word: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();

}
#endif //ERGASIA_HASH_TABLE_H
