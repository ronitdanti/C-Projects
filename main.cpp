/*
 * Symmetric Encryption Login System
 *
 * A basic login system that encrypts user registration data (username and password) and saves it to a file so that it can be pulled up and read during login.
 * 
 * Features:
 * * Registration
 * * Login
 * * Basic Encryption and Decryption
 * 
 * May add password format verification eventually?
 * 
 * @author ronit
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int key = 5;

bool isLoggedIn();
void registration();
string encrypt(string);
string decrypt(string);

bool isLoggedIn() {
    string username;
    string password;
    string file_username;
    string file_password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream read("data_" + username + ".txt");
    getline(read, file_username);
    getline(read, file_password);

    return (decrypt(file_username) == username && decrypt(file_password) == password);
}

void registration() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream file;
    file.open("data_" + username + ".txt");
    file << encrypt(username) << endl << encrypt(password);
    file.close();
}

string encrypt(string in) {
    string out = "";
    for (int i = 0; i < in.length(); i++) {
        out = out + ((char) (in.at(i) + key));
    }
    return out;
}

string decrypt(string in) {
    string out = "";
    for (int i = 0; i < in.length(); i++) {
        out = out + ((char) (in.at(i) - key));
    }
    return out;
}

int main(int argc, char** argv) {
    int choice = -1;
    while (choice != 3) {
        cout << "1: Register\n2: Login\n3: Exit\nYour choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
            registration();
            cout << "Account created!" << endl;
            break;
            case 2:
            if (isLoggedIn()) {
                cout << "Logged in successfully." << endl;
            } else {
                cout << "Invalid credentials." << endl;
            }
            break;
            case 3:
            break;
            default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "Exiting application." << endl;
    return 0;
}