
#ifndef ERGASIA_NODE_H
#define ERGASIA_NODE_H
#include <string>
using namespace std;

/**
 * Κλάση που αναπαριστά έναν κόμβο, για τα δέντρα αναζήτησης
 */
class node
{
public:
    string value;
    string key;
    node *left;
    node *right;
    node *parent;
    int count;
    int height;

public:
    /**
     * Κενός κατασκευαστής
     */
    node() {

    }
    /**
     * Κατασκευαστής που δέχεται ως όρισμα την τιμή του κόμβου (την λέξη)
     * @param v τιμή του κόμβου
     */
    node(string v) {
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        count = 1;
        height=0;
    }
    /**
    *Κατασκευαστής που δέχεται ως όρισμα την τιμή του κόμβου (την λέξη) και το κλειδί του
    * @param v τιμή του κόμβου
    * @param k το κλειδί
    */
    node(string v,string k) {
        value = v;
        key = k;
        count = 1;
        height=0;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    //επιστροφή του αριστερού κόμβου, του κόμβου που είμαι τώρα
    node * getLeft() {
        return left;
    }

    //επιστροφή του δεξιού κόμβου, του κόμβου που είμαι τώρα
    node * getRight() {
        return right;
    }

    //επιστροφή του γονέα κόμβου, του κόμβου που είμαι τώρα
    node * getParent() {
        return parent;
    }

    //ανάθεση του αριστερού κόμβου
    void setLeft(node *l) {
        left = l;
    }

    //ανάθεση του δεξιού κόμβου
    void setRight(node *r) {
        right = r;

    }

    //ανάθεση του γονέα κόμβου
    void setParent(node *p) {
        parent = p;

    }

    //επιστροφή της τιμής του κόμβου
    string getValue() {
        return value;
    }

    //ανάθεση της τιμής του κόμβου
    void setValue(string val) {
        value = val;
    }

    //επιστροφή κλειδιού του κόμβου
    string getKey() {
        return key;
    }

    //επιστροφή του counter
    int getCount(){
        return count;
    }

    //αύξηση του counter οταν βρω την τιμή που ψάχνω στο δέντρο
    void counter(){
        count++;
    }

    //ανάθεση νεόυ κλειδιού του κόμβου
    void setKey(string newkey) {
        key = newkey;
    }
    //επιστροφή ύψους δέντρου
    int getHeight()
    {
        return height;
    }

    //ανάθεση νέου ύψους
    void setHeight(int newHeight)
    {
        height=newHeight;
    }
};




#endif //ERGASIA_NODE_H
