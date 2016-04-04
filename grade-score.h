#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person
{
    string firstname;
    string lastname;
    int score;

public:
    Person(string& fname, string& lname, int score);
    const string& FirstName() const;
    const string& LastName() const;
    int Score() const; 
    bool operator>(const Person& p) const;
    string AsString();
};

class Tokenizer
{
    vector<string> tokens;
    vector<string>::iterator current;

public:
    Tokenizer(const string& line, char delimiter);
    string GetToken();
    int Size() const;
private:
    void Split(const char* str, char c = ',');
};
