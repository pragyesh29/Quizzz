#include<iostream>
#include<fstream>
#include<vector>
#include<limits>
#include<stdio.h>
#include<Windows.h>
#include<chrono>
#include<conio.h>
using namespace std;

int curr_score = 0;
void CoutCentered(string);

class Student{
    public:
    string name;
    int rollno;

    Student(){
        name = "";
        rollno = 0;
    }

    void inputDetails(){
        cout << "Enter Name : "; cin >> name;
        cout << "Enter Roll Number : "; cin >> rollno;
    }

    void showDetails(){
        // TODO
    }
};

void welcome(){
    system("CLS");
    cout<<"\n\n\n\t\t\t\t   __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
    cout<<"\t\t\t\t   \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
    cout<<"\t\t\t\t    \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
    cout<<"\t\t\t\t     \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
    _getch();
}

//enumeration is a user-defined data type
enum color{ 
	NONE, DARK_BLUE, GREEN, DARK_CYAN, DARK_RED, PURPLE, DARK_YELLOW, NORMAL, GRAY, BLUE, LIME, CYAN, RED, PINK, YELLOW, WHITE
};

void setcolor   (color newColor) 
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something.
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (newColor ) );
}


void readFile(){
    fstream f("data.csv", ios::in);

    // skip the first 1st line from file
    f.seekg(std::ios::beg);
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Beep(450, 650);
    while(!f.eof()){
        string s = "";
        getline(f, s);
        vector<string> record;
        int tmp = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i]=='$'){
                record.push_back(s.substr(tmp, i-tmp));
                tmp = i+1;
            }
        }

        // Extracted question with option and correct answer from file and stored in 'record' vector
        system("CLS");
        // TODO
        // Change the color and do decorations here
        cout << "Question " << record[0] << ") " << record[1] << '\n';

        HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console_color, 30);

        cout << "1) " << record[2] << '\n';
        cout << "2) " << record[3] << '\n';
        cout << "3) " << record[4] << '\n';
        cout << "4) " << record[5] << '\n';
        SetConsoleTextAttribute(console_color, 7);
        // Ask for answer
        int ch; ch = 0;
        while(ch < 1 || ch > 4){
            cout << "Answer: ";
            cin >> ch;
            if(ch < 1 || ch > 4){
                setcolor(YELLOW);
                CoutCentered("Invalid choice!!\nChoice must be between 1 to 4");
                // cout << "Invalid choice!!\nChoice must be between 1 to 4\n";
                setcolor(NORMAL);
                system("PAUSE");
                system("CLS");
                // TODO
                // Change the color and do decorations here
                cout << "Question " << record[0] << ") " << record[1] << '\n';
                cout << "1) " << record[2] << '\n';
                cout << "2) " << record[3] << '\n';
                cout << "3) " << record[4] << '\n';
                cout << "4) " << record[5] << '\n';
            }
        }
        if(record[ch+1] == record[6]){
            // Increment the score for correct answer
            curr_score += 10;
            setcolor(GREEN);
            CoutCentered("CORRECT ANSWER :)");
            _getch();
            setcolor(NORMAL);
            system("CLS");
        }else{
            setcolor(RED);
            CoutCentered("Wrong Answer :(");
            _getch();   
            setcolor(NORMAL);
            system("CLS");
            // TODO: Show score screen now
            break;
        }
    }
}

void CoutCentered(std::string text) {
    // This function will only center the text if it is less than the length of the console!
    // Otherwise it will just display it on the console without centering it.

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle.
    PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO(); // Create a pointer to the Screen Info pointing to a temporal screen info.
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo); // Saves the console screen info into the lpScreenInfo pointer.
    COORD NewSBSize = lpScreenInfo->dwSize; // Gets the size of the screen
    if (NewSBSize.X > text.size()) {
        int newpos = ((NewSBSize.X - text.size()) / 2); // Calculate the number of spaces to center the specific text.
        for (int i = 0; i < newpos; i++) std::cout << " "; // Prints the spaces
    }
    std::cout << text << std::endl; // Prints the text centered :]
}

int main(){
    welcome();
    readFile();
    return 0;
}