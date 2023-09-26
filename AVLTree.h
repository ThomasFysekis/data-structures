#ifndef AVLTREE_H
#define AVLTREE_H


#include "node.h"


class AVLTree : public node
{
private:
    node* root;

    node* addLeafPrivAVL(string, node*);
    int Height(node*);
    int max(int, int);
    node* RightRotation(node* &);
    node* LeftRotation(node* &);
    node* doubleRightRotation(node* &);
    node* doubleLeftRotation(node* &);

    node* DeleteNodePrivAVL(string,node*);
    node* min(node*);
public:
    AVLTree();
    void addLeaf(string);
    void FindNode(string*);
    void DeleteNode(string);




    void InOrder();
    void PreOrder();
    void PostOrder();
    node* CreateLeaf(string key);
    node* FindNodePriv(string, node*);
    void InOrderPriv(node*);
    void PreOrderPriv(node*);
    void PostOrderPriv(node*);
};

#endif // AVLTREE_H
