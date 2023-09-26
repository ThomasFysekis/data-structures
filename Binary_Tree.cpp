#include "Binary_Tree.h"
using namespace std;
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std::chrono;

/**
 *  Constructor
 */
bst::bst() {
    root = nullptr; //ρίζα δέντρου
}


/** Ιδιωτική συνάρτηση εισαγωγής.
 *
 * @param r κόμβος εισαγωγής
 * @param data η λέξη που θέλω να εισάγω
 * @return true αν η εισαγωγή έγινε με επιτυχία, false αν απέτυχε
 */
bool bst::insert(node *r, const string &data) {
    if (data== r->getValue()) { //η λέξη υπάρχει ήδη στο δέντρο
        r->counter(); //αυξάνω το πλήθος εμφάνισης της λέξης
        return false;
    }
    if (data > r->getValue()) //η λέξη που θελω να βάλω ειναι λεξικογραφικά μεγαλύτερη απο την λέξη του κόμβου που βρίσκομαι
    {
        if (r->getRight()==nullptr) //ελεύθερος χώρος δεξιά
        {
            r->setRight(new node(data)); //εισαγωγή λέξης
            r->getRight()->setParent(r); //αλλαγή γονέα
            return true;
        }
        return insert (r->getRight(),data); //ψάχνω χώρο με αρχή τον δεξί κόμβο
    }
    else
    {
        if (r->getLeft()==nullptr) //ελεύθερος χώρος αριστερά
        {
            r->setLeft(new node(data)); //εισαγωγή λέξης
            r->getLeft()->setParent(r); //αλλαγή γονέα
            return true;
        }
        return insert (r->getLeft(),data); //ψάχνω χώρο με αρχή τον αριστερό κόμβο
    }
}
/** Δημόσια συνάρτηση εισαγωγής
 *
 * @param data η λέξη που θέλω να εισάγω
 * @return κλήση της ιδιωτικής insert
 */
bool bst::insert(const string &data) {
    if (root == nullptr) //κενό δέντρο
    {
        root = new node(data); //ρίζα η λέξη που θελω να εισάγω
        return true;
    }
    return insert(root,data); //δίνω όλο το δέντρο με την λέξη που θέλω να εισάγω

}

/**
 * Συνάρτηση που επιστρέφει τον κόμβο που έχει την λέξη key
 * @param key η λέξη που ψάχνω
 * @return κόμβος με την λέξη
 */
node *bst::search(string key) {
    node *p;
    p = root;
    while (p != nullptr && key != p->getValue())
    {
        if (key>p->getValue())
            p = p->getRight();
        else
            p = p->getLeft();
    }
    return p;

}

/**
 * Συνάρτηση που ψάχνει λέξη σε έναν κόμβο και δίνει την λέξη που βρήκε στην ret
 * @param key η λέξη που ψάχνω
 * @param ret κενή μεταβλητή που αλλάζει όταν βρω την λέξη που ψάχνω
 * @return true αν βρέθηκε η λέξη, false αν οχι
 */
bool bst::search(string key, string &ret) {
    node *p = search (key);
    if (p == nullptr)
        return false;
    ret = p->getValue();
    return true;

}
/**
 * Εμφάνιση του δέντρου με σειρά in order
 */
void bst::InOrder() {
    inOrder (root); //δίνω την ρίζα του δέντρου μου
}

/**Εμφάνιση του δέντρου με σειρά in order
 *
 * @param p ο κόμβος που βρίσκομαι τώρα
 */
void bst::inOrder(node *p) {
    if (p==nullptr)
        return;
    inOrder (p->getLeft());
    cout<<p->getValue()<<" - "<<p->getCount()<<endl;
    inOrder (p->getRight());

}
/**
 * Εύρεση ελαχίστου
 * @param m κενή μεταβλητή που παίρνει την ελάχιστη τιμή του δέντρου
 * @return true αν βρέθηκε το ελάχιστο, false αν δεν βρέθηκε
 */
bool bst::min(string &m) {
    node *r = min (root);
    if (r==nullptr)
        return false;
    m = r->getValue();
    return true;
}

/**
 * Εύρεση ελάχίστου
 * @param start ο κόμβος που ξεκινάει η αναήτηση ελάχιστου
 * @return ο κόμβος που περιέχει την ελάχιστη τιμή
 */
node *bst::min(node *start) {
    if (start ==nullptr)
        return nullptr;
    node *p = start;
    while (p->getLeft()!=nullptr)
        p=p->getLeft();
    return p;

}

/**
 * Εύρεση μεγίστου
 * @param m κενή μεταβλητή που παίρνει την μέγιστη τιμή του δέντρου
 * @return true αν βρέθηκε το μέγιστο, false αν δεν βρέθηκε
 */
bool bst::max(string &m) {
    node *r = max (root);
    if (r==nullptr)
        return false;
    m = r->getValue();
    return true;
}

/**
 * Εύρεση μεγίστου
 * @param start ο κόμβος που ξεκινάει η αναήτηση μεγίστου
 * @return ο κόμβος που περιέχει την μέγιστη τιμή
 */
node *bst::max(node *start) {
    if (start ==nullptr)
        return nullptr;
    node *p = start;
    while (p->getRight()!=nullptr)
        p=p->getRight();
    return p;
}
/**
 *
 * @return το ύψος του δέντρου
 */
int bst::height() {
    return height(root);
}


int bst::height(node *r) {
    if (r ==nullptr)
        return 0;
    int left,right;
    left = 1+height(r->getLeft());
    right = 1+height(r->getRight());
    return left>right?left:right;
}
/**
 *
 * @return true αν το δέντρο ειναι ισσοροπημένο, false αν δεν ειναι
 */
