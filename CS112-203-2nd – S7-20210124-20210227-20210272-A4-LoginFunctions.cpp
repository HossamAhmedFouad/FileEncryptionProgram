// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: xxxxxx.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: xxxxx xxxxx
// Author2 and ID and Group: xxxxx xxxxx
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: xxxxx xxxxx
// Purpose:..........

#include <bits/stdc++.h>
#include <iostream>
#include <regex>
#include<conio.h>
#include<cstdio>
using namespace std;

bool ValidateUsername(string& username);
bool ValidatePassword(string& password);
bool confirm_pass(const string& reentered_pass,const string& password);
bool ValidateEmail(string& email);
bool ValidateID(string& id);
bool ValidateMobile(string& mobile);
void LoadDataBase();
pair<int,bool> ValidateLogin(string& id, string& pass);
vector<string>WordReader(string& line);
int Login();
vector<string>WordReader(string& line);
void Register();
/**
*STRUCTURE
*/
struct User{

    string username{},email{},password{},id{},mobile{};
    vector<string>oldPasswords{};

};
vector<User>users{};
/**
* DEBUG
*/
ostream& operator<<(ostream& out , vector<string>&data){
    out<<"[";
    for (string& word : data) {
        out<<word<<", ";
    }
    out<<"]";
    return out;
}

ostream& operator<<(ostream& out, vector<User>&data){
    for(User user : data){
        out<<user.username<<" " << user.password << " " << user.id<<endl;
    }
    return out;
}

int main(){

    //Test Your Code Here
 
    return 0;
}
/**
 * Load Data Base Users
 */
void LoadDataBase() {
    string result;
    bool read;
    fstream file;
    file.open("dataBase.txt", ios::in);
    string currentLine{};
    vector<string> words{};
    while (getline(file, currentLine)) {
        words = WordReader(currentLine);
        cout<<words<<endl;
        if (words.size() > 0) {
            if (words[0] == "USER") {
                User newUser;
                users.push_back(newUser);
            }else{
                words = WordReader(currentLine);
                if (words[0] == "Username") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].username = result;
                    result.clear();
                } else if (words[0] == "Password") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].password = result;
                    result.clear();
                } else if (words[0] == "Email") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].email = result;
                    result.clear();
                } else if (words[0] == "Mobile") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].mobile = result;
                    result.clear();
                } else if (words[0] == "Old") {
                    for (int i = 1; i < words.size(); ++i) {
                        users[users.size()-1].oldPasswords.push_back(words[i]);
                    }
                }

            }
        }
    }
    file.close();
}

/**
* User Registeration
*/

//Validation Functions

bool ValidateUsername(string& username){
    regex validUsername("[a-zA-z\\-]+");

    return regex_match(username,validUsername);
}

bool ValidatePassword(string& password){
    //Default State
    bool correct = false;
    bool upper_case{false},lower_case{false},digit{false},special_char{false},size{false};
    int sum;
    for(int i=0;i<password.size();i++){
        if (password.size()>8){
            size= true;
            if (islower(password[i])){
                lower_case= true;
            }
            if(isupper(password[i])){
                upper_case= true;
            }
            if(isdigit(password[i])){
                digit= true;
            }
            else {
                special_char = true;
            }
        }

    }
    sum=upper_case+lower_case+digit+special_char+size;
    if(sum==5){
        correct=true;
    }
    return correct;
}

bool confirm_pass(const string& reentered_pass,const string& pass){
    if(reentered_pass==pass){
        return true;
    }
    return false;
}

bool ValidateEmail(string& email){
    
    regex validEmail("[^\\.]+[\\.]?[0-9A-Za-z.]*@[0-9A-Za-z]*[A-Za-z]+[0-9]*([A-Za-z0-9]+[\\-][A-Za-z0-9]+)?\\.[a-z]+");
    
    return regex_match(email,validEmail);
}

bool ValidateID(string& id){
    
     regex validID("[^\\s]+");

    if(regex_match(id,validID)){
        for(User& user : users){
            if(user.id == id){
                cout<<"\nID already taken, please choose another one"<<endl;
                return false;
            }
        }
        return true;

    } else{
        cout<<"Invalid ID format, please try again"<<endl;
        return false;
    }
}

bool ValidateMobile(string& mobile){
    
    regex validMobile("(01)([0]{1}([1690]))?([0]{2})?([1]{1}([142]))?([2]{1}[0278])?([0-9]{7})");

    return regex_match(mobile,validMobile);
}

/**
*Read From Data Base File Word By Word
*/
vector<string> WordReader(string& line){
    vector<string>words{};
    string result{};
    int i = 0;
    while (i<line.size()){
        while (!isspace(line[i]) && i<line.size()){
            result.push_back(line[i]);
            i++;
        }
        if(result.size()>0){
            words.push_back(result);
        }
        result.clear();
        i++;
    }
    return words;
}

//Main Registration Function
void take_password(string& password){
        char x;
        int i = 0;
        while (true){
            x = _getch();
            if (x== '\b' && i > 0){
                i--;
                password.pop_back();
                printf("\b \b");
            }
            else if (x == '\r'){
                cout << endl;
                break;
            }
            else {
                password.push_back(x);
                i++;
                cout << '*';
            }
        }
    }

