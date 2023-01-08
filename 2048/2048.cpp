// This Program is written by Mohammad Hassan Heydari

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <fstream>
#pragma warning(disable : 4996)


using namespace std;

string firstPage() {

    string result;
    cout << "                                                   2048" << endl;
    cout << endl;
    cout << endl;
    cout << "Welcome to 2048 , for log in please enter 'logIn' and if you dont have account yet, please 'signIn', else if you want to play as a guest, enter Guest : ";
    cin >> result;
    return result;

}

void date() {

    time_t t = time(0);
    tm* now = localtime(&t);
    cout << "Date : " << (now->tm_year + 1900) << '/'
        << (now->tm_mon + 1) << '/'
        << now->tm_mday
        << "\n";

}

float timeDifference(clock_t time2, clock_t time1) {

    /* const clock_t time1 = clock();

     some program ...

     clock_t time2 = clock();
     cout << timeDifference(time2, time1);
     */

    return  float(time2 - time1) / CLOCKS_PER_SEC;

}


class Guest {
private:
    string getPassword(string entered) {
        string result = "";
        bool flag = false;
        for (int i = 0; i < entered.size(); i++) {
            if (entered[i] == ':') {
                flag = true;
                continue;
            }
            if (flag == true) {
                result += entered[i];
            }
        }
        return result;
    }

    string getUsername(string entered) {
        string result = "";
        for (int i = 0; i < entered.size(); i++) {
            if (entered[i] == ':') {
                break;
            }
            result += entered[i];
        }
        return result;
    }

    bool isUsernameExist(string entered) {
        ifstream file("test1.txt");
        string myText;
        while (getline(file, myText)) {
            // Output the text from the file
            if (getUsername(myText) == entered) {
                return 1;
            }

        }
        file.close();
        return 0;

    }

    bool strongPassword(string entered) {
        bool alpha = false;
        bool digit = false;
        if (entered.size() < 5) {
            return 0;
        }
        for (int i = 0; i < entered.size(); i++) {
            if (isalpha(entered[i]) == 1 || isalpha(entered[i]) == 2) {
                alpha = true;
            }
            if (isdigit(entered[i]) == 4) {
                digit = true;
            }
        }
        if (alpha && digit) {
            return 1;
        }
        else {
            return 0;
        }
    }

 
public:
    string theUsername;
    string thePassword;


    // if returns 1 means username and password are true, else they are false
    bool logIn(string username, string password) {
        ifstream file("test1.txt");
        string myText;
        while (getline(file, myText)) {
            // Output the text from the file
            if (getUsername(myText) == username) {
                if (getPassword(myText) == password) {
                    return 1;
                }
            }

        }
        file.close();
        return 0;
        
    }

    void signIn() {
        string username;
        string password;
        string result;

        cout << "\nenter the username : ";
        cin >> username;
        while (isUsernameExist(username)) {
            cout << "this username is already exit, enter another one ";
            cout << "\n enter the username : ";
            cin >> username;
        }
        cout << "\nenter the password : ";
        cin >> password;

        while (!(strongPassword(password))) {
            cout << "this password is not strong enough, try another one ";
            cout << "\n enter the password : ";
            cin >> password;
        }
        
        this->theUsername = username;
        this->thePassword = password;

        fstream file("test1.txt");
        file.seekg(0, ios::end);
        result = username + ":" + password + "\n";
        file << result;
        file.close();

    }


};

class User : public Guest {

public:
    string username;
    string password;


    User(string enteredUsername, string enteredPassword)  {
        this->username = enteredUsername;
        this->password = enteredPassword;
    }


    void welcome() {
        cout << "Hello and have a good game : " << this->username << endl;
        date();
    }
     
};

class Game {
    
    
public:
    
    string matrix[4][4];

    string indexOf(string number) {
        string result;
        bool flag = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (matrix[i][j] == number) {
                    result = to_string(i) + ":" + to_string(j);
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }

        }
        return result;
    }




    bool movementCorrect(string number) {
        char number_i = indexOf(number)[0];
        char number_j = indexOf(number)[2];

        int i = number_i - '0';
        int j = number_j - '0';

        if (matrix[i - 1][j] == " " || matrix[i][j - 1] == " " || matrix[i][j + 1] == " " || matrix[i + 1][j] == " ") {
            return 1;
        }

        return 0;

    }


    void printGame() {
        cout << "                                             ---------------------------" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "                                             ";
            for (int j = 0; j < 4; j++) {
                cout <<"|  " << matrix[i][j] << "  ";
                if (j == 3) {
                    cout << "|";
                }
            }
            if (i != 3) {
                cout << '\n' ;
                cout << "                                             ------------------------" << endl;
            }
            else {
                cout << endl;
            }
            
        }
        cout << "                                             ---------------------------" << endl;

    }

};

