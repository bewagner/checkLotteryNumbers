#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>

using namespace std;

/**
   Trim whitespace and tabs from a given string.
**/ 
string trim(string& str) {
	str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last-first+1));
}

/**
   Extract numbers from a given .csv file. 
   In this file, each line should contain one number and there should be no dividers like commas, dots …
**/ 
vector<string> extractNumbers(string fileName) {
	vector<string> l;
	ifstream file(fileName);
	string value;

	while(file.good()) {
		getline(file, value, '\n');
		if(value.length() > 0) {
			l.push_back(trim(value));
		}
	}
	file.close();
	return l;
}

/**
   Check if two given strings, a and b, are of the right format.
   That is, both are longer than four characters and have "*.csv" as their ending.
**/ 
bool isWrongFileFormat(string a, string b) {
	string fileEnding =  ".csv";
	string aEnding = a.substr(a.length() - 4, a.length());
	string bEnding = b.substr(b.length() - 4, b.length());

	if(a.length() < 4 || b.length() < 4 || aEnding != fileEnding || bEnding != fileEnding ) {
		return 1;
	}else {
		return 0;
	}
}


/**
   Print the correct usage for this program.
**/ 
void printUsage() {
	cerr << "Usage:" << endl
		 << "checkLotteryNumbers\t <correct numbers>.csv\t <my numbers>.csv"
		 << endl;
}

/**
   Print an according message, if you have won.
**/ 
bool printWin(string &number, string prizeName, string amount) {
	cout << "You won the "
		 << prizeName
		 << "!"
		 << endl
		 << "Your prize is "
		 <<  amount
		 << " NT$."
		 << endl
		 << "The winning number is "
		 << number
		 << "."
		 << endl << endl;
	return true;
}

/**
   Get the last n numbers of a given string.
**/ 
string getNLastNumbers(string &s, int n) {
	return s.substr(s.length() - n, s.length());
}

/** 
	Check for illegal characters in the input files.
**/ 
bool checkForIllegalCharacters(vector<string> v,  string filename) {
	for(unsigned int i = 0; i < v.size(); i++){
		if(!std::all_of(v[i].begin(), v[i].end(), ::isdigit)) {
			cout << "There was an illegal character (= not a number) on line "
				 << i + 1
				 << " of the file "
				 << filename
				 << endl
				 << v[i] << endl;
			return true;
		}
	}
	return false;
}



/**
   Issue a warning for custom numbers that are not 8 digits in length
**/ 
void issueWarning() {
	cout << "One of your custom numbers was shorter or longer than 8 digits. That is probably an error. Please check your input file." 
		 << endl << endl;
}

int main(int argc,  const char** argv) {
	// Check input
	if(argc !=  3 || isWrongFileFormat(argv[1], argv[2])) {
		printUsage();
		return -1;
	}
	
	// Read in files
	vector<string> correctNumbers = extractNumbers( argv[1]);
	vector<string> myNumbers = extractNumbers( argv[2]);
	
	if(checkForIllegalCharacters(correctNumbers, argv[1]) || checkForIllegalCharacters(myNumbers, argv[2])) {
		return EXIT_FAILURE;
	}
	
	// Initialize correct numbers
	string specialPrize =  correctNumbers[0];
	string grandPrize =  correctNumbers[1];
	vector<string> firstPrize(3);
	for(int i = 0; i < 3; i++) {
		firstPrize[i] =  correctNumbers[i + 2];
	}
	vector<string> additionalSixthPrize(4);
	for(int i = 0; i < 4; i++) {
		additionalSixthPrize[i] =  correctNumbers[i + 5];
	}
	
	
	// Check if I have won something for each number.
	bool won = false;
	
	for(auto s:myNumbers) {
				
		if(s.length() != 8){
			issueWarning();
		}
		
		// Check if I have won
		if(s == specialPrize) {
			won =  printWin(s, "special prize", "10.000.000");
		}
		
		if(s == grandPrize) {
			won =  printWin(s, "grand prize", "2.000.000");
		}
		
		for(auto n : firstPrize){
			// First prize
			if(s == n) {
				won =  printWin(s, "first prize", "200.000");
				continue;
			}	
			
			// Second prize
			if(getNLastNumbers(s, 7) == getNLastNumbers(n, 7)) {
				won =  printWin(s, "second prize", "40.000");
				continue;
			}

			// Third prize
			if(getNLastNumbers(s, 6) == getNLastNumbers(n, 6)) {
				won =  printWin(s, "third prize", "10.000");
				continue;
			}
			
			// Fourth prize
			if(getNLastNumbers(s, 5) == getNLastNumbers(n, 5)) {
				won =  printWin(s, "fourth prize", "4.000");
				continue;
			}
			
			// Fith prize
			if(getNLastNumbers(s, 4) == getNLastNumbers(n, 4)) {
				won =  printWin(s, "fifth prize", "1.000");
				continue;
			}
			
			// Sixth prize
			if(getNLastNumbers(s, 3) == getNLastNumbers(n, 3)) {
				won =  printWin(s, "sixth prize", "200");
				continue;
			}
		}
		
		// Additional sixth prize
		for(auto n : additionalSixthPrize) {
			if(getNLastNumbers(s, 3) == n) {
				won =  printWin(s, "additional sixth prize", "200");
			}
		}
	}
	

	if(!won) {
		cout << "Sadly, you didn't win anything this time." << endl;
	}

	return EXIT_SUCCESS;
}