bool bst::isBalanced() {
    return isBalanced(root);
}
/**
 *
 * @param r η ρίζα του δέντρου
 * @return true αν το δέντρο ειναι ισσοροπημένο, false αν δεν ειναι
 */
bool bst::isBalanced(node *r) {
    if (r==nullptr)
        return true;
    return ( abs(height(r->getLeft())-height(r->getRight()))<=1 &&
             isBalanced(r->getLeft()) && isBalanced(r->getRight()) );
}
/**
 * Destructor
 */
bst::~bst() {
    destroyTree(root);
}
/**
 * Μέθοδος που καταστρέφει το δέντρο
 * @param r ρίζα δέντρου
 */
void bst::destroyTree(node *r) {

    if (r!=nullptr)
    {
        destroyTree(r->getLeft());
        destroyTree(r->getRight());
        delete (r);
    }

}
/**
 * Διαγραφή στοιχείου απο το δέντρο
 * @param key λέξη που θέλω να διαγράψω
 * @return κλήση της ιδιωτικής remove με όρισμα τον κόμβο που περιέχει την key, αλλιώς επιστρέφει false
 */
bool bst::remove(string key) {
    node *child;
    child = search(key);
    if (child!=nullptr)
        return remove (child);
    return false;
}
/**
 * Διαγραφή κόμβου
 * @param child κόμβο παιδί που περιέχει την λέξη που θέλω να διαγράψω
 * @return true αν η διαφραφή ολοκληρώθηκε ,false αν η διαγραφή απέτυχε
 */
bool bst::remove(node *child) {
    node *parent;
    if (child ==nullptr)
        return false;
    parent = child->getParent();
    if (child->getLeft() == nullptr && child->getRight()==nullptr) //no children
    {
        if (parent==nullptr) // deleting root
        {
            delete(child);
            root=nullptr;
        }
        else if (parent->getLeft() == child)
        {
            delete (parent->getLeft());
            parent->setLeft(nullptr);
        }
        else
        {
            delete (parent->getRight());
            parent->setRight(nullptr);
        }
    }
    else if (child->getLeft() == nullptr ||child->getRight() == nullptr ) //one child
    {
        if (parent==nullptr) // deleting root
        {
            if (child->getLeft() == nullptr)
                root = child->getRight();
            else
                root = child->getLeft();
            delete (child);
        }
        else if (parent->getLeft()==child)
        {
            if (child->getLeft() == nullptr)
                parent->setLeft(child->getRight());
            else
                parent->setLeft(child->getLeft());
            delete (child);
        }
        else
        {
            if (child->getLeft() == nullptr)
                parent->setRight(child->getRight());
            else
                parent->setRight(child->getLeft());
            delete (child);
        }
    }
    else // two children
    {
        node *mm = min(child->getRight());
        child->setValue(mm->getValue());
        remove(mm);
    }
    return true;

}
/**
 * Αναζήτηση των λέξεων του πίνακα Q στην δομή
 * @param Q πίνακας που περιέχει 1000 λέξεις
 */
void bst::searchQ(string *Q) {

    string key;
    int num[1000]; // πίνακας που θα περιέχει το ποσό επαναλήψεων κάθε λέξης

    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //χρονόμετρο
    for (int i = 0; i < 1000; ++i) {

        key=Q[i]; //ορίζω ως κλειδί την λέξη που ψαχνω
        node* n;
        n = searchNode(key,root); //κόμβος που περιέχει την λέξη που ψάχνω
        if(n!=NULL){ //γεμάτος κόμβος
            num[i]=n->getCount(); //δίνω το ποσό επανάληψης της λέξης key
        } else { //κενός κόμβος
            cout<<"The word doesn't exist in the tree!"<<endl;
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1); //χρόνος αναζήτησης
    ofstream file("BST.txt"); //εγγραφή σε αρχείο
    file << "\n----------------------------BINARY TREE----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Pair: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();



}
/**
 * Μέθοδος που επιστρέφει τον κόμβο που περιέχει το key
 * @param key η λέξη που ψάχνω
 * @param n ο κόμβος που βρίσκομαι τώρα
 * @return τον κόμβο που περιέχει την λέξη key, ή αναδρομικά καλείται πάλι η ιδια μέθοδος για αναζήτηση κόμβου
 */
node *bst::searchNode(string key, node *n) {
    if(n==NULL){ //node doesnt exist
        return NULL;
    } else { //node exists
        if(n->getValue()==key){
            return n;
        } else {
            if(n->getValue()<key){
                return searchNode(key,n->getRight());
            } else {
                return searchNode(key,n->getLeft());
            }
        }
    }
}

/**
 *
 * Εμφάνιση του δέντρου με σειρά post order
 */

void bst::postOrder() //Call the private function.
{
    postOrder(root);
}
/**
 * Εμφάνιση του δέντρου με σειρά post order
 * @param p o κόμβος που βρίσκομαι
 */
void bst::postOrder(node* p) //PostOrder function.
{
    if (p== nullptr) //If the current node isn't NULL.
        return;
    postOrder(p->getLeft()); //Go left.
    postOrder(p->getRight()); //Go right.
    cout<<p->getValue()<<" - "<<p->getCount()<<endl;

}
/**
 *
 * Εμφάνιση του δέντρου με σειρά pre order
 */
void bst::preOrder() //Call the private function.
{
    preOrder(root);
}

/**
 * Εμφάνιση του δέντρου με σειρά pre order
 * @param p o κόμβος που βρίσκομαι
 */
void bst::preOrder(node* p) //PreOrder function.
{
    if (p== nullptr) //If the node isn't NULL.
        return;
    cout<<p->getValue()<<" - "<<p->getCount()<<endl;
    preOrder(p->getLeft()); //Go left.
    preOrder(p->getRight()); //Go right.

}

