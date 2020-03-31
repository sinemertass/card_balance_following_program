#include "NewMember.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void NewMember:: menu()
{
	NewMember member; //class object defination
	int menuChoise;
    int menu_item=0, run, x=9;
	
	bool running = true;
	//sutun satır
	gotoXY(8,2); cout<<"___________________";
	gotoXY(11,4); cout << "MOBILE AKBIL";
	gotoXY(8,5); cout<<"___________________";
	
	gotoXY(6,9); cout << "->";
	
	while(running)
	{
        gotoXY(11,9);  cout << "1) REGISTER";
		gotoXY(11,10);  cout << "2) LOGIN";
		gotoXY(11,11); cout << "3) QUIT PROGRAM";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x !=12) //down button pressed 12
			{
				gotoXY(6,x); cout << "  ";
				x++;
				gotoXY(6,x); cout << "->";
				menu_item++;
				continue;
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 8) //up button pressed 8
			{
				gotoXY(6,x); cout << "  ";
				x--;
				gotoXY(6,x); cout << "->";
				menu_item--;
				continue;
			}
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					gotoXY(0,14);
					member.registers();
					break;
				}
					
					
				case 1: {
					gotoXY(0,14);
					member.memberLogin();
					break;
				}
					
				case 2: {
					gotoXY(0,14);
					system("cls");
					exit(0);
				}
			}
		}		
 	}
	
	gotoXY(11,11);
}

void NewMember:: gotoXY(int x, int y) 
{ 
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(console,CursorPosition); 
}

void NewMember:: registers()
{
	string cardNo,username;
	int balance;
	ofstream fileRegister; //declare a file for register
	ofstream fileUsername; //declare a file for username 
	ofstream fileCardNo;   //declare a file for card no
	fileRegister.open("registers.txt", ios::app); //open a file for registers as "registers"
	
	cout << "Iett card number: "; 
	cin >> cardNo;

	fileCardNo.open("cardNoIett.txt", ios::app); //open a file for card no as "cardNoIett"
	NewMember member;
	
	if (member.registerControl(cardNo) == 1) //deciding outputs according to the card no check result
	{
		cout <<"This card number has been already using!"<<endl;
		Sleep(1500);
		system("cls");
		menu();
	}
	else
	{
	    member.cardNoIett = cardNo; //assign new cardNo as member's cardNoIett
	    fileCardNo<<member.cardNoIett<<endl;  //writing member's card no's into the cardNoIett file
	
		cout << "Name: "; 
		cin >> member.name;
		cout << "Surname: "; 
		cin >> member.surname;
		
		cout<<"Dear "<<member.name<<", please create an username and password for your membership."<<endl<<endl;
		cout<<"Username: ";
		cin>>username;
		fileUsername.open("username.txt", ios::app); //open a file for usenames as "username"
	    
		 char c;
   		 cout<<"Password: ";
		
   		 do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(password.length()>0){
                password.erase(password.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            password+= c;//add to string
            cout<<'*';   //print `*`
            break;
        }
    }while(c!=13);
    
      member.password=password;
		
	if (usernameControl(username) == 1) //deciding outputs according to the username check result
	{
		cout << "This username has been already using!"<<endl;
		Sleep(2000);
		system("cls");
    	menu();
	} 
    else
    {   
		srand(time(NULL));
	    balance=rand()%(100+1); //random number assignment as a balance between 1 and 100 
	    
	    member.balance=balance;		
	    member.username=username;
	
		fileUsername<<member.username<<endl; //writing usernames of members in username file
		fileRegister <<member.username<<'#'<<member.cardNoIett <<'#'<<member.name<<'#'<<member.surname<<'#'<<member.password<<'#'<<member.balance<<endl;
		//writing all informations of members in register file with hashtag seperator
    
	cout << "Member adding is completed!"<<endl;
	
	fileRegister.close();
	fileUsername.close();
	fileCardNo.close();
	
	member.menu2(); //display menu2
    }	 
}	
}	

	bool NewMember:: registerControl(string cardNo) //checking whether the card number is used or not
{
	bool control = 0; //assigning bool control as 0 at first
	ifstream fileCardNo;
	fileCardNo.open("cardNoIett.txt");
	
	NewMember member;

	while (!fileCardNo.eof()) //card no file is being read until the end of the file 
	{
		fileCardNo >> member.cardNoIett;
		if (member.cardNoIett == cardNo) 
		{
			control = 1;
		}
	}
 	return control;
}

