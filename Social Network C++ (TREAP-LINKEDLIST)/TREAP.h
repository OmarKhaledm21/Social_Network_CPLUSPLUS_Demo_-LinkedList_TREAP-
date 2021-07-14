

#ifndef SOCIAL_NETWORK_TREAP_H
#define SOCIAL_NETWORK_TREAP_H
#include <iostream>
#include "UserInfo.h"
using namespace std;


struct nodeBST
{
    UserInfo* user;
    string username;
    int priority;
    nodeBST* left;
    nodeBST* right;
};

class TREAP {
    nodeBST* root;
public:
    TREAP();
    nodeBST* RightRotation(nodeBST* n);
    nodeBST* LeftRotation(nodeBST* n);
    bool Add(string username,UserInfo* user);
    nodeBST* insert(nodeBST *current, UserInfo* user, string username);
    nodeBST * deleteNode(nodeBST *current, UserInfo& user , string username);
    void Remove(string username,UserInfo& user);
    bool isEmpty();
    bool Find(string username);
    void inorder(nodeBST* traverser);
    void printInOrder();
    void clear_tree(nodeBST* traverser);

    ~TREAP();
};

#endif //SOCIAL_NETWORK_TREAP_H
