
#ifndef ERGASIA_ORDERED_ARRAY_H
#define ERGASIA_ORDERED_ARRAY_H
#include "Unordered_Array.h"

class Ordered_Array : public Unordered_Array{
private :

    string *orarr{}; //πίνακας string

public:

    explicit Ordered_Array(long num);
    void show(Ordered_Array arr, long num);
    void search(Ordered_Array arr, string *Q, long sum);


    void swap(Ordered_Array array, int i, int j);//εναλλαγή στοιχείων
    int partition(Ordered_Array array, int low, int high);// διαχωρισμός
    void quickSort(Ordered_Array array, int low, int high);

    void search_Binary(Ordered_Array arr, string *Q, long sum);
    void deleteΙtem(Ordered_Array &arr, string key, long sum);

    void deleteOr(long num);

};
#endif //ERGASIA_ORDERED_ARRAY_H