void Register() {

    User newUser;
    cout << "Enter Username: ";
    getline(cin, newUser.username);


    while(!ValidateUsername(newUser.username)){
        
        cout << "\nInvalid Username Format, please try again" << endl;
        cout << "Enter Username: ";
        getline(cin, newUser.username);

    }
   
    cout << endl;
    cout<<"password must be not less than 8 characters,and contain at least one uppercase&lowercase&special character"<<endl;
    string reentered_pass;
    cout<<"please,enter a new password:";
    take_password(newUser.password);
    cout<<"please,enter password again:";
    take_password(reentered_pass);
    while (!confirm_pass(reentered_pass, newUser.password)){
        cout<<"not the same,please enter same password:";
        take_password(reentered_pass);
    }
    while(!ValidatePassword(newUser.password)){
        cout<<"password is weak,please enter password again:";
        take_password(newUser.password);
        cout<<"please,enter password again:";
        take_password(reentered_pass);
        while(!confirm_pass(reentered_pass,newUser.password)){
            cout<<"not the same,please enter same password:";
            take_password(reentered_pass);
        }
    }

    cout << endl;
    cout << "Enter ID: ";
    getline(cin, newUser.id);

    while (!ValidateID(newUser.id)){

        cout << "Enter ID: ";

        getline(cin, newUser.id);

    }

    cout << endl;
    cout << "Enter Email: ";
    getline(cin, newUser.email);

    while (!ValidateEmail(newUser.email)){

        cout << "\nInvalid Email Format, please try again" << endl;
        cout << "Enter Email: ";
        getline(cin, newUser.email);

       }

    cout << endl;
    cout << "Enter Mobile: ";
    getline(cin, newUser.mobile);

    while (!ValidateMobile(newUser.mobile)){

        cout << "\nInvalid mobile format, please try again" << endl;
        cout << "Enter Mobile: ";
        getline(cin, newUser.mobile);

    }

    //Opening Data Base File
    fstream file;
    file.open("dataBase.txt", ios::app);

    //Registering user to data base
    users.push_back(newUser);
    cout<<endl;
    cout<<users.size()<<endl;
    if (file.is_open()) {
        file << "USER " << users.size() << ":" << "\n";
        file << "    Username     : " << newUser.username << "\n";
        file << "    Password     : " << newUser.password << "\n";
        file << "    ID           : " << newUser.id << "\n";
        file << "    Email        : " << newUser.email << "\n";
        file << "    Mobile       : " << newUser.mobile << "\n";
        file << "    Old Passwords: ";
        for (int i = 0; i <newUser.oldPasswords.size(); ++i) {
            //ADD ENCRYPTION HERE
            file<<newUser.oldPasswords[i]<<" ";
        }
        file<<endl;
        file<<endl;
        file.close();
    }
}
pair<int,bool>ValidateLogin(string& id, string& pass) {
    bool foundID{false}, correctPass{false};
    pair<int, bool> result;
    int counter = -1;
    for (User &user: users) {
        counter++;
        if (user.id == id) {
            foundID = true;
            if (user.password == pass) {
                correctPass = true;
                result.first = counter;
                result.second = foundID && correctPass;
            }
            break;
        }
    }
    return result;
}

/**
* User Login
*/


int Login(){
    User newUser;
    int counter{0};
    cout<<"Enter ID: ";
    getline(cin,newUser.id);
    cout<<endl;
    cout<<"Enter Password: ";
    TakePassword(newUser.password);
    pair<int,bool>res = ValidateLogin(newUser.id,newUser.password);
    while (!res.second && counter<2){
        counter++;
        cout<<"\nInvalid ID or password, please try again"<<endl;
        cout<<"Enter ID: ";
        getline(cin,newUser.id);
        cout<<"Enter Password: ";
        TakePassword(newUser.password);
        res = ValidateLogin(newUser.id,newUser.password);
    }
    if (counter==2){
        cout<<"Too many trials, ACCESS DENIED"<<endl;
    }else{
        cout<<"Success! Welcome " << users[res.first].username <<endl;
    }

    return res.first;
}


/**
* Change Password
*/
void ChangePassword(){
        string OldPass, NewPass, ReenteredNewPassword;
        Login();
        cout << "please enter your old password:";
        take_password(OldPass);
    while(OldPass!=users[indexuser-1].password){
        cout<<"wrong password,please try again:";
        take_password(OldPass);
    }
        cout << "enter new password";
        take_password(NewPass);
        users[indexuser].oldPasswords.push_back(OldPass);
        users[indexuser].password = NewPass;
        fstream file;
        file.open("dataBase.txt", ios::in);
        string currentLine{};
        vector<string> words{};
        fstream file_out;
        file_out.open("modified.txt", ios::app);
        while (getline(file, currentLine)) {
            words = WordReader(currentLine);
            if (words.size() > 0) {
                if (words[1] == to_string(indexuser+1)) {
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    currentLine = "    Password     : " + NewPass;
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    file_out << currentLine << endl;
                    getline(file, currentLine);
                    for (int i = 0; i < OldPass.size(); i++) {
                        currentLine.push_back(OldPass[i]);
                    }
                    currentLine.push_back(' ');
                    file_out << currentLine << endl;

                } else {
                    file_out << currentLine << endl;
                }
            }
        }
        file.close();
        file_out.close();
        currentLine.clear();
        file.open("dataBase.txt", ios::out);
        file_out.open("modified.txt", ios::in);
        while (getline(file_out, currentLine)) {
            file << currentLine << endl;
        }
        file_out.close();
        file.close();
        file_out.open("modified.txt", ios::out);
        file_out.close();

}


