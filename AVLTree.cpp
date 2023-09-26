#include "AVLTree.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <chrono>
#include <fstream>

using namespace std::chrono;


AVLTree::AVLTree()
{
    root=NULL;
}
/**
* Η μέθοδος αυτή καλεί την συναρτηση addLeafPrivAVL.
* @param key ουσιαστικα ειναι μια μεταβλητη που θεωρειται το κλειδι του κομβου.
*
*/
void AVLTree::addLeaf(string key)
{
    root = addLeafPrivAVL(key,root);
}
/**
* Σκοπος αυτης της μεθοδου ειναι να βαλει τη μεταβλητη key που δεχεται στο αντικημενο που δειχνει η μεταβλητη pointer.
* @param key ειναι μια μεταβλιτη που αντιπρωσοπευει το κλειδι του κομβου.
* @param pointer ειναι ενας δεικτης που δειχνει σε αντικημενο node.
*/
node* AVLTree::addLeafPrivAVL(string key, node* pointer)
{
    if (pointer == NULL)
    {
        pointer = CreateLeaf(key); //διμιουργια νεου φυλλου.
    }
    else if (key < pointer->key) //Αν το key είναι μικρότερο από το περιεχόμενο του κόμβου τότε καλείται η addLeafPrivAvl  για το αριστερό παιδί του κόμβου.
    {
        pointer->left = addLeafPrivAVL(key,pointer->left);

        if (Height(pointer->left) - Height(pointer->right) == 2)
        {
            if(key < pointer->left->key)
                pointer = RightRotation(pointer);
            else{
                pointer = doubleRightRotation(pointer);
            }
        }

    }
    else if (key > pointer->key)
    {
        pointer->right = addLeafPrivAVL(key,pointer->right);

        if (Height(pointer->right) - Height(pointer->left) == 2)
        {
            if (key > pointer->right->key){
                pointer = LeftRotation(pointer);
            }
            else{
                pointer = doubleLeftRotation(pointer);
            }
        }
    }
    else
    {
        pointer->count += 1;
    }
    pointer->height = max(Height(pointer->left), Height(pointer->right))+1;

    return pointer;


}
/**
* Η μεθοδος αυτη υπολογιζει το υψος του δεντρου.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*
*/
int AVLTree::Height(node* pointer)
{
    if (pointer==NULL)
        return -1;
    return pointer->height; //επεστρεψε το height
}
/**
*Σκοπος της μεθοδου αυτης ειναι να κανει δεξια περιστροφη το δεντρο ετσι ωστε να ισοροπησει.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*/
node* AVLTree::RightRotation(node* &pointer)
{
    if (pointer->left != NULL) //αν το αριστερόπαιδι δεν ειναι null.
    {
        node* x = pointer->left; //αποθηκευσε το αριστερο παιδι του τρεχοντος κομβου στον κομβο χ.
        pointer->left = x->right; //οριζουμε το αριστερο παιδι του τρεχοντος κομβου στο δεξι παιδι του χ.
        x->right = pointer;
        pointer->height = max(Height(pointer->left), Height(pointer->right)) + 1; //βρισκουμε το μεγιστο υψος του δεξιου παιδιου του κομβου και προσθετουμε +1.
        x->height = max(Height(x->left), pointer->height) + 1; //βρισκουμε το μεγιστο υψος του αριστερου παιδιου του κομβου και προσθετουμε +1.
        return x;
    }
    return pointer;

}
/**
* Και αυτη η μεθοδος εχει ως σκοπο να κανει αριστρερη περιστροφη το δεντρο ωστα να ισιροπηση.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
* Ουσιαστικα και αυτη η μεθοδος υλοποιηται οπως και η παραπανω απλα απο την αριστερη πλευρα.
*/
node* AVLTree::LeftRotation(node* &pointer)
{
    if (pointer->right != NULL)
    {
        node* x = pointer->right;
        pointer->right = x->left;
        x->left = pointer;
        pointer->height = max(Height(pointer->left), Height(pointer->right)) + 1;
        x->height = max(Height(pointer->right), pointer->height) + 1;
        return x;
    }
    return pointer;
}
/**
*Η μεθοδος αυτη κανει διπλη περιστροφητο δεντρο ωστε να μπορεσει να ισιοροπιση. Η συναρτηση καλει και τις δυο αλλας συναρτησεις RightRotation και LeftRotation.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
* @return Η συνάρτηση επιστρεφει δείκτη που δείχνει σε αντικείμενο node
*/
node* AVLTree::doubleRightRotation(node* &pointer)
{
    pointer->left = LeftRotation(pointer->left); //το αριστερο παιδι κανει rotation προς τα αριστερα.
    return RightRotation(pointer);
}
/**
*Η μεθοδος αυτη κανει διπλη περιστροφητο δεντρο ωστε να μπορεσει να ισιοροπιση. Η συναρτηση καλει και τις δυο αλλας συναρτησεις RightRotation και LeftRotation.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
* @return Η συνάρτηση επιστρεφει δείκτη που δείχνει σε αντικείμενο node
*/
node* AVLTree::doubleLeftRotation(node* &pointer) //Double left rotation.
{
    pointer->right = RightRotation(pointer->right); //το δεξι παιδι κανει rotation προς τα δεξια.
    return LeftRotation(pointer);
}
/**
* Σκοπός της συνάρτησης είναι να βρει το μεγαλύτερο από τα δυο ορίσματα.
*@param a ειναι ενα ορισμα με τυπο int.
*@param b ειναι ενα ορισμα με τυπο int.
*@return η συνάρτηση επιστρέφει μια μεταβλητή τύπου int
*/
int AVLTree::max(int a, int b)
{
    if (a>b)
        return a;
    return b;
}
/**
*Σκοπός της συνάρτησης είναι κάνει διάσχιση από τα αριστερά προς τα δεξιά αυτό έχει ως αποτέλεσμα να εμφανίζονται τα στοιχεία του δέντρου ταξινομημένα.
*/
void AVLTree::InOrder()
{
    InOrderPriv(root);
}
/**
*H συνάρτηση αυτή κάνει διάσχιση της κλάσης πρώτα από τον κόμβο μετα στο αριστερό και στο τέλος πάει στο δεξί παιδί.
*/
void AVLTree::PreOrder()
{
    PreOrderPriv(root);
}
/**
*Η συνάρτηση αυτή κάνει διάσχιση από τα παιδιά προς τον γονέα δηλαδή πηγαίνει πρώτα από το αριστερό παιδί υστέρα στο δεξί παιδί και τέλος στον γονέα.
*/
void AVLTree::PostOrder()
{
    PostOrderPriv(root);
}
/**
*Σκοπός της συναρτήσεις είναι να κάνει την αναζήτηση των λέξεων του πίνακα Q στο δέντρο AVL και να την χρονομέτρηση.
*@param Q ειναι ο πινακας απο το οποιο θα παρουμε τις λεξεις που θα αναζητησουμε.
*/
void AVLTree::FindNode(string *Q)
{
    string key;
    int num[1000];
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //ξεκιναει το χρονόμετρο
    for(int i=0;i<1000;i++){
        key=Q[i];
        node* temp;
        temp=FindNodePriv(key,root);
        if (temp!=NULL){
            num[i]=temp->count;
        } else
            cout<<"The word doesn't exist in the tree!"<<endl;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1); //υπολογιζετε ο χρονος αναζητησησης των λεξεων.
    ofstream file("AVL.txt"); //εγγραφή σε αρχείο
    file << "\n----------------------------AVL TREE----------------------------\n";
    for(int i=0;i<1000;i++){
        file<<"Pair: "<<Q[i]<<" , appears "<<num[i]<<" time(s)"<<endl;
    }
    file<<"DURATION: "<<time_span.count()<<" sec"<<endl;
    file<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    file.close();
}
/**
*Σκοπός της συνάρτησης είναι να διαγράψει τον κόμβο που έχει πάρει ως όρισμα με τη βοήθεια της συναρτήσεις DeleteNodePrivAvl.
*@param key ειναι μεταβλητη τύπου string και στην ουσια ειναι το κλειδιτου κομβου.
*/
void AVLTree::DeleteNode(string key)
{
    root=DeleteNodePrivAVL(key,root);
}
/**
*Σκοπός της συνάρτησης είναι να διαγράψει τον κόμβο που έχει πάρει ως όρισμα αυτη η μεθοδος καλειται απο την απο πανω.
*@param key ειναι μεταβλητη τύπου string και στην ουσια ειναι το κλειδιτου κομβου.
* @param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*@return δεικτη που δειχνει σε αντικημενο με τυπο node.
*/
node* AVLTree::DeleteNodePrivAVL(string key, node* pointer)
{
    node* temp;
    bool flag=true;

    if (root==NULL) //αν η ριζα ειναι null ουσιαστικα δεν υπαρχει δεντρο οποτε επιστρεφει null.
    {
        return nullptr;
    }
    else if(key < pointer->key) //αν το key ειναι μικροτερο του κομβου καλει αναδρομικα τον εαυτο της για το αριστερο παιδι.
    {
        pointer->left = DeleteNodePrivAVL(key, pointer->left);
    }
    else if(key > pointer->key) //αν το key ειναι μεγαλυτερο του κομβου καλει αναδρομικα τον ευτο της για το δεξι παιδι..
    {
        pointer->right = DeleteNodePrivAVL(key, pointer->right);
    }

    else if (pointer->count>1) //αν η λεξη υπαρχει παραπανω απο μια φορες.
    {
        pointer->count-=1;
        flag=false;
    }
        // για δυο παιδια
    else if (pointer->left!=nullptr && pointer->right!=nullptr)
    {
        temp = min(pointer->right); //αποθηκευει τον μικροτερο κομβο
        pointer->key = temp->key;
        pointer->count=temp->count;
        pointer->right = DeleteNodePrivAVL(pointer->key, pointer->right); //διαγραφη τον μικροτερο κομβο.
    }
        // για ενα ή για κανενα παιδι
    else
    {
        if(pointer->left == nullptr) //αν το αριστερο παιδι ειναι null
            pointer = pointer->right; //o γονεας γινεται το δεξι παιδι
        else if(pointer->right == nullptr) //αν το δεξι παδι ειναι null
            pointer = pointer->left; //o γονεας γινεταιτο αριστρερο παιδι.
    }
    if(pointer == nullptr)
    {
        return pointer;
    }

    if (flag)
    {
        pointer->height = max(Height(pointer->left), Height(pointer->right))+1;

        // αν ο κομβος ειναι μη ισοροπημενος

        if(Height(pointer->left) - Height(pointer->right) == -2)
        {

            if(Height(pointer->right->right) - Height(pointer->right->left) == 1)
                return LeftRotation(pointer);

            else{
                return doubleLeftRotation(pointer);
            }
        }

        else if(Height(pointer->right) - Height(pointer->left) == 2)
        {
            if(Height(pointer->left->left) - Height(pointer->left->right) == 1){
                return RightRotation(pointer);
            }
            else{
                return doubleRightRotation(pointer);
            }
        }
    }
    return pointer;
}
/**
*Η μεθοδος αυτη βρισκει τον ελαχιστο κομβο.
*@param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*@return  δεικτη που δειχνει σε αντικημενο με τυπο node.
*/
node* AVLTree::min(node* pointer)
{
    if (root!=NULL)
    {
        if (pointer->left==NULL) //αν το αριστεροπαιδι ειναι null.
        {
            return pointer; //επεστρεψε τον μικροτερο κομβο
        }
        else{
            return min(pointer->left); //πανε αριστερα
        }
    }
    else
    {
        cout<<"The tree is empty!"<<endl;
        return NULL;
    }
}
/**
* Σκοπός της συνάρτησης αυτής είναι ότι όταν χρειάζεται ένα καινούργιο φύλλο δημιουργεί ένα.
*@param key ειναι μια μεταβλιτη που αντιπρωσοπευει το κλειδι του κομβου.
*@return επιστρεφει ενα δεικτη που δειχνει σε αντικημενο node.
*/
node* AVLTree :: CreateLeaf(string key)
{
    node *n= new node; //φτιαχνει νεο κομβο.
    n->key=key; //τοποθετειτο κλειδι στο νεο κομβο.
    n->left=NULL; //κανει το δεξι παιδι null
    n->right=NULL; //κανει το αριστερο παιδι null.
    n->count=1;
    n->height=0;

    return n;
}
/**
*Ουσιαστικά αυτή η συνάρτηση κάνει αναζήτηση και καλείται από την findNote.
*@param key ειναι μια μεταβλιτη που αντιπρωσοπευει το κλειδι του κομβου.
*@param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*@return δεικτη που δειχνει σε αντικημενο με τυπο node.
*/
node* AVLTree ::FindNodePriv(string key, node* pointer)
{
    if (pointer!=NULL) //αν υπαρχει κομβος
    {
        if (pointer->key==key) //εαν το εσωτερικο που δειχνει ο pointer ειναι ιδιο με το key.
        {
            return pointer;
        }
        else
        {
            if (pointer->key>key) //εαν το εσωτερικο που δειχνει ο pointer ειναι μικροτερο απο το key
            {
                return FindNodePriv(key,pointer->left); //πανε δεξια
            }
            else
            {
                return FindNodePriv(key,pointer->right); //πανε αριστερά
            }
        }

    }
    else
    {
        return NULL;
    }
}
/**
*Σκοπός της συνάρτησης είναι να κάνει προσπέλαση το δέντρο από τα δεξιά προς τα αριστερά. καλειτε απο την InOrder.
*@param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*
*/
void AVLTree ::InOrderPriv(node* pointer)
{
    if (pointer!=NULL) //Αν ο κομβος δεν ειναι null.
    {
        if (pointer->left!=NULL)
        {
            InOrderPriv(pointer->left); //πανε αριστερα.
        }
        cout<<pointer->key<<"["<<pointer->count<<"]"<<endl;
        if (pointer->right!=NULL)
        {
            InOrderPriv(pointer->right); //πανε δεξια.
        }
    }
    else
    {
        cout<<"The tree is empty!"<<endl;
    }
}
/**
*Σκοπός της συνάρτησης είναι να κάνει προσπέλαση το δέντρο απο τα παιδια προς τον γωνιό και πιο συγκεκριμενα απο το αριστερο παιδι στο δεξιό παιδι και τελος στον γωνιό. καλειτε απο την PostOrder.
*@param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*
*/
void AVLTree::PostOrderPriv(node* pointer)
{
    if (pointer!=NULL) //Αν ο κομβος δεν ειναι null.
    {
        if (pointer->left!=NULL)
        {
            PostOrderPriv(pointer->left); //πανε αριστερα.
        }
        if (pointer->right!=NULL)
        {
            PostOrderPriv(pointer->right); //πανε δεξια.
        }
        cout<<pointer->key<<"["<<pointer->count<<"]"<<endl;
    }
    else
    {
        cout<<"The tree is empty!"<<endl;
    }
}
/**
* Σκοπός της συνάρτησης είναι να κάνει προσπέλαση το δέντρο απο  τον γονέα προς τα παιδιά. καλειτε απο την PreOrder.
*@param pointer ειναι ουσιαστικα ενας δεικτης που δειχνει σε ενα αντικημενο node.
*
*/
void AVLTree::PreOrderPriv(node* pointer)
{
    if (pointer!=NULL) ///Αν ο κομβος δεν ειναι null.
    {
        cout<<pointer->key<<"["<<pointer->count<<"]"<<endl;
        if (pointer->left!=NULL)
        {
            PreOrderPriv(pointer->left); //πανε αριστερα.
        }
        if (pointer->right!=NULL)
        {
            PreOrderPriv(pointer->right); //πανε δεξια.
        }
    }
}

