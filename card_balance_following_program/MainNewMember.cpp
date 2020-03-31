#include <iostream>
#include "NewMember.h"

using namespace std;

int main()
{
	NewMember member; //class object defination
	while (true)
	{
		system("color 06");
		system("cls"); //cleaning the screen every time before menu came
		member.menu(); //Calling menu	
		system("pause"); //indicate that the operation is over
	}
	return 0;
}
