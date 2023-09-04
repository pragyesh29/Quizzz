#include<bits/stdc++.h>
#include<conio.h>
#include<Windows.h>
using namespace std;

int curr_score = 0;
void CoutCentered(string);
void CoutCentered(int);
void CoutCentered(string, int);

//enumeration is a user-defined data type
enum color{ 
	NONE, DARK_BLUE, GREEN, DARK_CYAN, DARK_RED, PURPLE, DARK_YELLOW, NORMAL, GRAY, BLUE, LIME, CYAN, RED, PINK, YELLOW, WHITE
};

void setcolor   (color newColor) 
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something.
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (newColor ) );
}

class Student{
    public:
    char name[20];
    int rollno;

    Student(){
        for(int i = 0; i < 20; i++) name[i]='\0';
        rollno = 0;
    }

    void inputDetails(){
        system("CLS");
        setcolor(BLUE);
        cout << "Enter First Name : ";
        cin.getline(name, 20);
        system("CLS");
        setcolor(DARK_CYAN);
        cout << "Enter Roll Number : "; cin >> rollno;
        system("CLS");
        setcolor(NORMAL);
    }

    void putScore(int score){
        fstream f("history.csv", ios::in|ios::out|ios::app);
        for(int i = 0; i < 20; i++){
            if(name[i] != '\0') f << name[i];
            else break;
        }
        f << ',' << rollno << ',' << score << ',' << '\n';
        f.close();
    }

    void showDetails(){
        fstream f;
        f.open("history.csv", ios::in);
        cout << "NAME                " << "ROLL NUMBER    " << "SCORE" << '\n';
        while(!f.eof()){
            string s;
            getline(f, s);
            vector<string> record;
            int j = 0;
            for(int i = 0; i < s.size(); i++){
                if(s[i] == ','){
                    record.push_back(s.substr(j, i-j));
                    j = i+1;
                }
            }
            cout << record[0];
            for(int i = 0; i < 20-record[0].size(); i++) cout << " ";
            cout << record[1];
            for(int i = 0; i < 15-record[1].size(); i++) cout << " ";
            cout << record[2];
            cout << '\n';
        }
        _getch();
        system("CLS");
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


int readFile(){
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

        int maxtime = stoi(record[7]);
        do{
            // Extracted question with option and correct answer from file and stored in 'record' vector
            system("CLS");
            // TODO
            // Change the color and do decorations here

            cout << '\n';
            setcolor(RED);
			CoutCentered(maxtime);
            setcolor(NORMAL);

            cout << "Question " << record[0] << ") " << record[1] << "\n\n";

            HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_color, 15);
            cout << "1) " << record[2] << "\n\n";
            cout << "2) " << record[3] << "\n\n";
            cout << "3) " << record[4] << "\n\n";
            cout << "4) " << record[5] << "\n\n";
            SetConsoleTextAttribute(console_color, 7);
            // Ask for answer

            if(_kbhit()){
                char ch = _getch();

                // TODO: What if user entered invalid choice? Check for that case.

                if(record[(ch-'0')+1] == record[6]){
                    // Increment the score for correct answer
                    curr_score += stoi(record[8]);
                    setcolor(GREEN);
                    CoutCentered("CORRECT ANSWER :)");
                    setcolor(NORMAL);
                    _getch();
                    system("CLS");
                    break;
                }else{
                    setcolor(RED);
                    CoutCentered("Wrong Answer :(");
                    setcolor(NORMAL);
                    _getch();   
                    system("CLS");
                    break;
                }
            }
            setcolor(PINK);
            CoutCentered("Your current score is", curr_score);
            setcolor(NORMAL);
			Sleep(1000);
            maxtime--;
        }while(maxtime!=0);
    }
    
    // TODO: Show score screen now
    system("CLS");
    CoutCentered("YOUR SCORE IS");
    CoutCentered(curr_score);
    if(curr_score < 100){
        setcolor(RED);
        CoutCentered("Work Hard!!!");
    }else if(curr_score >= 100 && curr_score <= 150){
        setcolor(YELLOW);
        CoutCentered("Good, keep working hard!!");
    }else if(curr_score > 151 && curr_score < 180){
        setcolor(DARK_CYAN);
        CoutCentered("Great, keep it up!!");
    }else{
        setcolor(LIME);
        CoutCentered("Excellent!!");
    }
    setcolor(NORMAL);
    _getch();
    system("CLS");
    return curr_score;
}

void CoutCentered(string text) {
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

// Overloading
void CoutCentered(int n) {
    // This function will only center the text if it is less than the length of the console!
    // Otherwise it will just display it on the console without centering it.

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle.
    PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO(); // Create a pointer to the Screen Info pointing to a temporal screen info.
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo); // Saves the console screen info into the lpScreenInfo pointer.
    COORD NewSBSize = lpScreenInfo->dwSize; // Gets the size of the screen
    
    int size = ceil(log10(n));

    if (NewSBSize.X > size) {
        int newpos = ((NewSBSize.X - size) / 2); // Calculate the number of spaces to center the specific text.
        for (int i = 0; i < newpos; i++) std::cout << " "; // Prints the spaces
    }
    std::cout << n << std::endl; // Prints the text centered :]
}

// Overloading
void CoutCentered(string s, int n) {
    // This function will only center the text if it is less than the length of the console!
    // Otherwise it will just display it on the console without centering it.

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle.
    PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO(); // Create a pointer to the Screen Info pointing to a temporal screen info.
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo); // Saves the console screen info into the lpScreenInfo pointer.
    COORD NewSBSize = lpScreenInfo->dwSize; // Gets the size of the screen
    
    int size = s.size() + 2 + ceil(log10(n));

    if (NewSBSize.X > size) {
        int newpos = ((NewSBSize.X - size) / 2); // Calculate the number of spaces to center the specific text.
        for (int i = 0; i < newpos; i++) std::cout << " "; // Prints the spaces
    }
    std::cout << s << " : " << n << '\n'; // Prints the text centered :]
}

int main(){
    Student s;
    s.inputDetails();
    welcome();
    int score = readFile();
    s.putScore(score);
    s.showDetails();
    return 0;
}