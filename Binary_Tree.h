
#ifndef ERGASIA_BINARY_TREE_H
#define ERGASIA_BINARY_TREE_H
#include <string>
#include "node.h"


class bst
{
private:
    node *root;
    bool insert (node *r, const string &data);
    node *search (string key);
    void inOrder (node *p);
    node  *min (node *start);
    node  *max (node *start);
    bool remove (node *child);
    int height (node *r);
    bool isBalanced (node *r);
    void destroyTree(node *r);
    void postOrder(node *p);
    void preOrder(node *p);
public:
    bst();
    ~bst();
    bool insert (const string &data);
    bool search (string key, string &ret);
    node* searchNode(string key,node* n);
    void InOrder ();
    bool min (string &m);
    bool max (string &m);
    bool remove (string key);
    int height ();
    bool isBalanced ();
    void searchQ(string *Q);
    void postOrder();
    void preOrder();


};

#endif //ERGASIA_BINARY_TREE_H
