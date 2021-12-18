#include <iostream>
#include<fstream>       //Is a file manipulation library
#include<string>
#include<conio.h>       //Used to monitor user keyboard events
#include<io.h>
#include<vector>
#include<windows.h>
#include<cmath>
#include<cassert>
#include"CPUusage.h"
//head own
using namespace std;
string PATH = R"(C:\ProgramData\lava\user\)";               //Global variable PATH  /* NOLINT */

void setColour(int x) {                                  //Define the font color function
    HANDLE h = GetStdHandle(-11);
    SetConsoleTextAttribute(h, x);
}

void getFiles(const string &path, vector<string> &files)          //View file functions
{
    long hFile;
    struct _finddata_t file_info{};
    string path_p;
    if ((hFile = _findfirst(path_p.assign(path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            if ((file_info.attrib & _A_SUBDIR)) {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
                    getFiles(path_p.assign(path).append("/").append(file_info.name), files);
                }
            } else {
                string file_str = file_info.name;
                files.push_back(file_str);
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    }
}

void registered(const string &User, const string &password)      //The registration function
{
    ofstream ofs;

    ofs.open(R"(C:\ProgramData\lava\nest\login\login.txt)");            //Open and create a file named "login. TXT "in C:\ProgramData\

    ofs << User
        << endl;                                            //Write the user name and password to the file respectively
    ofs << password << endl;

    ofs.close();                                                //Close the file
}

int login()                                                     //Log in function
{
    ifstream ifs;                                                //I'll call it ifstream and I'll call it "ifs"
    ifs.open(R"(C:\ProgramData\lava\nest\login\login.txt)", ios::in);    //Open the file
    if (!ifs.is_open())                                          //Error feedback
    {
        cout << "E:open file error" << endl;
    }
    string buf1;
    while (getline(ifs, buf1)) {                           //Loop twice to read validation
        string validation;
        cout << "input:(first time is the User name,second time is password)" << endl;
        cin >> validation;
        if (validation != buf1)                              //Error feedback
        {
            cout << "E: User. The password is incorrect or read incorrectly" << endl;
            return 0;
        }
    }
    cout << "---------------------------" << endl;
    ifs.clear();
    ifs.seekg(ios::beg);                                //Close the file and return the code
    return 1;
}

void release() {
    ofstream ofs;
    ofs.open(R"(C:\ProgramData\lava\nest\release.txt)");
    ofs << "release 0.1.02 SV [standard version]" << endl;
    ofs << "by CN_rh1" << endl;
}

void file_search(string path, const string &mode) {
    struct _finddata_t file_find{}; //A structure used to store information about a file
    if (path[path.size() - 1] == '\\')
        path.resize(path.size() - 1);
    string curr = path + "\\" + mode;//The file you want to find supports wildcard characters
//Wildcards are special statements. They are asterisks (*) and question marks (?). , used to obscure the search for files.
// You can use it instead of one or more real characters when searching for folders;
// It is common to use wildcard characters instead of one or more real characters when you do not know the real characters or are too lazy to enter a full name.
// Actually use "*Not? "Pad" can correspond to Notepad\MyNotepad [* can represent any string;? Only represents a single string, but the word must exist]
// The c_str() function returns a pointer constant to a normal C string, which is the same as this string
    int handle = _findfirst(curr.c_str(), &file_find);//First lookup
    if (-1 == handle)
        return;
    do {
        if (!strcmp(file_find.name, ".."))//If the directory is an upper-level directory, skip it
            continue;
        //---------process---------------
        curr = path + "\\" + file_find.name;
        cout << curr << endl;
        //------------------------------
        if (_A_SUBDIR == file_find.attrib)
            file_search(curr, mode);//Find subdirectories recursively

    } while (!(_findnext(handle, &file_find)));

    _findclose(handle);    //Don't forget to close the handle
}

void readTxt(const string &file) {
    ifstream infile;
    infile.open(file.data());   //Connect a file stream object to a file
    assert(infile.is_open());   //If it fails, an error message is output and the program is terminated

    string s;
    while (getline(infile, s)) {
        cout << s << endl;
    }
    infile.close();             //Close the file input stream
}

class product {                                          //Define a base class
public:
    virtual string chose(string input) = 0;               //Define a base class pure virtual function
};

class watch
        : public product {                             //Define the watch class and inherit from the base product class
public:
    string chose(string input) override {
        vector<string> folder;
        getFiles(PATH, folder);
        cout << folder.size() << endl;
        for (auto &i : folder)
            cout << i << endl;
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class net_new : public product {
public:
    string chose(string input) override {
        ofstream ofs;
        cout << "Enter file name" << endl;
        string file_name;
        cin >> file_name;
        ofs.open(PATH + file_name);
        cout << "input" << endl;
        while (input != "down_new") {
            cin >> input;
            ofs << input << endl;
        }
        ofs.close();
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class color : public product {
public:
    string chose(string input) override {
        cout << "what color do you want?" << endl;
        string color;
        cin >> color;
        if (color == "RED") {
            system("color 4A");
        } else if (color == "BLUE") {
            system("color 1A");
        } else if (color == "light") {
            system("color 0A");
        } else {
            cout << "do not have this color" << endl;
        }
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class word_color : public product {
public:
    string chose(string input) override {
        cout << "what color do you want?" << endl;
        string color;
        cin >> color;
        if (color == "BLUE") {
            setColour(1);
        }
        if (color == "RED") {
            setColour(4);
        }
        if (color == "dark") {
            setColour(8);
        } else {
            cout << "do not have this color" << endl;
        }
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class system_dos : public product {
public:
    string chose(string input) override {
        system("start cmd");
        string result = "down";
        cout << "--------------------------------------------" << endl;
        return result;
    }
};

class power : public product {
public:
    string chose(string input) override {
        cout << "You want to take a power of a number" << endl;
        cout << "Enter the number you want" << endl;
        long long num;
        cin >> num;
        cout << "Enter the power of the number you want" << endl;
        long long time;
        cin >> time;
        cout << pow(num, time) << endl;
        string result = "successful";
        cout << "--------------------------------------------" << endl;
        return result;
    }
};

class change_directory : public product {
public:
    string chose(string input) override {
        cout << "   ";
        string path;
        cin >> path;
        if (path == "nest") {
            PATH = R"(C:\ProgramData\lava\nest\)";
            return "down";
        }
        if (path == "home") {
            PATH = R"(C:\ProgramData\lava\user\)";
        }
        if (path == "else") {
            cout << "input path:" << "   " << endl;
            cin >> PATH;
        }
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class find_files : public product {
    string chose(string input) override {
        string mode;
        cout << "   ";
        cin >> mode;
        file_search(PATH, mode);
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class cat_files : public product {
    string chose(string input) override {
        cout << "   ";
        string name;
        cin >> name;
        readTxt(PATH + name);
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class pwd : public product {
    string chose(string input) override {
        cout << PATH << endl;
        cout << "--------------------------------------------" << endl;
        return "down";
    }
};

class not_find : public product {
    string chose(string input) override {
        cout << "commend no find,please try again" << endl;
        return "down";
    }
};

class cpu : public product {
    string chose(string input) override {
        CPUusage usg(12316);
        for (int i = 0; i < 10; i++) {
            float cpu = usg.get_cpu_usage();
            printf("Taskmgr.exe: %.2f%%\n", cpu);
            Sleep(500);
        }

        usg.setpid(11084);
        for (int i = 0; i < 10; i++) {
            float cpu = usg.get_cpu_usage();
            printf("devenv.exe: %.2f%%\n", cpu);
            Sleep(1000);
        }
        return "down";
    }
};

class Factory {                              // Define the FACTORY. Everything is determined in the FACTORY
public:
    static product *created(const string &input) {
        if (input == "wl") {
            return new watch;
        }
        if (input == "new") {
            return new net_new;
        }
        if (input == "color") {
            return new color;
        }
        if (input == "word_color") {
            return new word_color;
        }
        if (input == "sd") {
            return new system_dos;
        }
        if (input == "power") {
            return new power;
        }
        if (input == "cd") {
            return new change_directory;
        }
        if (input == "find") {
            return new find_files;
        }
        if (input == "lfinside") {
            return new cat_files;
        }
        if (input == "ld") {
            return new pwd;
        }
        if (input == "lcpu") {
            return new cpu;
        } else {
            return new not_find;
        }
    }
};

class w_worksh {
public:
    void warehouse() const {        // This indicates that this is an infinite loop function
        if (!cat) {
            cout << "worksh is starting work" << endl;
            release();
            string input;
            while (input != "power_off") {
                cout << PATH << "%%user:";
                cin >> input;
                cout << Factory::created(input)->chose(input) << endl;
            }
        }
        if (!nest) {
            cout << "nest is broken" << endl;
        }
        if (cat) {
            cout << "cat != false" << endl;
        }
    }

private:
    bool nest = true;
    bool cat = false;
};

/*
* CLASS area:
* Workshop triggers class;
* Workshop response class;
* Workshop class
* about the workshop

*/
class in_worksh {
public:
    static void in_() {
        cout << "input worksh" << endl;
        string work;
        cin >> work;
        if (work == "worksh") {
            cout << "down" << endl;
        } else {
            cout << "you must take this program down and try again" << endl;
        }
    }
};

class on_worksh {
public:
    static void _on() {
        cout << "worksh be true" << endl;
    }
};

int main() {
    system("color 0A");
    setColour(2);
    ofstream ofs;
    ifstream ifs;
    ifs.open(R"(C:\ProgramData\lava\nest\login\time.txt)", ios::in);             //Check whether the file exists
    if (!ifs) {
        system("md C:\\ProgramData\\lava");
        system(R"(md C:\ProgramData\lava\user)");
        system(R"(md C:\ProgramData\lava\nest)");
        system(R"(md C:\ProgramData\lava\nest\login)");
        ofs.open(R"(C:\ProgramData\lava\nest\login\time.txt)");
    }
    char active;
    string name;
    string password;
    cout << "Do you want to register a user?Y/N" << endl;
    cin >> active;
    if (active == 'Y') {
        cout << "enter your user name" << endl;
        cin >> name;
        cout << "enter your password" << endl;
        cin >> password;
        registered(name, password);
        cout << "login:" << endl;
        login();
    } else if (active == 'N') {

    } else {
        return 0;
    }
    cout << "pass" << endl;
    _getch();
    in_worksh::in_();
    on_worksh::_on();
    w_worksh ts2;
    ts2.warehouse();
}
