
#ifndef SOCIAL_NETWORK_LINKEDLIST_H
#define SOCIAL_NETWORK_LINKEDLIST_H
#include <iostream>
#include <fstream>
#include <string>
#include "UserInfo.h"
#include "TREAP.h"
using namespace std;


struct node {
    UserInfo nodeUser;
    TREAP myTreap;
    node* next;
};

class LinkedList {
public:
    node* head;
    node* tail;
    int count;
public:
    LinkedList();
    bool isEmpty()const;
    void print()const ;
    int length()const;
    UserInfo& front()const ;
    UserInfo& back()const ;
    void deleteNode(UserInfo& deleteItem) ;
    UserInfo& search(string username);
    bool searchUserInFriendList(string username,string target);
    void add_Friends(string username,string target);
    void remove_Friends(string username,string target);
    void peopleYouMayKnow(UserInfo user);
    void FriendsList(string username) ;
    void push_back(const UserInfo& newItem);
    void printList();
    void destroyList();
    ~LinkedList();
};


#endif //SOCIAL_NETWORK_LINKEDLIST_H
