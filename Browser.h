//Steven Nguyen
//Oct 26, 2014
//Browser.h

#ifndef ____html__
#define ____html__

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

class Browser
{
public:
	Browser();
	
	void loadHTML(string filename);
	//Pre: none
	//Post: load text into displayText
	
	void display(ostream &out) const;
	//Pre: none
	//Post: none
	
    string getLink(int index);
	//Pre: index must be within the range
	//Post: none
	
private:
	// Display size
	int numColumns, numRows, hyperTextCount;

	stack<string> bodyTag;
	vector<string> hyperText;

	bool tagCheck = true;
	
    string displayText;
	
	string parseTag(string tag);
	void parseHTML(string encodedText);
};

ostream& operator<<(ostream& out, const Browser &rhs);

#endif /* defined(____html__) */