bool NewMember:: usernameControl(string username) //checking whether the username is used or not
{
	bool control = 0;
	ifstream fileUsername;
	fileUsername.open("username.txt");
	
	NewMember member;
 
	while (!fileUsername.eof()) //username file is being read until the end of the file 
	{
		fileUsername >> member.username;
		if (member.username == username)
		{
			control = 1;
		}
	}
 	return control;
}

void NewMember:: memberLogin()
{
	NewMember member;
	string username,password;
	cout << "Username: "; cin >> username;

	 char c;
    cout<<"Enter password:";
    do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(password.length()>0){
                password.erase(password.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            password+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
    }while(c!=13);
    
    member.password=password;	
		
	if((member.memberLoginControl(username,password)==1)) //sending username and password through memberLoginControl
													      // for checking their compliance 
	{
		cout<<"Login completed successfully!"<<endl<<endl;
		member.menu2();		
    }
    else
   {
		cout << "Please check username and password!"<<endl;
		Sleep(2000);
		system("cls");
    	member.menu();
	}    	
}

bool NewMember:: memberLoginControl(string username,string Password) //checking username and password compliance for login
{
	bool control = 0;
	ifstream fileRegister;
	string user,cardNo, name,surname,password,balance;
	string line;
	fileRegister.open("registers.txt");

	while (!fileRegister.eof())
	{
		getline(fileRegister,line,'\n'); //in register file, catching a line until it sees \n and assigning it as line
		user = line.substr(0,line.find("#")); 

		if (user.compare(username)== 0 ) //function that compares two strings (compares user and username)
		{

			user = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			cardNo = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			name = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			surname = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			password = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			balance = line.substr(0,line.find("#"));
           
           if(password.compare(Password)==0)
           {
           	control=1;
		   }
		} 
	}
	fileRegister.close();
	return control;	
}
void NewMember:: menu2() 
{
	NewMember member;
	int menu2Choise;

	int menu_item=0, run, x=9;
	bool running = true;
	system ("cls");
	gotoXY(11,2); cout<<"___________________";
	gotoXY(14,4); cout << "MOBILE AKBIL";
	gotoXY(11,5); cout<<"___________________";

	gotoXY(6,9); cout << "->";
	
	while(running)
	{
        gotoXY(11,9);  cout << "1) BALANCE CHECKING";
		gotoXY(11,10);  cout << "2) LOAD MONEY";
		gotoXY(11,11);  cout << "3) RETURN TO THE MAIN MENU";
		gotoXY(11,12); cout << "4) QUIT PROGRAM";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed 12
			{
				gotoXY(6,x); cout << "  ";
				x++;
				gotoXY(6,x); cout << "->";
				menu_item++;
				continue;
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 8) //up button pressed 12
			{
				gotoXY(6,x); cout << "  ";
				x--;
				gotoXY(6,x); cout << "->";
				menu_item--;
				continue;
			}
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					
					gotoXY(0,14);
					member.balanceChecking();
					break;
				}
				case 1: {
					gotoXY(0,14);
					menu3();
					break;
				}
				case 2: {
					gotoXY(0,14);
					system("cls");
					menu();
					break;
				}	
				case 3: {
					gotoXY(0,14);
					system("cls");
					exit(0);
				}
			}
		} 	
	}
	
	gotoXY(11,11);
}

