#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<filesystem>
#include<direct.h>

const char* dirPath = "C:\\eQHpjDE6wq";
const char* filePath = "C:\\eQHpjDE6wq\\TTw82bF1Rl.txt";

using namespace std;

void Quit();
void AddService();
void ShowAll();
void SearchService();
void menu();

bool CheckForFile(const char* filePath) {
	if (FILE* file = fopen(filePath, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

bool dirExists(const string& dirPath)
{
	DWORD fileAttr = GetFileAttributesA(dirPath.c_str());
	if (fileAttr == INVALID_FILE_ATTRIBUTES)
		return false;

	if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
		return true;   //dirPath found

	return false;    //did not find dirPath
}

void Login() {
	char login[20];
	char pass[20];
	cout << "Please enter your username: \n";
	cin >> login;
	cout << "Please enter your password: \n";
	cin >> pass;
	if (strcmp(login, "admin") == 0 && strcmp(pass, "password") == 0) {
		cout << "Welcome to Password Encryption Tool, " << login << "\n";
		cout << "Last updated: 9/21/2021 9:56 AM\n";
	}
	else {
		cout << "Your username or password was incorrect, please try again\n";
		Sleep(1000);
		Login();
	}
}

void Quit() {
	exit(0);
}

void FirstTimeSetupCheck() {

	if (dirExists(dirPath)) {
		cout << "[dirExists] " << dirPath << " exists!\n";
	}
	else {
		cout << "[dirExists] " << dirPath << " does not exist!\n";
		cout << "[dirExists] Creating Folder in " << dirPath << "\n";
		_mkdir(dirPath);
		cout << "[dirExists] Created Folder Successfully.\n";
	}

	if (CheckForFile(filePath)) {

		cout << "[CheckForFile] " << filePath << " exists!\n";
	}
	else {
		cout << "[CheckForFile] " << filePath << " does not exist!\n";
		cout << "[CheckForFile] Creating password.txt \n";
		ofstream myFile;
		myFile.open(filePath);
		myFile.close();
		cout << "[CheckForFile] file placed successfully.\n";
	}

}

string encryptString(string s) {
	char buffer[1024];
	strcpy(buffer, s.c_str());
	for (int i = 0; (i < 100 && buffer[i] != '\0'); i++) {
		buffer[i] = buffer[i] + 25; //adding 25 to the ascii character
	}
	return buffer;
}

string decryptString(string s) {
	char buffer[1024];
	strcpy(buffer, s.c_str());

	for (int i = 0; (i < 100 && buffer[i] != '\0'); i++) {

		buffer[i] = buffer[i] - 25; //adding 25 to the ascii character
	}
	return buffer;
}

void AddService() {
	string service;
	string username;
	string password;
	ofstream file(filePath, ios::app); //append
	system("CLS");
	cout << "Enter new service: " << endl;
	cin >> service;
	system("CLS");
	cout << "Enter new username: " << endl;
	cin >> username;
	system("CLS");
	cout << "Enter password: " << endl;
	cin >> password;

	service = encryptString(service);
	username = encryptString(username);
	password = encryptString(password);

	file << service << ' ' << username << ' ' << password << endl;
	file.close();
	system("CLS");
	menu();

}

void SearchService() {
	ifstream file(filePath);
	string service;
	string str, line;
	string username;
	string password;
	bool Found = false;
	system("CLS");
	cout << "Enter the service you want to find:" << endl;
	cin >> str;

	while (file >> service >> username >> password) {

		service = decryptString(service);
		username = decryptString(username);
		password = decryptString(password);

		if (str == service) {
			Found = true;
			system("CLS");
			cout << "Found Service: " << service << endl;
			cout << "Username: " << username << endl;
			cout << "Password: " << password << endl;
		}
	}
	if (Found == false) {
		cout << "Sorry, we could not find a service with that name." << endl;

	}

	Sleep(3000);
	system("CLS");
	menu();
}

void ShowAll() {
	ifstream file(filePath);
	string service;
	string username;
	string password;
	system("CLS");
	cout << "All Passwords/Services Stored" << endl;
	cout << "Service -- Username -- Password" << endl;
	while (file >> service >> username >> password) {
		service = decryptString(service);
		username = decryptString(username);
		password = decryptString(password);
		cout << service << ' ' << username << ' ' << password << endl;
	}
	system("pause");
	cin.get();
	system("CLS");
	menu();

}
void menu() {
	cout << "What would you like to do? \n";
	cout << "(1) View All passwords\n";
	cout << "(2) View a specific service login\n";
	cout << "(3) Add a password/service\n";
	cout << "(4) Exit program\n";
	int val;
	cin >> val;
	switch (val) {
	case 1:
		ShowAll();
		break;
	case 2:
		SearchService();
		break;

	case 3:
		AddService();
		break;
	case 4:
		Quit();
		break;
	}
	if (val > 4 || val > 1) {
		"Please enter a valid input.\n";
		Sleep(2000);
		menu();
	}
}
