//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_FRIENDSBST_H
#define SOCIAL_NETWORK_FRIENDSBST_H
#include <iostream>
#include "UserInfo.h"

using namespace std;

struct nodeBST
{
    UserInfo* user;
    string username;
    nodeBST* left;
    nodeBST* right;
};

class friends{

};

class FriendsBST {
private:
    nodeBST* root;
    void inorder(nodeBST* p){
        if (p != NULL)
        {
            inorder(p->left);
            cout << *(p->user)<< " ";
            inorder(p->right);
        }
    }
public:
    FriendsBST():root{nullptr}{}
    bool isEmpty(){
        return (root== nullptr);
    }

    bool Find(string username){
        return false;
    }

    void Add(string username,UserInfo* user){
        nodeBST* current;
        nodeBST* trailCurrent = NULL;
        nodeBST* newNode;

        newNode = new nodeBST;
        newNode->user = user;
        newNode->username=username;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL)
            root = newNode;
        else
        {
            current = root;

            while (current != NULL)
            {
                trailCurrent = current;
                if (current->username == username)
                {
                    cout << "The insert item is already in the tree!";
                    cout << "duplicates are not allowed." << endl;
                    return;
                }
                else {
                    if (current->username> username)
                        current = current->left;
                    else
                        current = current->right;
                }
            }

            if (trailCurrent->username> username)
                trailCurrent->left = newNode;
            else
                trailCurrent->right = newNode;
        }
    }

    void printInOrder(){
        inorder(root);
    }
};


#endif //SOCIAL_NETWORK_FRIENDSBST_H
