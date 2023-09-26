
#include "Unordered_Array.h"
using namespace std;
#include <string>
#include<algorithm>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>

using namespace std::chrono;

/**
* O κατασκευαστης της κλασης Unordered_Array σε αυτο αρχικοποιουντα τα πεδια τις κλασης.
* @param num η μεταβλητη οπου αναπαρισμα το πληθος των λεξεων του αρχειου.
*/
Unordered_Array::Unordered_Array(long num) {
    n=num;
    arr=new string[n];
}

/**
* Η μεθοδος οπου εμφανιζει στην οθονη τον πινακα arr.
* @param arr ο πινακας οπου θα εμφανιστει στην οθονη.
* @param sum ουσιαστικα ειναι το μεγεθος του πινακα δηλαδη τοο συνολο των λεξεων του αρχειου.
*
*/
void Unordered_Array::show(Unordered_Array arr,long sum) {
    for(int j=0;j<sum;j++){
        if (arr.getVal(j)!="") {
            cout <<"Word: "<< arr.getVal(j)<< endl;
        }
    }

}

/**
* Στη μεθοδο αυτη υλοποιειται χρονομετριτε και εμφανιζεται η σειριακη αναζητηση.
* @param arr ο πινακας στον οποιο θα εφαρμοστει η αναζητηση.
* @param Q ο πινακας απο τον οποιο θα βρουμε τις λεξεις που πρεπει να αναζητησουμε στον πινακα arr.
* @param sum το συνολο των λεξεων που βρισκονται στον πινακα arr.
*
*/
void Unordered_Array::search(Unordered_Array arr, string *Q, long sum) {

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
    ofstream file("Unordered.txt");
    file << "\n----------------------------UNORDERED ARRAY----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Word: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();




}
/**
*Η μεθοδος αυτη ειναι ουσιαστικα ο καταστροφεας του πινακα arr.
* @param sum το μεγεθος του πινακα
*/
void Unordered_Array::deleteUn(long num) {
    for (int i = 0; i < num; ++i) {
        arr[i]='\0';
    }

}


/**
 *
 * @param arr πινακας
 * @param key η λεξη που θελω να διαγραψω
 * @param sum το μεγεθος του πινακα
 *
 */
void Unordered_Array::deleteΙtem(Unordered_Array& arr,string key, long sum) {
    for(int i=0;i<sum;i++){
        if(arr.getVal(i)==key){
            arr.setVal(i,arr.getVal(sum-1));
            arr.setVal(sum-1,"");
            break;

        }
    }

}