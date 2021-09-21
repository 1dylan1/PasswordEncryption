#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include "functions.h"

using namespace std;

int main() {

	SetConsoleTitle( TEXT("Password Encryption Manager")); 
	FirstTimeSetupCheck();
	Login();
	menu();


	return 0;
}