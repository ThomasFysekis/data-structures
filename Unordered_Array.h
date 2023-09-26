#ifndef ERGASIA_UNORDERED_ARRAY_H
#define ERGASIA_UNORDERED_ARRAY_H
using namespace std;
#include <string>

class Unordered_Array{

private:
    long n;
    string *arr{};

public:
    explicit Unordered_Array(long num);
    void deleteUn(long num);
    void setVal(long i,string val){
        arr[i]=val;
    }
    string getVal(long i){
        return arr[i];
    }
    void show(Unordered_Array arr,long sum);
    void search(Unordered_Array arr,string Q[],long sum);

    void deleteΙtem(Unordered_Array &arr, string key, long sum);

    long getN(){
        return n;
    }
};


#endif //ERGASIA_UNORDERED_ARRAY_H
