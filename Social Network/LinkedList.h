//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_LINKEDLIST_H
#define SOCIAL_NETWORK_LINKEDLIST_H
#include <iostream>
#include "UserInfo.h"
#include "FriendsBST.h"
using namespace std;

struct node {
    UserInfo nodeUser;
    FriendsBST myTree;
    node* next;
};

class LinkedList {
public:
    node* head;
    node* tail;
    int count;
public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    bool isEmpty()const {
        return head == nullptr;
    }

    void print()const {
        node* current = head;
        while (current != nullptr) {
            cout << current->nodeUser << " ";
            current = current->next;
        }
    }

    int length()const {
        return count;
    }

    UserInfo& front()const {
        if (head != nullptr) { return head->nodeUser; }
        else { cout<<"Users List is empty!\n"; }
        UserInfo nullObj;
        return nullObj;
    }

    UserInfo& back()const {
        if (tail != nullptr) { return tail->nodeUser; }
        else { cout<<"Users List is empty!\n"; }
        UserInfo nullObj;
        return nullObj;
    }

    void deleteNode(UserInfo& deleteItem) {
        node* current=NULL;
        node* trailCurrent=NULL;
        bool found;
        if (head == NULL) {
            cout << "List is empty" << endl;
        }
        else {
            found = false;
            trailCurrent = head;
            current = head->next;
        }
        while (current != NULL && !found)
        {
            if (current->nodeUser.getName() != deleteItem.getName())
            {
                trailCurrent = current;
                current = current->next;
            }
            else {
                found = true;
            }
        }
        if (found == true) {
            trailCurrent->next = current->next;
            count--;
            if (tail == current) {
                tail = trailCurrent;
            }
            delete current;
        }
        else if (found == false) {
            cout << "Item is not found!" << endl;
        }
    }

    UserInfo& search(string username) {
        node* current;
        bool found = false;
        current = head;
        while (current != NULL && !found) {
            if (current->nodeUser.getUsername() == username) {
                found = true;
            }
            else {
                current = current->next;
            }
        }
        if(!found){
            UserInfo* temp= new UserInfo("","","");
            return *temp;
        }
        return current->nodeUser;
    }

    bool searchUserInFriendList(string username,string target){
        node* current;
        bool found = false;
        current = head;
        while (current != NULL && !found) {
            if (current->nodeUser.getUsername() == username) {
                found = true;
            }
            else {
                current = current->next;
            }
        }
        if(found){
            bool foundUser = current->myTree.Find(target);
            return foundUser;
        }else{
            cout<<"This user is not your friend! :(\n";
            return false;
        }
    }

    void add_Friends(string username,string target){
        node* current;
        node* newFriends;
        bool found = false;
        bool found_target=false;

        current = head;
        while (current != NULL && !found) {
            if (current->nodeUser.getUsername() == username) {
                found = true;
            }
            else {
                current = current->next;
            }
        }

        newFriends=head;
        while (newFriends!=NULL && !found_target){
            if(newFriends->nodeUser.getUsername() == target){
                found_target=true;
            }else{
                newFriends = newFriends->next;
            }
        }
        if(found_target && found) {
            if(current->myTree.Add(newFriends->nodeUser.getUsername(), &newFriends->nodeUser) &&
                    (newFriends->myTree.Add(current->nodeUser.getUsername(), &current->nodeUser)) ){
                cout << "User added to friends list\n";
            }else{
                cout<<"User is already in your friend list!\n";
            }
        }else {
            cout << "This user is not avalible\n";
        }
    }

    void remove_Friends(string username,string target){
        node* current;
        node* newFriends;
        bool found = false,found_target=false;
        newFriends=head;
        current = head;

        while (current != NULL && !found) {
            if (current->nodeUser.getUsername() == username) {
                found = true;
            }
            else {
                current = current->next;
            }
        }

        while (newFriends!=NULL && !found_target){
            if(newFriends->nodeUser.getUsername() == target){
                found_target=true;
            }else{
                newFriends = newFriends->next;
            }
        }

        if(found_target && found) {
            current->myTree.Remove(newFriends->nodeUser.getUsername(), current->nodeUser);
            newFriends->myTree.Remove(current->nodeUser.getUsername(), newFriends->nodeUser);
            cout << "User removed from friends list\n";
        }else {
            cout << "This user is not in your friends list\n";
        }
    }

