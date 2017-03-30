//Steven Nguyen
//Oct 26, 2014
//main.cpp
#include "Browser.h"
#include <string>
#include <iostream>
#include <stack>
using namespace std;

int menu();

const char YES = 'y',
  NO = 'n';

int main()
{  
  Browser myBrowser;
  
  char again = 'y';

  int choice = 0, hyperNum;

  string fileLink = "home.html";

  stack<string> backward, forward; //going backward and forward
  
  myBrowser.loadHTML(fileLink);
  cout << myBrowser << endl;
	
  while(again == YES){
	choice = menu();

	switch(choice){
	case 1:
	  //delete the link when the previous link is same
	  while(!backward.empty() && fileLink == backward.top()){
		backward.pop();
	  }
	  if(!backward.empty()){
		forward.push(fileLink);
		fileLink = backward.top();
		backward.pop();
		myBrowser.loadHTML(fileLink);
		cout << myBrowser << endl;
	  }else
		cout << endl << "This is the first page..." << endl;
	  break;
	  
	case 2:
	  //delete the link when the forward link is same
	  while(!forward.empty() && fileLink == forward.top()){
		forward.pop();
	  }
	  if(!forward.empty()){
		backward.push(fileLink);
		fileLink = forward.top();
		forward.pop();
		myBrowser.loadHTML(fileLink);
		cout << myBrowser << endl;
	  }else
		cout << endl << "This is the last page..." << endl;
	  break;
	  
	case 3:
	  cout << endl
		   << "Please enter the proper hypertext link number here: ";
	  cin >> hyperNum;
	  backward.push(fileLink);
	  fileLink = myBrowser.getLink(hyperNum);
	  myBrowser.loadHTML(fileLink);
	  cout << myBrowser << endl;
	  break;

	case 4:
	  backward.push(fileLink);
	  cout << endl << "Please enter the link here: ";
	  cin >> fileLink;
	  myBrowser.loadHTML(fileLink);
	  cout << myBrowser << endl;
	  break;
	  
	case 5: again = 'n';
	  break;
	  
	default:
	  cout << endl << "Invalid input" << endl;
	  break;
	}
	
  }
	  
  return 0;
}

int menu()
{
  int num;
  cout << endl
	   << "Menu choice: " << endl
	   << "1. Go backward" << endl
	   << "2. Go forward" << endl
	   << "3. Go to the hypertext link" << endl
	   << "4. Enter your link" << endl
	   << "5. Quit" << endl
	   << "Your choice here: ";
  cin >> num;
  cout << endl;
  return num;
}
