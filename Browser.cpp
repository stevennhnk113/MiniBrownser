//Steven Nguyen
//Oct 26, 2014
//Browser.cpp

#include "Browser.h"

Browser::Browser()
  : numColumns(40), numRows(8), displayText("")
{
  hyperTextCount = 0;
  tagCheck = true;
}

void Browser::loadHTML(string filename)
{
	string str;
	string allText = "";
	ifstream infile;
	infile.open(filename.c_str());
	if( !infile.is_open() )
	{
		cout << "ERROR Loading HTML file!\n";
		return;
	}
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,str); // Saves the line in STRING.
		allText += str + "\n";
	}
	infile.close();
	
	parseHTML(allText);
}

void Browser::parseHTML(string encodedText)
{
  //const char SPACE = ' ';
  int num = 0,
	col = 0,
	count = 0;
  //countSpace = 0;
  string temp = "",
	temp1,
	tag = "";
  // What do you need to reset?
  displayText = "";
  tagCheck = true;
  num = encodedText.length();
  
  // What do you need to track? (7+ things)
  for(int i = 0; i < num; i++){	
	temp = encodedText[i];
	
	if(temp == "<"){
	  while(temp != ">"){
		if(temp != " ") //avoiding space in tag
		  tag += temp;
		i++;
		temp = encodedText[i];
	  }
	  tag += ">";
	  temp = parseTag(tag);
	  if(encodedText[i+1] == '\n')
		i++;
	  if(temp == "\n" || temp == "\n\n")
		col = 0;
	  tag = "";
	  
	}else if(temp == "\n"){
	  temp = " ";
	  
	}else if(temp == " " &&
			 (encodedText[i+1] == ' '||encodedText[i+1] == '\n')){
	  temp = "";

	}else if(temp == "/r"){
	  temp = "";
	  
	}else if( col >= 30 && isalnum(temp[0]) && isprint(temp[0]) ){
	  while(encodedText[i] != ' ' && encodedText[i] != '\n'
			&& encodedText[i] != '<'){
		temp1 += encodedText[i];
		i++;
		col++;
		count++;
	  }
	  if(col <= 40){
		temp = temp1;
		temp1 = "";
		i--;
		count = 0;
	  }else{
		temp = "\n" + temp1;
		col = count;
		count = 0;
		i--;
		temp1 = "";
	  }
	}
	
	displayText += temp;
	if(temp != "")
	  col++;
	if(tagCheck == false)
	  i = num;
  }
  hyperTextCount = 0;
  // Be sure to use the parseTag() function
}

string Browser::parseTag(string tag)
{
  string link, temp = "";
  bool done = false, read = false;
  int num = 0;

  if(toupper(tag[1]) != 'A'){
	for(unsigned i = 0; i < tag.length(); i++)
	  temp += toupper(tag[i]);
	tag = temp;
  }
  
  switch(toupper(tag[1])){
  case 'P': return "\n\n"; 
	break;
	
  case 'B':
	if(tag[2] == 'R')
	  return "\n";
	else if(tag[2] == 'O')
	  bodyTag.push(tag);
	break;
	
  case 'A':
	while(!done){
	  if(tag[num] == '\"'){
		read = true;
		num++;
		done = true;
	  }
	  while(read){
		link += tag[num];
		num++;
		if(tag[num] == '\"')
		  read = false;
	  }
	  num++;
	}
	hyperText.push_back(link);
	done = false;
	  
	hyperTextCount++;
	return '[' +  to_string(hyperTextCount) + ']';
	break;

  case 'H':
	if(toupper(tag[2]) == 'T')
	  bodyTag.push(tag);
	break;

  case '/':
	if(toupper(tag[2]) == 'A')
	  return "[]";
	
	else{
	  if(bodyTag.empty()){
		cout << "There is a missing tag to pair with " << tag << endl;
		tagCheck = false;
		
	  }else if(tag[2] == 'B' && bodyTag.top() ==  "<BODY>")
		bodyTag.pop();
	  //html tag
	  
	  else if(tag[2] == 'H' && bodyTag.top() ==  "<HTML>")
		bodyTag.pop();
	  
	  else{
		cout << endl
			 << "There is a missing tag, either the tag goes with "
			 << bodyTag.top() << " or " << tag << endl;
		tagCheck = false;
	  }
	}
	break;
	
  default: return "";
	break;
  }
  return "";
}

void Browser::display(ostream &out) const
{
	out << displayText << endl;
}

ostream& operator<<(ostream& out, const Browser &rhs)
{
	rhs.display(out);
	return out;
}

string Browser::getLink(int index)
{
  string temp = hyperText[index - 1];
  hyperText.clear();
  return temp;
}
