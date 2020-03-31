#ifndef NEWMEMBER_H_
#define NEWMEMBER_H_

#include <iostream>
#include <fstream>  //for file operations
#include <string>
#include <stdlib.h> 
#include <ctime>    //for random value generation
#include <sstream>  //for string operations
#include <io.h>
#include <conio.h>	//console input/output operations
#include <windows.h>//for changing background and font color
using namespace std;

class NewMember {
	public:
	string cardNoIett;
	string name;
	string surname;
	string username;
	string password;
	int balance;
	
	void menu();
	void gotoXY(int x, int y);//function for arrow key usage
	void registers();
	bool registerControl(string cardNo);
	bool usernameControl(string username);
	void memberLogin();
	bool memberLoginControl(string username,string Password);
	void menu2();
	void balanceChecking();
	void balanceShow(string userName);
	void menu3();
	void loadMoneyMyAccount();
	void loadMoneyOtherAccount();
	void creditCardMyAccount();
	void moneyOperation(string username);
	void bankCardMyAccount();
	void moneyOperationOther(string username);
	void creditCardOtherAccount();
	void bankCardOtherAccount();
	
};
#endif
