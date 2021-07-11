//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_USERINFO_H
#define SOCIAL_NETWORK_USERINFO_H
#include <iostream>

using namespace std;

class UserInfo {
private:
    string username;
    string fullName;
    string emailAddress;


public:
    UserInfo(){
        username="";
        fullName="";
        emailAddress="";
    }
    UserInfo(string username,string fullName,string emailAddress){
        this->username=username;
        this->fullName=fullName;
        this->emailAddress=emailAddress;
    }

    string getName(){
        return fullName;
    }

    string getUsername(){
        return username;
    }



    void printInfo(){
        cout<<"Full Name: "<<this->fullName<<"\nEmail Address: "<<this->emailAddress<<endl<<"Username: "<<this->username<<endl;
    }

    bool operator==(UserInfo& right){
        return (this->fullName==right.fullName);
    }

    UserInfo operator=(const UserInfo& user){
        this->username=user.username;
        this->fullName=user.fullName;
        this->emailAddress=user.emailAddress;
        return *this;
    }

    friend ostream& operator << (ostream& out, UserInfo b){
        out<<"User Info: "<<endl;
        out<<"Full Name: "<<b.fullName<<"\nEmail Address: "<<b.emailAddress<<endl<<"Username: "<<b.username<<endl<<endl;
        return out;
    }
};


#endif //SOCIAL_NETWORK_USERINFO_H