int main()
{
    string order = firstPage();
    bool UserFlag = false;

    if (order == "signIn") {

        Guest user;
        user.signIn();
        User userLogged(user.theUsername, user.thePassword);
        userLogged.welcome();
        cout << endl;
        UserFlag = true;

    }
    else if (order == "logIn") {

        Guest user;
        string username, password;
        cout << '\n' << "Please enter your username and password" << endl;
        cout << "username : ";
        cin >> username;
        cout << "password : ";
        cin >> password;

        if (user.logIn(username, password) == 1) {

            User userLogged(username, password);
            userLogged.welcome();
            UserFlag = true;
        }

        else {
            cout << "log in failed !" << endl;
        }

    }

    else if (order == "Guest") {
        Game game;
        game.matrix[0][0] = "12";
        game.matrix[0][1] = "1";
        game.matrix[0][2] = "2";
        game.matrix[0][3] = "15";
        game.matrix[1][0] = "11";
        game.matrix[1][1] = "6";
        game.matrix[1][2] = "5";
        game.matrix[1][3] = "8";
        game.matrix[2][0] = "7";
        game.matrix[2][1] = "10";
        game.matrix[2][2] = "9";
        game.matrix[2][3] = "4";
        game.matrix[3][0] = " ";
        game.matrix[3][1] = "13";
        game.matrix[3][2] = "14";
        game.matrix[3][3] = "3";

        game.printGame();


        string order;
        cout << endl;
        cout << "Enter the Order , numbers to move, EXIT for exit : ";
        cin >> order;

        while (order != "EXIT") {

            char charStar_i = game.indexOf(" ")[0];
            char charStar_j = game.indexOf(" ")[2];
            int intStar_i = charStar_i - '0';
            int intStar_j = charStar_j - '0';

            if (game.movementCorrect(order) == 1) {

                char charOrder_i = game.indexOf(order)[0];
                char charOrder_j = game.indexOf(order)[2];
                int intOrder_i = charOrder_i - '0';
                int intOrder_j = charOrder_j - '0';


                string temp = order;
                game.matrix[intOrder_i][intOrder_j] = " ";
                game.matrix[intStar_i][intStar_j] = temp;

            }
            cout << endl;

            game.printGame();
            cout << "Enter order : ";
            cin >> order;
        }
    }

    


    if (UserFlag) {
        // game started

        const clock_t time1 = clock();

        Game game;
        game.matrix[0][0] = "12";
        game.matrix[0][1] = "1";
        game.matrix[0][2] = "2";
        game.matrix[0][3] = "15";
        game.matrix[1][0] = "11";
        game.matrix[1][1] = "6";
        game.matrix[1][2] = "5";
        game.matrix[1][3] = "8";
        game.matrix[2][0] = "7";
        game.matrix[2][1] = "10";
        game.matrix[2][2] = "9";
        game.matrix[2][3] = "4";
        game.matrix[3][0] = " ";
        game.matrix[3][1] = "13";
        game.matrix[3][2] = "14";
        game.matrix[3][3] = "3";


        game.printGame();

        string order;
        cout << endl;
        cout << "Enter the Order , numbers to move, EXIT for exit : ";
        cin >> order;

        while (order != "EXIT") {
            clock_t time2 = clock();

            char charStar_i = game.indexOf(" ")[0];
            char charStar_j = game.indexOf(" ")[2];
            int intStar_i = charStar_i - '0';
            int intStar_j = charStar_j - '0';
            
            if (game.movementCorrect(order) == 1) {

                char charOrder_i = game.indexOf(order)[0];
                char charOrder_j = game.indexOf(order)[2];
                int intOrder_i = charOrder_i - '0';
                int intOrder_j = charOrder_j - '0';


                string temp = order;
                game.matrix[intOrder_i][intOrder_j] = " ";
                game.matrix[intStar_i][intStar_j] = temp;
               
            }
            cout << endl;
            cout <<"time passed : " << timeDifference(time2, time1) << '\n' << '\n';

            game.printGame();
            cout << "Enter order : ";
            cin >> order;

        }

    }
      
}