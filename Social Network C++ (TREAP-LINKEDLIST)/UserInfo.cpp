
#include "UserInfo.h"
UserInfo::UserInfo(){
    username="";
    fullName="";
    emailAddress="";
}

UserInfo::UserInfo(string username,string fullName,string emailAddress){
    this->username=username;
    this->fullName=fullName;
    this->emailAddress=emailAddress;
}

string UserInfo::getName(){
    return fullName;
}

string UserInfo::getUsername(){
    return username;
}

void UserInfo::printInfo(){
    cout<<"Full Name: "<<this->fullName<<"\nEmail Address: "<<this->emailAddress<<endl<<"Username: "<<this->username<<endl;
}

bool UserInfo::operator==(UserInfo& right){
    return (this->fullName==right.fullName);
}

UserInfo UserInfo::operator=(const UserInfo& user){
    this->username=user.username;
    this->fullName=user.fullName;
    this->emailAddress=user.emailAddress;
    return *this;
}

ostream& operator << (ostream& out, UserInfo user){
    out<<"User Info: "<<endl;
    out << "Full Name: " << user.fullName << "\nEmail Address: " << user.emailAddress << endl << "Username: " << user.username << endl << endl;
    return out;
}