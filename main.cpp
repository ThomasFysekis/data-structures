#include <iostream>
using namespace std;
#include <string>
#include<algorithm>
#include <fstream>
#include "Unordered_Array.h"
#include "Ordered_Array.h"
#include "Binary_Tree.h"
#include "AVLTree.h"
#include "Hash_Table.h"
#include <cstdlib>

string lower(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

string removePunctuation(string word) {

    word.erase(remove(word.begin(), word.end(), ':'), word.end());
    word.erase(remove(word.begin(), word.end(), ','), word.end());
    word.erase(remove(word.begin(), word.end(), '-'), word.end());
    word.erase(remove(word.begin(), word.end(), '.'), word.end());
    word.erase(remove(word.begin(), word.end(), '!'), word.end());
    word.erase(remove(word.begin(), word.end(), '?'), word.end());
    word.erase(remove(word.begin(), word.end(), ';'), word.end());
    word.erase(remove(word.begin(), word.end(), '_'), word.end());
    word.erase(remove(word.begin(), word.end(), '='), word.end());
    word.erase(remove(word.begin(), word.end(), '+'), word.end());
    word.erase(remove(word.begin(), word.end(), '/'), word.end());
    word.erase(remove(word.begin(), word.end(), '"'), word.end());
    word.erase(remove(word.begin(), word.end(), '&'), word.end());
    word.erase(remove(word.begin(), word.end(), '%'), word.end());
    word.erase(remove(word.begin(), word.end(), '%'), word.end());
    word.erase(remove(word.begin(), word.end(), '`'), word.end());
    word.erase(remove(word.begin(), word.end(), '^'), word.end());
    word.erase(remove(word.begin(), word.end(), '('), word.end());
    word.erase(remove(word.begin(), word.end(), ')'), word.end());
    word.erase(remove(word.begin(), word.end(), '['), word.end());
    word.erase(remove(word.begin(), word.end(), ']'), word.end());
    word.erase(remove(word.begin(), word.end(), '@'), word.end());
    word.erase(remove(word.begin(), word.end(), '#'), word.end());
    word.erase(remove(word.begin(), word.end(), '*'), word.end());
    word.erase(remove(word.begin(), word.end(), '~'), word.end());
    word.erase(remove(word.begin(), word.end(), '1'), word.end());
    word.erase(remove(word.begin(), word.end(), '2'), word.end());
    word.erase(remove(word.begin(), word.end(), '3'), word.end());
    word.erase(remove(word.begin(), word.end(), '4'), word.end());
    word.erase(remove(word.begin(), word.end(), '5'), word.end());
    word.erase(remove(word.begin(), word.end(), '6'), word.end());
    word.erase(remove(word.begin(), word.end(), '7'), word.end());
    word.erase(remove(word.begin(), word.end(), '8'), word.end());
    word.erase(remove(word.begin(), word.end(), '9'), word.end());
    word.erase(remove(word.begin(), word.end(), '0'), word.end());
    word.erase(remove(word.begin(), word.end(), '\n'), word.end());
    //word.erase(remove(word.begin(), word.end(), ' '), word.end());

    return word;


}

int num_of_rows()
{
    fstream file1;
    string filename="small-file.txt";

    long long int sum=0;
    string WORD1,WORD2;
    file1.open(filename);
    if (!file1)
    {
        cout << "Unable to open file test.txt"<<endl;
        exit(1);
    }
    file1>>WORD1;
    while(!file1.eof())
    {
        file1>>WORD2;
        sum++;
        WORD1=WORD2;
    }
    cout<<"Total pairs in the text file: "<<sum<<endl;
    file1.close();
    return sum;
}



int main() {


    int SUM=num_of_rows();
    string Q[1000];
    Unordered_Array un_arr(SUM);
    Ordered_Array or_arr(SUM);
    bst BST;
    AVLTree AVL;
    Hash_Table<int,string> H(1000);



    fstream file;
    string filename="small-file.txt";
    string word1, word2;

    file.open(filename);
    if (!file) {
        cout << "Unable to open file test.txt"<<endl;
        exit(1);
    }
    int i=0;

    double undur=0;
    double ordur=0;
    double bstdur=0;
    double avldur=0;
    double hashdur=0;
    file>>word1;
    while (file >> word2 && i<SUM)
    {

        string tempword = removePunctuation(lower(word1+" "+word2));
        if(tempword.length()>0) {


            high_resolution_clock::time_point t1u = high_resolution_clock::now();
            un_arr.setVal(i, tempword);
            high_resolution_clock::time_point t2u = high_resolution_clock::now();
            duration<double> time_spanu = duration_cast<duration<double>>(t2u - t1u);
            undur+=time_spanu.count();


            high_resolution_clock::time_point t1o = high_resolution_clock::now();
            or_arr.setVal(i,tempword);
            high_resolution_clock::time_point t2o = high_resolution_clock::now();
            duration<double> time_spano = duration_cast<duration<double>>(t2o - t1o);
            ordur+=time_spano.count();

            high_resolution_clock::time_point t1b = high_resolution_clock::now();
            BST.insert(tempword);
            high_resolution_clock::time_point t2b = high_resolution_clock::now();
            duration<double> time_spanb = duration_cast<duration<double>>(t2b - t1b);
            bstdur+=time_spanb.count();

            high_resolution_clock::time_point t1a = high_resolution_clock::now();
            AVL.addLeaf(tempword);
            high_resolution_clock::time_point t2a = high_resolution_clock::now();
            duration<double> time_spana = duration_cast<duration<double>>(t2a - t1a);
            avldur+=time_spana.count();

            high_resolution_clock::time_point t1h = high_resolution_clock::now();
            H.insert(1,tempword);
            high_resolution_clock::time_point t2h = high_resolution_clock::now();
            duration<double> time_spanh = duration_cast<duration<double>>(t2h - t1h);
            hashdur+=time_spanh.count();



            i++;

        }
        word1 = word2;

    }

    file.close();
    cout<<"Quicksort in process.Please wait..."<<endl;
    or_arr.quickSort(or_arr,0,SUM-1);
    cout<<"Quicksort completed."<<endl;


    cout<<"Making Q..."<<endl;
    file.open(filename);
    file>>word1;
    int q=0;
    while (file >> word2 && q<1000){

        string tempword = removePunctuation(lower(word1+" "+word2));
        if(tempword.length()>0) {
            string temp1 =tempword;
            Q[q] = temp1;
            //cout << Q[q] << endl;
            q++;

        }
        word1=word2;

    }
    file.close();
    cout<<"Q is ready..."<<endl;






    cout<<"Searching Q's pairs in Unordered Array..."<<endl;
    un_arr.search(un_arr,Q,SUM);
    file.open("Unordered.txt",fstream::app);
    file<<"Construction duration - "<<undur<<" sec"<<endl;
    file<<"_____________________________________________________________"<<endl;
    file.close();
    cout<<"Results are written in Unordered.txt!"<<endl;



    cout<<"Searching Q's pairs in Ordered Array..."<<endl;
    or_arr.search(or_arr,Q,SUM);
    file.open("Ordered.txt",fstream::app);
    file<<"Construction duration - "<<ordur<<" sec"<<endl;
    file<<"_____________________________________________________________"<<endl;
    file.close();
    cout<<"Results are written in Ordered.txt!"<<endl;


    cout<<"Searching Q's pairs in BST..."<<endl;
    BST.searchQ(Q);
    file.open("BST.txt",fstream::app);
    file<<"Construction duration - "<<bstdur<<" sec"<<endl;
    file<<"_____________________________________________________________"<<endl;
    file.close();
    cout<<"Results are written in BST.txt!"<<endl;


    cout<<"Searching Q's pairs in AVL..."<<endl;
    AVL.FindNode(Q);
    file.open("AVL.txt",fstream::app);
    file<<"Construction duration - "<<avldur<<" sec"<<endl;
    file<<"_____________________________________________________________"<<endl;
    file.close();
    cout<<"Results are written in AVL.txt!"<<endl;



    cout<<"Searching Q's pairs in Hash Table..."<<endl;
    H.searchQ(H,Q);
    file.open("HashTable.txt",fstream::app);
    file<<"Construction duration - "<<hashdur<<" sec"<<endl;
    file<<"_____________________________________________________________"<<endl;
    file.close();
    cout<<"Results are written in HashTable.txt!"<<endl;


    cout<<"                   -----------------END OF PROGRAM-----------------"<<endl;
    return 0;
}
