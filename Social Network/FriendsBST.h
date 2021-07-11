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

    int calheight(nodeBST *p){
        if(p->left && p->right){
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }
        else if(p->left && p->right == NULL){
            return p->left->height + 1;
        }
        else if(p->left ==NULL && p->right){
            return p->right->height + 1;
        }
        return 0;
    }

    int bf(nodeBST *n){
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

    nodeBST * llrotation(nodeBST *n){
        nodeBST *p;
        nodeBST *tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp;
    }

    nodeBST * rrrotation(struct nodeBST *n){
        struct nodeBST *p;
        struct nodeBST *tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp;
    }

    nodeBST * rlrotation(nodeBST *n){
        struct nodeBST *p;
        struct nodeBST *tp;
        struct nodeBST *tp2;
        p = n;
        tp = p->right;
        tp2 =p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp;

        return tp2;
    }

    nodeBST * lrrotation(nodeBST *n){
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

    void Add(string username,UserInfo* user){
        root=insert(root,user,username);
    }
    nodeBST* insert(nodeBST *r,UserInfo* user,string username){

        if(r==NULL){
            nodeBST *n= new nodeBST;
            n->username = username;
            n->user=user;
            r = n;
            r->left = r->right = NULL;
            r->height = 1;
            return r;
        }
        else{
            if(username < r->username)
                r->left = insert(r->left, user,username);
            else
                r->right = insert(r->right, user,username);
        }

        r->height = calheight(r);

        if(bf(r)==2 && bf(r->left)==1){
            r = llrotation(r);
        }
        else if(bf(r)==-2 && bf(r->right)==-1){
            r = rrrotation(r);
        }
        else if(bf(r)==-2 && bf(r->right)==1){
            r = rlrotation(r);
        }
        else if(bf(r)==2 && bf(r->left)==-1){
            r = lrrotation(r);
        }

        return r;

    }

    nodeBST * deleteNode(nodeBST *p,UserInfo& user ,string username){

        if(p->left == NULL && p->right == NULL){
            if(p==this->root)
                this->root = NULL;
            delete p;
            return NULL;
        }

        nodeBST *t;
        nodeBST *q;
        if(p->username < username){
            p->right = deleteNode(p->right, user,username);
        }
        else if(p->username > username){
            p->left = deleteNode(p->left, user,username);
        }
        else{
            if(p->left != NULL){
                q = inpre(p->left);
                p->user = q->user;
                p->username=q->username;
                p->left=deleteNode(p->left,*q->user,q->username);
            }
            else{
                q = insuc(p->right);
                p->username = q->username;
                p->user = q->user;
                p->right = deleteNode(p->right,*q->user,q->username);
            }
        }

        if(bf(p)==2 && bf(p->left)==1){ p = llrotation(p); }
        else if(bf(p)==2 && bf(p->left)==-1){ p = lrrotation(p); }
        else if(bf(p)==2 && bf(p->left)==0){ p = llrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==-1){ p = rrrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==1){ p = rlrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==0){ p = llrotation(p); }
        return p;
    }

    void levelorder_newline(){
        if (this->root == NULL){
            cout<<"\n"<<"Empty tree"<<"\n";
            return;
        }
        levelorder_newline(this->root);
    }

    void levelorder_newline(nodeBST *v){
        queue <nodeBST *> q;
        nodeBST *cur;
        q.push(v);
        q.push(NULL);

        while(!q.empty()){
            cur = q.front();
            q.pop();
            if(cur == NULL && q.size()!=0){
                cout<<"\n";

                q.push(NULL);
                continue;
            }
            if(cur!=NULL){
                cout<<" "<<*(cur->user);

                if (cur->left!=NULL){
                    q.push(cur->left);
                }
                if (cur->right!=NULL){
                    q.push(cur->right);
                }
            }


        }
    }

    nodeBST* inpre(struct nodeBST* p){
        while(p->right!=NULL)
            p = p->right;
        return p;
    }

    struct nodeBST* insuc(struct nodeBST* p){
        while(p->left!=NULL)
            p = p->left;
        return p;
    }

    void Remove(string username,UserInfo& user){
        root=deleteNode(root,user,username);
    }


    //READY TO GO
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

    void inorder(nodeBST* p){
        if (p != NULL)
        {
            inorder(p->left);
            cout << *(p->user)<< " ";
            inorder(p->right);
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