void NewMember:: balanceChecking()
	{
		NewMember member;
	    string username;
	    int balance;
	    cout<<"Please enter your username for your security."<<endl;
	    cout<<"Username:";
	    cin>>member.username;
	    username=member.username;
	    member.balanceShow(username); //sending username variable into the balanceShow function
	}
	
void NewMember:: balanceShow(string userName)
{
	fstream fileRegister; //input/output file stream class
	string user,cardNo, name,surname,password,balance;
	string line;
	fileRegister.open("registers.txt"); //opens registers file

	while (!fileRegister.eof())
	{
		getline(fileRegister,line,'\n');
		user = line.substr(0,line.find("#"));

		if (user.compare(userName)== 0 ) //comparing user and userName strings
		{
			user = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			cardNo = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			name = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			surname = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			password = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			balance = line.substr(0,line.find("#"));

			cout<<"Dear "<<name<<" "<<surname<<", your balance is "<<balance<<" TL.";
		} 
	}
	fileRegister.close();
}

void NewMember:: menu3() 
{
	NewMember member;
	int menu3Choise;
    int menu_item=0, run, x=8;
	bool running = true;

	system ("cls");
	gotoXY(11,2); cout<<"___________________";
	gotoXY(14,4); cout << "MOBILE AKBIL";
	gotoXY(11,5); cout<<"___________________";
	
	gotoXY(6,9); cout << "->";
	
	while(running)
	{
		
        gotoXY(11,9);  cout << "1) Load Money to Your Account";
		gotoXY(11,10);  cout << "2) Load Money to Different Account";
		gotoXY(11,11);  cout << "3) Return to the Main Menu";
		gotoXY(11,12);  cout << "4) Quit Program";
	

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed
			{
				gotoXY(6,x); cout << "  ";
				x++;
				gotoXY(6,x); cout << "->";
				menu_item++;
				continue;	
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 8) //up button pressed
			{
				gotoXY(6,x); cout << "  ";
				x--;
				gotoXY(6,x); cout << "->";
				menu_item--;
				continue;
			}
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 1: {
					
					gotoXY(0,14);
					loadMoneyMyAccount();
					break;
				}
				case 2: {
					gotoXY(0,14);
					loadMoneyOtherAccount();	
					break;
				}
				case 3:
				{
					gotoXY(0,14);
					system("cls");
					menu();
					break;
				}	
				case 4: {
					gotoXY(0,14);
					exit(0);
					break;
				}
			}
		}		
	}
	
	gotoXY(11,11);
}

void NewMember:: loadMoneyMyAccount()
{
	NewMember member;
	int cardChoise; 

	cout <<endl<< "1) Credit Card" <<endl;
	cout << "2) Bank Card" <<endl;
	cout << "Enter your selection: "; 
	cin >> cardChoise; 
	cout << endl;
 
	switch (cardChoise) //deciding next operation according to the choice
	{
	case 1: creditCardMyAccount(); 
		break;
	case 2: bankCardMyAccount();
		break;
	default:
		cout << "You made a wrong choice in the menu!"<<endl;
		Sleep(2000);
		member.menu3();
		break;
	}
}

void NewMember:: loadMoneyOtherAccount()
{
	NewMember member;
	int cardChoise; 

	cout <<endl<< "1) Credit Card" <<endl;
	cout << "2) Bank Card" <<endl;
	cout << "Enter your selection: "; 
	cin >> cardChoise; 
	cout << endl;
 
	switch (cardChoise) //deciding next operation according to the choice
	{
	case 1: creditCardOtherAccount(); 
		break;
	case 2: bankCardOtherAccount(); 
		break;
	default:
		cout << "You made a wrong choice in the menu!!"<<endl;
		Sleep(2000);
		member.menu3();
		break;	
	}
}