    void peopleYouMayKnow(UserInfo user){
        cout<<"---------------People you may know------------------\n";
        string username = user.getUsername();
        node* current=head;
        int counter=0;
        while (current!=NULL && counter!=5){
            if(current->nodeUser.getUsername() == username){
                current=current->next;
                continue;
            }else if(current->myTree.Find(username)){
                current=current->next;
                continue;
            }else{
                cout<<"User "<<counter+1<<": \n";
                current->nodeUser.printInfo();
                current=current->next;
                counter++;
            }
        }
    }

    void FriendsList(string username) {
        node* current;
        bool found = false;
        current = head;
        while (current != NULL && !found) {
            if (current->nodeUser.getUsername() == username) {
                found = true;
            }
            else {
                current = current->next;
            }
        }

        if(found){
            if(current->myTree.isEmpty()){
                cout<<"Could not find any friends!  :(\n";
            }else {
                current->myTree.printInOrder();
            }
        }
    }

    void push_back(const UserInfo& newItem) {
        node* newNode = new node;
        newNode->nodeUser = newItem;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            count++;
        }
        else {
            tail->next = newNode;
            tail = newNode;
            count++;
        }

        string line2;
        ifstream myFile2 ("../all-users-relations.in");
        if (myFile2.is_open())
        {
            while ( getline (myFile2,line2) )
            {
                string str[2];
                int j=0;
                for(int i=0; i<line2.size(); i++) {
                    if(line2[i]==','){
                        i+=2;
                        j++;
                    }
                    str[j]+=line2[i];
                }
                if(str[0]==newNode->nodeUser.getUsername()) {
                    string USERS_INFO;
                    ifstream USERS_FILE ("../all-users.in");
                    if (USERS_FILE.is_open())
                    {
                        while ( getline (USERS_FILE, USERS_INFO) )
                        {
                            string users_line[3];
                            int x=0;
                            for(int z=0; z < USERS_INFO.size(); z++) {
                                if(USERS_INFO[z] == ','){
                                    z+=2;
                                    x++;
                                }
                                users_line[x]+=USERS_INFO[z];
                            }
                            if(users_line[0]==str[1]) {
                                UserInfo *temp = new UserInfo(users_line[0], users_line[1], users_line[2]);
                                newNode->myTree.Add(str[1], temp);
                            }
                        }
                        USERS_FILE.close();
                    }else {
                        cout << "Unable to open file";
                    }

                }else if(str[1]==newNode->nodeUser.getUsername()){
                    string USERS_INFO;
                    ifstream USERS_FILE ("../all-users.in");
                    if (USERS_FILE.is_open())
                    {
                        while ( getline (USERS_FILE, USERS_INFO) )
                        {
                            string users_line[3];
                            int x=0;
                            for(int z=0; z < USERS_INFO.size(); z++) {
                                if(USERS_INFO[z] == ','){
                                    z+=2;
                                    x++;
                                }
                                users_line[x]+=USERS_INFO[z];
                            }
                            if(users_line[0]==str[0]) {
                                UserInfo *temp = new UserInfo(users_line[0], users_line[1], users_line[2]);
                                newNode->myTree.Add(str[0], temp);
                            }
                        }
                        USERS_FILE.close();
                    }else {
                        cout << "Unable to open file";
                    }
                }else{
                    continue;
                }
            }
            myFile2.close();
        }else {
            cout << "Unable to open file";
        }
    }

    void printList(){
        node* cur=head;
        while (cur!= nullptr){
            cur->nodeUser.printInfo();
            cur=cur->next;
        }
    }

    void destroyList() {
        node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    ~LinkedList() { destroyList(); }
};


#endif //SOCIAL_NETWORK_LINKEDLIST_H
