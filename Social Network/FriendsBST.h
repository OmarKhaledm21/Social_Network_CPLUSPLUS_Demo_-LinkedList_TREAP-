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

    void Remove(string username){
        nodeBST* current;
        nodeBST* trailCurrent;

        if (root == NULL)
        {
            cout << "The tree is empty!" << endl;
            return;
        }

        if (root->username == username)
        {
            deleteFromTree(root);
            return;
        }

        trailCurrent = root;

        if (root->username > username)
            current = root->left;
        else
            current = root->right;

        //search for the item to be deleted.
        while (current != NULL)
        {
            if (current->username == username)
                break;
            else
            {
                trailCurrent = current;
                if (current->username > username)
                    current = current->left;
                else
                    current = current->right;
            }
        }

        if (current == NULL)
            cout << "User is not in your friend list!" << endl;
        else if (trailCurrent->username > username) {
            deleteFromTree(trailCurrent->left);
        }
        else{
            deleteFromTree(trailCurrent->right);
        }
    }

    void deleteFromTree(nodeBST*& node){
        nodeBST* current;
        nodeBST* trailCurrent;
        nodeBST* temp;

        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            node = NULL;
        }
        else if (node->left == NULL)
        {
            temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == NULL)
        {
            temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            current = node->left;
            trailCurrent = NULL;

            while (current->right != NULL)
            {
                trailCurrent = current;
                current = current->right;
            }

            node->username = current->username;
            node->user=current->user;

            if (trailCurrent == NULL)
                node->left = current->left;
            else
                trailCurrent->right = current->left;

            delete current;
        }
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
                    cout << "The user is already a friend!\n";
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

    void clear_tree(nodeBST* node){
        if (node != NULL)
        {
            clear_tree(node->left);
            clear_tree(node->right);
            delete node;
            node = NULL;
        }
    }

    ~FriendsBST(){
        clear_tree(root);
    }
};


#endif //SOCIAL_NETWORK_FRIENDSBST_H