void NewMember:: creditCardMyAccount()
{
	NewMember member;
	    string username,creditCardNo,smsCode,a;
	    cout<<"Please enter your username for your security."<<endl;
	    cout<<"Username: ";
		cin>>member.username;
		username=member.username;
		
		if (usernameControl(username) == 1) //deciding outputs according to the username check result
	{
		cout<<"Enter your credit card number: ";
	    cin>>creditCardNo;
	    
	    char c;
    cout<<"enter sms code: ";
   
    do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
    }while(c!=13);
	    
	    if(memberLoginControl(username,smsCode)==1)//username and password verification as sms code control
	{
		moneyOperation(username);
	}
	else
	{
		cout<<"You entered wrong sms code, last two chance!!!"<<endl;
		Sleep(1500);
		int counter=1;
		while(counter<3)
		{
		cout<<counter<<". Chance "<<endl;
		  
	    char c;
    cout<<"Enter sms code: ";
    do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
    }while(c!=13);
		
		if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
		{
			moneyOperation(username);
		}
		counter++;
		}
	}		
	} 
    else
    {   
	   	cout<<"No user with that username!!"<<endl;
		cout<<"Please try later after 2 second..";
		Sleep(2500);
		system("cls");
		
		gotoXY(11,2); cout<<"___________________";
    	gotoXY(14,4); cout << "MOBILE AKBIL";
    	gotoXY(11,5); cout<<"___________________";
		
		gotoXY(0,8);
	   	creditCardMyAccount();
    }	    
}

void NewMember:: moneyOperation(string username)
{
	ifstream fileRegister;
	ofstream fileTemporaryRegister;	
	fileRegister.open("registers.txt");
	fileTemporaryRegister.open("TemporaryRegisters.txt", ios::app); //open a file for using temporary registers list
    string user,cardNo, name,surname,password,balance; 
	string line;
     
    int i,balance2;
	  
	while (!fileRegister.eof())
	{
		getline(fileRegister,line,'\n');
		user = line.substr(0,line.find("#"));

		if (user.compare(username)!=0) //comparing user and username strings
		{
			line = line.substr(0,line.find('\n'));
		    fileTemporaryRegister<<line<<endl;  //writing all lines in registers into the temporary file except the line which we want to change it's balance 
		}	
			if (user.compare(username)== 0 )//after username verification, collecting the information in order to reach and change the balance 
		{
		
			user = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			cardNo = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			name = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			surname = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			password = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			balance = line.substr(0,line.find("#"));
			
			i= atoi(balance.c_str()); //integer converting to the string
		}
	}
	
    cout<<"Amount of money for loading: ";
    int amount;
    cin>>amount;
    balance2=amount+i;//base money and loaded money addition
    
	fileTemporaryRegister<<username<<'#'<<cardNo<<'#'<<name<<'#'<<surname<<'#'<<password<<'#'<<balance2;//writing new balance and other informations into the temporary file
	cout<<"Dear "<<name<<" "<<surname<<", your new balance is "<<balance2<<" TL";//display the new balance of user

	fileRegister.close();	
 	fileTemporaryRegister.close();	
 	
    remove("registers.txt");//deleting the file which name is registers
	rename("TemporaryRegisters.txt", "registers.txt");//temporary file named as "registers" 
	Sleep(2500);
	system("cls");
	menu3();
}

void NewMember:: bankCardMyAccount()
{
		NewMember member;
	    string username,bankCardNo,smsCode;
	    cout<<"Please enter your username for security!"<<endl;
	    cout<<"Username: ";
	    cin>>member.username;
	    username=member.username;
	    	
		if (usernameControl(username) == 1)
	{
		cout<<"Enter your bank card number: ";
	    cin>>bankCardNo;

	    char c;
    	cout<<"Enter sms code: ";
   	 do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
 	   }while(c!=13);
	    
	    if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
		{
		moneyOperation(username);
		}
		else
		{
		cout<<endl<<endl;
		cout<<"Your entered wrong sms code, last two chance!!!"<<endl;
		int counter=1;
		while(counter<3)
		{
		cout<<counter<<". Chance "<<endl;
		    
		char c;
    	cout<<"Enter sms code: ";
    	do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
	    }while(c!=13);
	    
		if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
		{
			moneyOperation(username);
		}
		counter++;
		}
	}		
}
		
	else
	{
		cout<<endl<<endl;
		cout<<"No user with that username!!"<<endl;
		cout<<"Please try later after 2 second...";
		Sleep(2500);
		system("cls");
		gotoXY(11,2); cout<<"___________________";
    	gotoXY(14,4); cout << "MOBILE AKBIL";
    	gotoXY(11,5); cout<<"___________________";
		
		gotoXY(0,8);
		bankCardMyAccount();
	}
}

