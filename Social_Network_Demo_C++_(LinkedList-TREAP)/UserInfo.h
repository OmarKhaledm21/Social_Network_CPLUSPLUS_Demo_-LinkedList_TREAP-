
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
    UserInfo();
    UserInfo(string username, string fullName, string emailAddress);
    string getName();
    string getUsername();
    void printInfo();
    bool operator==(UserInfo &right);
    UserInfo operator=(const UserInfo &user);
    friend ostream &operator<<(ostream &out, UserInfo user);
};
#endif //SOCIAL_NETWORK_USERINFO_H
