#include "grade-score.h"

Person::Person(string& fname, string& lname, int score)
:firstname(fname), lastname(lname), score(score)
{
}

const string& Person::FirstName() const 
{
    return firstname;
}

const string& Person::LastName() const 
{
    return lastname;
}

int Person::Score() const
{
    return score;
}

bool Person::operator>(const Person& p) const
{

    return(score > p.Score() || (score == p.Score() && lastname < p.LastName()) || (score == p.Score() && lastname == p.LastName() && firstname < p.FirstName()));
}

string Person::AsString()
{
    char buf[500];
    snprintf(buf, sizeof(buf), "%s, %s, %i", lastname.c_str(), firstname.c_str(), score);
    return string(buf);
}


Tokenizer::Tokenizer(const string& line, char delimiter)
{
    Split(line.c_str(), delimiter);
    current = tokens.begin();
}

string Tokenizer::GetToken()
{
    string token;
    if (current != tokens.end()) {
	token = *current;
        ++current;
    }
    return token; 
}

int Tokenizer::Size() const
{
    return tokens.size();
}

void Tokenizer::Split(const char* str, char c)
{
    do
    {
        // Skip blank
        while (*str == ' ') {
            str++;
	}
        const char *begin = str;
        
        while (*str != c  && *str != ' ' && *str) {
            str++;
        }
        tokens.push_back(string(begin, str));
    } while (0 != *str++);
    
}

bool compareName(const Person& a, const Person& b)
{
    return(a > b);
}

int main(int argc, char* argv[])
{
    vector<Person> personList;
    string line;
    if (argc < 2) {
        cout << "Missing input file" << endl;
        return -1;
    }


    ifstream infile(argv[1]);
    while (getline(infile, line)) {
        Tokenizer tokens = Tokenizer(line, ','); 
        if (tokens.Size() < 3)
	    continue;
        string lastname = tokens.GetToken();
        string firstname = tokens.GetToken();
        string score = tokens.GetToken();
        char* send;
        long int scorenum =  strtol(score.c_str(), &send, 10);
        if (scorenum == 0 && score != "0") {
	    continue;
        }
        personList.push_back(Person(firstname, lastname, scorenum)); 

    }
    infile.close();
    std::sort(personList.begin(), personList.end(), compareName);

    // write to an output file
    string filename = argv[1];
    size_t pos = filename.find_last_of(".");

    string ofilename;
    if (pos != string::npos)
        ofilename = filename.substr(0, pos) + "-sorted" + filename.substr(pos);
    else
	ofilename = filename + "-sorted.txt";
    
    ofstream outfile(ofilename.c_str());
    for (vector<Person>::iterator it = personList.begin(); it != personList.end(); ++it) {
        outfile << it->AsString() << endl << endl;
        cout << it->AsString() << endl << endl;
    }
    cout << "Finished: created " << ofilename << endl;
    outfile.close();
    return 0;
}