void NewMember:: moneyOperationOther(string username)
{
	ifstream fileRegister;
	ofstream fileTemporaryRegister;
	fileRegister.open("registers.txt");
	fileTemporaryRegister.open("temporaryRegisters.txt", ios::app);	
  
    string user,cardNo, name,surname,password,balance;
	string line;
     
     int i,balance2;
	  
	while (!fileRegister.eof())
	{
		getline(fileRegister,line,'\n');
		user = line.substr(0,line.find("#"));

		if (user.compare(username)!=0) //comparing user and username strings
		{
			line = line.substr(0,line.find('\n'));
		    fileTemporaryRegister<<line<<endl;//writing all lines in registers into the temporary file except the line which we want to change it's balance 
		}		
			if (user.compare(username)== 0 )//after username verification, collecting the information in order to reach and change the balance 
		{
		
			user = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			cardNo = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			name = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			surname = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			password = line.substr(0,line.find("#"));

			line = line.substr(line.find("#")+1,line.length());
			balance = line.substr(0,line.find("#"));
			
			i= atoi(balance.c_str()); //converting integer to the string
		}
	}
	
    cout<<"Amount of money for loading: ";
    int amount;
    cin>>amount;
    balance2=amount+i;//base money and loaded money addition
    
	fileTemporaryRegister<<username<<'#'<<cardNo<<'#'<<name<<'#'<<surname<<'#'<<password<<'#'<<balance2;//writing new balance and other informations into the temporary file
	cout<<endl<<endl;
	cout<<"Your loading operation is completed..."<<endl;
	Sleep(2500);
	cout<<name<<" "<<surname<<"'s new balance is "<<balance2<<" TL";//display the new balance of money loaded account
	cout<<endl<<endl;
	fileRegister.close();	
 	fileTemporaryRegister.close();
 	
    remove("registers.txt");//deleting the file which name is registers
	rename("temporaryRegisters.txt", "registers.txt");//temporary file named as "registers" 
   	Sleep(4500);
	system("cls");
	menu3();
}

void NewMember:: creditCardOtherAccount()
{
		NewMember member;
	    string username,creditCardNo,smsCode;
	    string username2;
	    cout<<"Please enter your username for your security."<<endl;
	    cout<<"Username: ";
	    cin>>member.username;
	    username=member.username;
	    
	if (usernameControl(username) == 1)
	{
	   	cout<<"Enter your credit card number: ";
	    cin>>creditCardNo;
	    
	    char c;
     	cout<<"enter sms code: ";
    	do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
  	  }while(c!=13);
	    
	    if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
	 {
		cout<<"Your operation is processing..."<<endl;
		Sleep(2500);
		cout<<"Enter the username of the account you want to load money: ";
		cin>>username2;
		
			if (usernameControl(username2) == 1)//checking for entered username usage
			{
			  moneyOperationOther(username2);
			}
			
			else
			{
				cout<<"No user with that username!!"<<endl;
				cout<<"Your operation is finished..."<<endl;
				Sleep(1000);
				cout<<"You are directing to the main menu...";
				Sleep(3000);
				system("cls");
				menu3();
			}
	   }
		else
	 {
		cout<<"Your entered wrong sms code, last two chance!!!"<<endl;
		Sleep(1500);
		int counter=1;
		while(counter<3)
		{
		cout<<counter<<". Chance "<<endl;
		char c;
     	cout<<"enter sms code: ";
    	do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
  	  }while(c!=13);
	
		if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
		{
			cout<<"Your operation is processing..."<<endl;
			Sleep(2500);
			cout<<"Enter the username of the account you want to load money: ";
			cin>>username2;
			if (usernameControl(username2) == 1)//checking for entered username usage
			{
			  moneyOperationOther(username2);
			  break;
			}
			
			else
			{
				cout<<"No user with that username!!"<<endl;
				cout<<"Your operation is finished..."<<endl;
				Sleep(1000);
				cout<<"You are directing to the main menu...";
				Sleep(3000);
				system("cls");
				menu3();  
			}
		}
		counter++;
		}
	}		
}
	else
	{
		cout<<"No user with that username!!"<<endl;
		cout<<"Please try later after 2 second..";
		Sleep(2500);
		creditCardOtherAccount();
	}
}

