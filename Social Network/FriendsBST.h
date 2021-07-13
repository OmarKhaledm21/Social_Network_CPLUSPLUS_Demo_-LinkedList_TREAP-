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
    int priority;
    nodeBST* left;
    nodeBST* right;
};

class FriendsBST {
public:
    nodeBST* root;

    FriendsBST():root{nullptr}{}

    nodeBST* RightRotation(nodeBST* n){
        nodeBST* temp = n->left;
        n->left = temp->right;
        temp->right = n;
        return temp;
    }

    nodeBST* LeftRotation(nodeBST* n){
        nodeBST* temp = n->right;
        n->right = temp->left;
        temp->left = n;
        return temp;
    }

    bool Add(string username,UserInfo* user){
        if(Find(username)){
            return false;
        }else {
            root = insert(root, user, username);
            return true;
        }
    }

    nodeBST* insert(nodeBST *current, UserInfo* user, string username){
        if(current == NULL){
            nodeBST *n= new nodeBST;
            n->username = username;
            n->user=user;
            n->priority = rand() % 100;
            current = n;
            current->left = current->right = NULL;
            //current->height = 1;
            return current;
        }
        else {
            if (username < current->username) {
                current->left = insert(current->left, user, username);
                if (current->priority > current->left->priority) {
                    current = RightRotation(current);
                }
            } else {
                current->right = insert(current->right, user, username);
                if(current->priority> current->right->priority){
                    current= LeftRotation(current);
                }
            }
        }
        return current;

    }

    nodeBST * deleteNode(nodeBST *current, UserInfo& user , string username){
        if(current== nullptr){
            return current;
        }

        if(current->username < username){
            current->right = deleteNode(current->right, user, username);
            return current;
        }
        else if(current->username > username){
            current->left = deleteNode(current->left, user, username);
            return current;
        }
        if(current->right== nullptr){
            nodeBST* temp;
            temp=current;
            current= current->left;
            delete temp;
        }else if(current->left== nullptr){
            nodeBST* temp;
            temp=current;
            current=current->right;
            delete temp;
        }else{
            if(current->left->priority > current->right->priority){
                current = LeftRotation(current);
                current->left = deleteNode(current->left,user,username);
            }else{
                current = RightRotation(current);
                current->right = deleteNode(current->right,user,username);
            }
        }
        return current;
    }


    void Remove(string username,UserInfo& user){
        root=deleteNode(root,user,username);
    }
    
    bool isEmpty(){
        return (root== nullptr);
    }

    bool Find(string username){
        nodeBST* current = root;

        while (current != NULL)
        {
            if (current->username == username)
                return true;
            else if (current->username > username)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    void inorder(nodeBST* traverser){
        if (traverser != NULL)
        {
            inorder(traverser->left);
            cout << *(traverser->user) << " ";
            inorder(traverser->right);
        }
    }

    void printInOrder(){
        inorder(root);
    }

    void clear_tree(nodeBST* traverser){
        if (traverser != NULL)
        {
            clear_tree(traverser->left);
            clear_tree(traverser->right);
            delete traverser;
            traverser = NULL;
        }
    }

    ~FriendsBST(){
        clear_tree(root);
    }
};

#endif //SOCIAL_NETWORK_FRIENDSBST_H
