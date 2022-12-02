//*****************
//Program Name: Flash Card Program
//Author: Daniel Arlegui
//IDE Used: Eclipse
//*****************

//Libraries
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <map>
#include <list>
using namespace std;

const int maxQuestions = 10; //Fixed number of questions

//Function(s)
void getFile(map<string, string> &map);
void Quiz(map<string, string> &map, list<string> &list);

int main()
{
	//Housekeeping
	map<string, string> US; //State, Capitol
	list<string> repeats;

	//Getting File
	getFile(US);

	/*for(auto it : US){ //Answer Key
		cout << "States: " << setw(14) << it.first << setw(13) << "Capitols: " << it.second << endl;
	} */

	//Quiz Time
	Quiz(US, repeats);

	return 0;
}

//getFile(): gets the file inputs to the map
//Arguments: (map<string, string> &map) | Returns: void
void getFile(map<string, string> &map){
	string state, capitol;
	ifstream fin("capitols.txt");
	if(!fin){
		cout << "\n\nError: input file does not exist.";
		exit(EXIT_FAILURE);
	}
	while(!fin.eof()){ //Capitols, State
		getline(fin, capitol);
		getline(fin, state);
		map.emplace(state, capitol);
	}
	fin.close();
	//Has an issue where it captures the two last blank lines of the file.
	//Don't know how to fix...
}

//Quiz(): QUIZ TIME FOR THE USER
//Arguments: (map<string, string> &map) | Returns: void
void Quiz(map<string, string> &map, list<string> &list){
	srand(time(0));
	int correct = 0, incorrect = 0, coinFlip = rand() % 2 + 1;; //CoinFlip for either quizing for states or capitols
	string response, first, second, full, answer;

	//GAME TITLE
	cout << "I'm going to test you with 10 questions on states and capitols.\n\n";

	multimap<string, string>::iterator miter; //Map iterator
	for(int i = 0; i < maxQuestions; i++){ //Quiz starting
		miter = map.begin();
		for(int j = 0, size = map.size(); j < rand() % size; j++) //Randomizing Question
			miter++;
		//Questioning them on the capitol
		if(coinFlip == 1){
			cout << miter->second << " is the capitol of what state? ---> ";
			getline(cin, response);
			//Making the answer & response all lowercase
			answer = miter->first;
			transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
			transform(response.begin(), response.end(), response.begin(), ::tolower);
			if(response == answer){
				correct++;
				cout << "Correct!\n\n";
			}
			else{
				stringstream ss(answer);
				ss >> first >> second;
				full = first + second; //New answer key if answer has two letters
				if(response == full){ //Makes sure they still get the right answer if no space between 2 letters
					correct++;
					cout << "Correct!\n\n";
				}
				else{
					incorrect++;
					cout << "Incorrect! Right answer was " << miter->first << "\n\n";
				}
			}
		}
		else{ //Making them Question on what state
			cout << "What is the capitol of " << miter->first << "---> ";
			getline(cin, response);
			//Making the answer & response all lowercase
			answer = miter->second;
			transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
			transform(response.begin(), response.end(), response.begin(), ::tolower);
			if(response == answer){
				correct++;
				cout << "Correct!\n\n";
			}
			else{
				stringstream ss(answer);
				ss >> first >> second;
				full = first + second; //New answer key if answer has two letters seperated
				if(response == full){ //Makes sure they still get the right answer if no space between 2 letters
					correct++;
					cout << "Correct!\n\n";
				}
				else{
					incorrect++;
					cout << "Incorrect! Right answer was " << miter->second << "\n\n";
				}
			}
		}
		//Making sure they don't get the same question
		map.erase(miter);
		//To not allow duplicate questions, Though map.erase(miter) already does the job done
		list.push_back(miter->first);
	}

	//Results
	cout << "\nYou got " << correct << " out of " << maxQuestions << " right. | "
		 << (float)correct / (maxQuestions * .01) << "%" << " Grade"<< endl;
	cout << "\n/* Quiz Statistics */\n" << "Correct answers: " << correct <<
			"\nIncorrect answers: " << incorrect << endl;
}