void NewMember:: bankCardOtherAccount()
{
	NewMember member;
	    string username,bankCardNo,smsCode;
	    string username2;
	    cout<<"Please enter your username for your security."<<endl;
	    cout<<"Username:";
	    cin>>member.username;
	    username=member.username;
	    
	    if (usernameControl(username) == 1)
	{
	    cout<<"Enter your bank card number: ";
	    cin>>bankCardNo;
	    
	    char c;
    	cout<<"enter sms code: ";
	    do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
    	}while(c!=13);
	    
	    if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
	 {
		cout<<endl<<endl;
		cout<<"Your operation is processing..."<<endl;
		Sleep(2500);
		cout<<"Enter the username of the account you want to load money: ";
		cin>>username2;
		
			if (usernameControl(username2) == 1)//checking for entered username usage
			{
			  moneyOperationOther(username2);
			}
			
			else
			{
				cout<<"No user with that username!!"<<endl;
				cout<<"Your operation is finished..."<<endl;
				Sleep(1000);
				cout<<"You are directing to the main menu...";
				Sleep(3000);
				system("cls");
				menu3();
			}			
}
		else
	 {
		cout<<"Your entered wrong sms code, last two chance!!!"<<endl;
		Sleep(1500);
		int counter=1;
		
		while(counter<3)
		{
		cout<<counter<<". Chance "<<endl;
	    
	    char c;
	    cout<<"Enter sms code: ";
    	do{
        c = getch();
        switch(c){
        case 0://special keys. like: arrows, f1-12 etc.
            getch();//just ignore also the next character.
            break;
        case 13://enter
            cout<<endl;
            break;
        case 8://backspace
            if(smsCode.length()>0){
                smsCode.erase(smsCode.end()-1); //remove last character from string
                cout<<c<<' '<<c;//go back, write space over the character and back again.
            }
            break;
        default://regular ascii
            smsCode+= c;//add to string
            cout<<'*';//print `*`
            break;
        }
    	}while(c!=13);	
		if(memberLoginControl(username,smsCode)==1)//username and its password verification as sms code control
	 	{
			cout<<"Your operation is processing..."<<endl;
			Sleep(2500);
			cout<<"Enter the username of the account you want to load money: ";	cin>>username2;
			
			if (usernameControl(username2) == 1)//checking for entered username usage
			{
			  moneyOperationOther(username2);
			}			
			else
			{
				cout<<"No user with that username!!"<<endl;
				cout<<"Your operation is finished..."<<endl;
				Sleep(1000);
				cout<<"You are directing to the main menu...";
				Sleep(3000);
				system("cls");
				menu3();
			}
	 	 }
	  counter++;
	}		
  }
}	
	    else
	 	{
		cout<<"No user with that username!!"<<endl;
		cout<<"Please try later after 2 second..";
		Sleep(2500);		
		system("cls");
		bankCardOtherAccount();
 	    }	
}
