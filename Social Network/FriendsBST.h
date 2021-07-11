//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_FRIENDSBST_H
#define SOCIAL_NETWORK_FRIENDSBST_H
#include <iostream>
#include "UserInfo.h"
#include "queue"
using namespace std;

struct nodeBST
{
    UserInfo* user;
    string username;
    int height;
    nodeBST* left;
    nodeBST* right;
};

class FriendsBST {
public:
    nodeBST* root;

    FriendsBST():root{nullptr}{}

    int getHeight(nodeBST *n){
        if(n->left && n->right){
            if (n->left->height < n->right->height)
                return n->right->height + 1;
            else return n->left->height + 1;
        }
        else if(n->left && n->right == NULL){
            return n->left->height + 1;
        }
        else if(n->left == NULL && n->right){
            return n->right->height + 1;
        }
        return 0;
    }

    int getBalanceFactor(nodeBST *n){
        if(n->left && n->right){
            return n->left->height - n->right->height;
        }
        else if(n->left && n->right == NULL){
            return n->left->height;
        }
        else if(n->left== NULL && n->right ){
            return -n->right->height;
        }
    }

    nodeBST * LeftLeftRotation(nodeBST *n){
        nodeBST *p;
        nodeBST *tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp;
    }

    nodeBST * RightRightRotation(struct nodeBST *n){
        nodeBST *p;
        nodeBST *tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp;
    }

    nodeBST * RightLeftRotation(nodeBST *n){
        nodeBST *p;
        nodeBST *tp;
        nodeBST *tp2;
        p = n;
        tp = p->right;
        tp2 =p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp;

        return tp2;
    }

    nodeBST * LeftRightRotation(nodeBST *n){
        struct nodeBST *p;
        struct nodeBST *tp;
        struct nodeBST *tp2;
        p = n;
        tp = p->left;
        tp2 =p->left->right;

        p -> left = tp2->right;
        tp ->right = tp2->left;
        tp2 ->right = p;
        tp2->left = tp;

        return tp2;
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
            current = n;
            current->left = current->right = NULL;
            current->height = 1;
            return current;
        }
        else{
            if(username < current->username)
                current->left = insert(current->left, user, username);
            else
                current->right = insert(current->right, user, username);
        }

        current->height = getHeight(current);

        if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == 1){
            current = LeftLeftRotation(current);
        }
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == -1){
            current = RightRightRotation(current);
        }
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1){
            current = RightLeftRotation(current);
        }
        else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1){
            current = LeftRightRotation(current);
        }

        return current;

    }

    nodeBST * deleteNode(nodeBST *current, UserInfo& user , string username){

        if(current->left == NULL && current->right == NULL){
            if(current == this->root)
                this->root = NULL;
            delete current;
            return NULL;
        }

        nodeBST *t;
        nodeBST *q;
        if(current->username < username){
            current->right = deleteNode(current->right, user, username);
        }
        else if(current->username > username){
            current->left = deleteNode(current->left, user, username);
        }
        else{
            if(current->left != NULL){
                q = predecessor(current->left);
                current->user = q->user;
                current->username=q->username;
                current->left=deleteNode(current->left, *q->user, q->username);
            }
            else{
                q = successor(current->right);
                current->username = q->username;
                current->user = q->user;
                current->right = deleteNode(current->right, *q->user, q->username);
            }
        }

        if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == 1){
            current = LeftLeftRotation(current);
        }else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1){
            current = LeftRightRotation(current);
        }else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == 0){
            current = LeftLeftRotation(current);
        }else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == -1){
            current = RightRightRotation(current);
        }else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1){
            current = RightLeftRotation(current);
        }else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 0){
            current = LeftLeftRotation(current);
        }
        return current;
    }

    void printAVL_levelOrder(){
        if (this->root == NULL){
            cout<<"\n"<<"Empty tree"<<"\n";
            return;
        }
        levelorder(this->root);
    }

    void levelorder(nodeBST *root){
        queue <nodeBST *> q;
        nodeBST *current;
        q.push(root);
        q.push(NULL);

        while(!q.empty()){
            current = q.front();
            q.pop();
            if(current == NULL && q.size() != 0){
                cout<<"\n";
                q.push(NULL);
                continue;
            }
            if(current != NULL){
                cout<<" "<<*(current->user);
                if (current->left != NULL){
                    q.push(current->left);
                }
                if (current->right != NULL){
                    q.push(current->right);
                }
            }
        }
    }

    nodeBST* predecessor(nodeBST* myNode){
        while(myNode->right != NULL) {
            myNode = myNode->right;
        }
        return myNode;
    }

    nodeBST* successor(nodeBST* myNode){
        while(myNode->left != NULL) {
            myNode = myNode->left;
        }
        return myNode;
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
