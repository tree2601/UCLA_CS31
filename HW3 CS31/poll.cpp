#include<string>
#include<cassert>
#include<iostream>
using namespace std;

bool checkstate(string text, int& pos) {
	string state = "";
	while (isalpha(text[pos])) {
		state += toupper(text[pos]);
		pos++;
	}                    //collecting the beginning letters of the string.  
	if (state == "AL" || state == "AK" || state == "AZ" || state == "AR" || state == "CA" || state == "CO" || state == "CT" || state == "DE" || state == "FL" ||
		state == "GA" || state == "HI" || state == "ID" || state == "IL" || state == "IN" || state == "IA" || state == "KS" || state == "KY" || state == "LA" ||
		state == "ME" || state == "MD" || state == "MA" || state == "MI" || state == "MN" || state == "MS" || state == "MO" || state == "MT" || state == "NE" ||
		state == "NV" || state == "NH" || state == "NJ" || state == "NM" || state == "NY" || state == "NC" || state == "ND" || state == "OH" || state == "OK" ||
		state == "OR" || state == "PA" || state == "RI" || state == "SC" || state == "SD" || state == "TN" || state == "TX" || state == "UT" || state == "VT" ||
		state == "VA" || state == "WA" || state == "WV" || state == "WI" || state == "WY")
		return true;   
	else
		return false; // check whether the string starts with a state if it is not empty."

					  //pseudocode:
					  //find the beginning letters of the text
					  //if the beginning letters form a state name, return true.
					  //otherwise return false. 
					
}


bool checkpartyresult(string text, int& pos) {
	while(pos!=text.size()) {
		string number = "";
		while (isdigit(text[pos])){
			number += text[pos];
			pos++;
		}                           
		if (number == "")
			return false;//check whether the following part of the string starts with a number;
		else {
			if (pos == text.size())
				return false;//check whether the number is followed by some character;
			else if (isalpha(text[pos])) {
				pos++;//if the following chararcter is a letter, move to the next character;
			}
			else
				return false;
		}

		}	
		return true;//check whether the state is followed by a series of legal party results;

					//pseudocode:
		//repeatedly:
		//    check whether the text reaches the end;
		//    find a number starting from the given position in the text;
		//    if no number found, return false;
		//    check whether the text reaches the end;
		//    if it reaches the end, return false;
		//    check whether the following character is a letter;
		//    increment the number indicating the position;

	
	}
		

bool hasProperSyntax(string pollData) {
	for (int k = 0; k < pollData.size(); k++) {
		if (pollData[0] == ',' || pollData[pollData.size() - 1] == ',')//check if the string begins or ends with a comma. 
			return false;
		
			string sample = "";
			while (pollData[k] != ',') {
				sample += pollData[k];
				k++;
				if (k >= pollData.size()) {
					break;
				}
				//quit the loop if it reaches the end of the string;
			}//collect a part of the string until it reaches a comma;
			int i = 0;
			if (!checkstate(sample, i))
				return false;
			else if (!checkpartyresult(sample, i))
				return false;            //check whether this collected part of the string is legal;
		}
	
	
	return true;          //the pollData is legal if it passes all the tests above. 
						 
  //pseudocode:
	// repeatedly:
	    // if the string starts or ends with a comma, return false;
	    // collect a substring from the string until it reaches a comma.
	    // if the string reaches the end, break;
	    //check if the string starts with a state name, return false if not;
	    //check if the state name is followed by a random number of party results, return false if not. 
	//return true if the string reaches the end;

}

int tallySeats(string pollData, char party, int& seatTally) {
	if (!hasProperSyntax(pollData))
		return 1;
	else if (!isalpha(party))
		return 2;
	else
		seatTally = 0;
		for (int j = 0; j < pollData.size(); j++) {
			if (toupper(pollData[j]) == toupper(party)&&j!=0&&isdigit(pollData[j-1]))   //enter the if statement only when the character matches input party, is not the first letter, and follows a digit;
			{
				int k = j;//A substitute is used to get j's value while keeping j unchanged;
				int square = 0;//To record the position of a digit in a number. 
				do {
					k--;
					int n = pollData[k] - '0';//convert the character into the corresponding digit;
					int m = square;//A substitute is used to get square's value while keeping square unchanged;
					while(m>0)
					{
						n *= 10;
						m--;
					}             //the digit will be adjusted to be in ones, tens,hundreds..... based on what is collected;
					seatTally += n;//Each collected digit will add to the seatTally 
					square++;
				} while (isdigit(pollData[k-1]));//check if the previous character is still a digit;
			}
			
				


		}
		return 0;
		//pseudocode:
		//check if the input string is legal, return 1 if not;
		// check if the input party is legal, return 2 if not;
		//repeatedly:
		    //find the letter matching with the input party, proceed only if it is in a party result;
		    //record its position;
		    //repeatedly:
		                 //find a number character before the letter,
		                 //convert it to int;
		                 //adjust it to the correct digit place;
		                // increment number of seats;
		                 // increment the digit place
		//return 0 when the string reaches the end;
		    

}


int main() {
	assert(hasProperSyntax("ca54t9f33a"));
	assert(!hasProperSyntax("GG"));
	assert(!hasProperSyntax("Ak4"));
	assert(!hasProperSyntax("deep_dark_fantasy"));
	assert(hasProperSyntax("De45d"));
	assert(hasProperSyntax("ny43t98e65r,nm,Ut43g114514h,AK80s"));
	assert(hasProperSyntax("CA3d5r"));
	assert(hasProperSyntax("ny3d4e65e5t7688765r43v"));
	assert(hasProperSyntax("nm,ny34n,tn12q19n"));
	assert(!hasProperSyntax("nm,ny34n,tn12q19n,CA87+43t"));
	assert(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D"));
	assert(!hasProperSyntax("NY114514D,,,,KS4R"));
	assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
	assert(!hasProperSyntax(","));
	assert(!hasProperSyntax("TN98d,"));
	assert(!hasProperSyntax(",TN98d,"));
	assert(!hasProperSyntax(",TN98d"));

	int seats = 99;
	assert(tallySeats(",",'d',seats)==1&&seats==99);
	assert(tallySeats("d34e", 'd', seats) == 1 && seats == 99);
	assert(tallySeats("nm,ny34n,tn12q19n", 'n', seats) == 0&& seats == 53);
	seats = 99;
	assert(tallySeats(",", 'd', seats) == 1 && seats == 99);
	assert(tallySeats("ca54e", '@', seats) == 2 && seats == 99);
	assert(tallySeats("ca54e", '5', seats) == 2 && seats == 99);
	assert(tallySeats("ca87g12b333v,nm12s", 'd', seats) == 0 && seats == 0);
	assert(tallySeats("ut1919t810e,ak514t6324w", 't', seats) == 0 && seats == 2433);
	seats = 99;
		

	cout << "well done. "<<endl;
	

	//for debugging

}












	/* string mydata = "";
	getline(cin, mydata);
	char myparty;
	cout << "give a party";
	cin >> myparty;
	int mynumber = 0;
	int return_value= tallySeats(mydata, myparty, mynumber);
	if (return_value == 1)
		cout << "return value is " << return_value;

	else if (return_value == 2)
		cout << "return value is " << return_value;

	else if(return_value == 0){
		cout << "return value is " << return_value;
		cout << "the number of seats is " << mynumber;
	}
		
	
	//just for debugging;

}

*/
	

	
		
		
		
