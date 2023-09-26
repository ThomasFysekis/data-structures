
#include <iostream>

#include "Ordered_Array.h"
using namespace  std;
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>

using namespace std::chrono;


Ordered_Array::Ordered_Array(long num) : Unordered_Array(num) {

    orarr = new string[getN()];
}


/**
 * Εναλλαγή δυο στοιχείων του πίνακα
 * @param array πίνακας
 * @param i θέση 1ου στοιχείου
 * @param j θέση 2ου στοιχείου
 */
void Ordered_Array::swap(Ordered_Array array,int i,int j){
    string temp = array.getVal(i);
    array.setVal(i,array.getVal(j));
    array.setVal(j,temp);
}
/**
 * Διαχωρισμός πίνακα για να γίνει η ταξινόμηση
 * @param array πίνακας
 * @param low αρχή διαμέρισης
 * @param high τέλος διαμέρισης
 * @return σημείο διαχωρισμού
 */
int Ordered_Array::partition(Ordered_Array array,int low,int high){
    string pivot = array.getVal(high);
    int i=low-1;
    for (int j = low; j < high; ++j) {
        if(array.getVal(j).compare(pivot)<0){
            i++;
            swap(array,i,j);
        }

    }
    swap(array,i+1,high);
    return(i+1);
}
/**
 * Μέθοδος ταξινόμησης quicksort
 * @param array πίνακας που είναι να ταξινομηθεί
 * @param low αρχή ταξινόμησης
 * @param high τέλος ταξινόμησης
 */
void Ordered_Array::quickSort(Ordered_Array array,int low,int high){

    if (low<high){

        int pi= partition(array,low,high);

        quickSort(array,low,pi-1);

        quickSort(array,pi+1,high);
    }
}
/**
* Μεθοδος εμφανισεις στοιχειων του πινακα
* @param array πινακας που πρεπει να εκτυπωθει στην οθονη.
* @param num το συνολο των λεξεων που περιεχονται στον πινακα.
*
*/
void Ordered_Array::show(Ordered_Array arr, long num) {
    for(int j=0;j<num;j++){
        if (arr.getVal(j)!="") {
            cout <<"Word: "<< arr.getVal(j)<< endl;

        }
    }
}
/**
*Μέθοδος που εφαρμοζει χρονομετρει και ετυπωνει την δυαδικη αναζητηση
* @param arr o πινακας οπου θα εκτελεστει η αναζητηση.
* @param Q ο πινακας οπου το περιεχωμενου θα αναζητηθει στον πινακα arr
* @param sum το συνολο των λεξεων του πινακα arr
*
*/
void Ordered_Array::search_Binary(Ordered_Array arr,string *Q, long sum)
{

    int num[1000];
    for(int & n : num){
        n=0;
    }
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int L=0,R=sum,M,i;
    bool D=false;
    for(i=0;i<1000;i++)
    {
        while(D==false && L<=R)
        {
            M=(L+R)/2;
            if (arr.getVal(M)==Q[i])
            {
                D=true;
                // num[i]++;

                int p=M+1;
                while(arr.getVal(M)==Q[i])
                {
                    num[i]++;
                    M--;

                }
                M=p-1;
                while(arr.getVal(p)==Q[i])
                {

                    num[i]++;
                    p++;

                }



            }
            else if (arr.getVal(M)<Q[i])
            {
                L=M+1;
            }
            else
            {
                R=M-1;
            }
        }

        L=0;
        R=sum;
        D=false;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    ofstream file("Ordered.txt");

    file << "\n----------------------------ORDERED ARRAY----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Word: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();






}
/**
 * Μέθοδος αναζήτησης για δοκιμές
 * @param arr πίνακας
 * @param Q πίνακας λέξεων
 * @param sum μέγεθος πίνακα
 */
void Ordered_Array::search(Ordered_Array arr, string *Q, long sum) {

    int num[1000];
    for(int & n : num){
        n=0;
    }
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i=0;i<1000;i++){
        for (int j=0;j<sum;j++){
            if(Q[i] == arr.getVal(j)){
                num[i] += 1;
            }
        }

    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    ofstream file("Ordered.txt");

    file << "\n----------------------------ORDERED ARRAY----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Word: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();


}
/**
 * Καταστροφέας
 * @param num μέγεθος πίνακα
 */
void Ordered_Array :: deleteOr(long num){
    for (int i = 0; i < num; ++i) {
        orarr[i]='\0';
    }
}


/**
 *
 * ιδια με τοu unordered array απλα εδω γίνεται παλι quicksort μετά την διαγραφή
 */
void Ordered_Array::deleteΙtem(Ordered_Array &arr, string key, long sum) {
    for(int i=0;i<sum;i++){
        if(arr.getVal(i)==key){
            string temp=arr.getVal(i);
            arr.setVal(i,arr.getVal(sum-1));
            arr.setVal(sum-1,"");
            quickSort(arr,0,sum-2);
            break;

        }
    }

}