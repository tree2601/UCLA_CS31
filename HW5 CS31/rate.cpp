using namespace std;
const int MAX_WORD_LENGTH = 20;
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<cctype>
#include<cassert>
#include<iostream>


bool checkword (char word[]) {
		if (word[0] == '\0')
			return false;//check if the nth row is empty. 
		for (int i = 0; word[i] != '\0'; i++) {
			if (!isalpha(word[i])) {
				return false;
			}
			
		}
		return true;
	
	
}//check whether the nth row in an array is a word made up of letters;


void convert(char word[]) {
	for (int i = 0; word[i] != '\0'; i++) {
		word[i] = tolower(word[i]);
	}
}//convert a char array into lower letters.

bool isrepeat(const char word1[], const char word2[], const char word3[], const char word4[]) {
	return((strcmp(word1, word3) == 0 && strcmp(word2, word4) == 0 )||( (strcmp(word1, word4) == 0 && strcmp(word2, word3) == 0)));
}//check whether two sets of patterns are repeated. 

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns)
{

	if (nPatterns > 0) {
		int i = 0;//recording the position through the whole char array;
		int j = 0; //recording the position through the "correct" char array;
		while (i < nPatterns) {
			if (separation[i] >= 0 && checkword(word1[i]) && checkword(word2[i])) {
				convert(word1[i]);
				convert(word2[i]);
				separation[j] = separation[i];
				strcpy(word1[j], word1[i]);
				strcpy(word2[j], word2[i]);
				i++;
				j++;


			}
			else {
				i++;
			}
		}//put all the proper patterns in the leading positions of each array; 
		//now j is the number of proper patterns; 
		for (int k = 0; k < j; k++) {
			for (int g = k + 1; g < j; g++) {
				if (isrepeat(word1[k], word2[k], word1[g], word2[g])) {
					if (separation[g] > separation[k])
						separation[k] = separation[g];
					word1[g][0]=='\0';
					word2[g][0]=='\0';
					separation[g] = -1;

				}
			}
		};//find all the repeated patterns and convert them to zero bytes and -1;

		int s = 0;
		int t = 0;
		while (s < j) {
			if (strlen(word1[s]) != 0 || strlen(word2[s]) != 0 ||separation[s] != -1)
			{
				separation[t] = separation[s];
				strcpy(word1[t], word1[s]);
				strcpy(word2[t], word2[s]);
				t++;
				s++;
			}
			else {
				s++;
			}

		}
		return t;//put all the unique proper patterns and put them to the leading positions of each array; 
		//t is the number of proper,unique patterns. 




	}
	return 0;//return 0 if nPatterns is not a positive integer; 
}


void adjust(char text[]) {
	for (int i = 0; i < strlen(text); i++) {
		while (!isalpha(text[i]) && text[i] != ' '&&text[i] != '\0') {
			for (int j = i; text[j] != '\0'; j++) {
				text[j] = text[j + 1];
			}
		}
	}
	//delete all the characters except for letters and spaces in a C string;
	for (int k = 0; text[k] != '\0'; k++) {
		if (text[k] == ' ') {
			while (text[k + 1] == ' ') {
				for (int q = k + 1; text[q] != '\0'; q++) {
					text[q] = text[q + 1];
				}
			}
		}
	}//adjust all consecutive spaces into one single space;
}


int findword(const char text[], const char word[],int pos[]) {
	int n = 0;//check how many times the word appears in the text;
	for (int i = 0; text[i] != '\0'; i++) {
		int k = 0;
		while (word[k] != '\0'&&text[i + k] != '\0'&&word[k] == text[i + k]) {
			k++;
		}//comparing the characters in word with those in the text one by one;
		if (k == strlen(word)) {  //if k is equal to the length of word, that means it contains all the characters in word in the correct order;
			if (text[i + k] == '\0' || text[i + k] == ' ') {//check if the word is followed by a space or it reaches the end of the text;
				if (i == 0 ||text[i - 1] == ' ')//check if the word follows a space or it is the beginning of the text;
					pos[n] = i;//use the pos array to record the position where the word's first letter shows up;
				    n++;
			}
		}
	 }
	
	return n;
}//check whether a word exists in a given text.returns the number of times it shows up in the text; 

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
int min(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {
	int r = 0;
	char copy[250];//use a copy of the original document;
	strcpy(copy, document);
	adjust(copy);//leave only letters and spaces;remove any consecutive spaces;
	convert(copy);//convert copy into lower case;

	for (int m = 0; m < nPatterns; m++) {
		bool match = false;
		int word1pos[250];//record the position of first letter of word 1;
		int word2pos[250];//record the position of first letter of word 2;
		int count1 = findword(copy,word1[m],word1pos);//record the number of times word 1 shows up in the copy;
		int count2 = findword(copy, word2[m], word2pos);//record the number of times word 2 shows up in the copy;

		if(count1>0&&count2>0){
			for (int i = 0; i < count1; i++) {
				for (int j = 0; j < count2; j++) {
					
					int begin = min(word1pos[i], word2pos[j]);
					int end = max(word1pos[i], word2pos[j]);
					int space = 0;
					for (int k = begin; k < end; k++) {
						if (copy[k] == ' ')
							space++;
					}//check the number of spaces the part of the copy from begin to end contains;
					if (space >= 1 && space <= separation[m] + 1)//separation of n words will have separation of n+1 spaces; Also they must be at least one space apart to avoid overlapping of the same words;
					{
						match = true;
					}
				}
			}
		}
	if (match == true) //if the two words exist and fall within the range;
			r++;
		
	}
	return r;
}


int main() {
	cerr << "start" << endl;
	char worda[3][21] = { "mad","deranged","nefarious"};
	char wordb[3][21] = { "scientist","robot","plot" };
	int separationx[3] = { -99,3,0 };
	int x = makeProper(worda, wordb, separationx, 3);
	cerr << "x is" << x << endl;

	/*char sampletext[250];
	strcpy(sampletext, "!!! dogs this sentence contains many words, and we need to do it as we check if the findword function works nonrmally for the words it contains. 2 dogs watch watch dogs 2:) ");
	char word7[8][21] = {"this","dogs","words","useless","looks","need","check","do"};
	char word8[8][21] = {"sentence","watch","contains","test","like","if","if","findword"};
	int separation3[8] = {2,1,0,8,0,10,0,1};
	int mypos[250];
	int mycount=0;
	int x = 8;
	adjust(sampletext);
	convert(sampletext);
	mycount =findword(sampletext,"it",mypos );
	
	int samplerate = rate(sampletext, word7, word8, separation3, x);

	cerr << "the length is" << strlen(sampletext) << endl;
	cerr << "the rate is " << samplerate << endl;*/
	
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};
	
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	
	
	
	cout << "All tests succeeded" << endl;
}

/*assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
	test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
assert(rate("**** 2018 ****",
	test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
assert(rate("  That plot: NEFARIOUS!",
	test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
assert(rate("deranged deranged robot deranged robot robot",
	test1w1, test1w2, test1dist, TEST1_NRULES) == 1);*/

/*cerr << "the length is" << strlen(sampletext) << endl;
cerr << "the number I found is " << mycount << endl;*/

	

/*for (int s = g; s < j - 1; s++) {
separation[s] = separation[s + 1];
strcpy(word1[s], word1[s + 1]);
strcpy(word2[s], word2[s + 1]);
}
j--;*/

/*char word1[11][21] = { "michael","aaaa","Michael","6324","david","computationofmath","ucla_student","david","grace","michael","tree" };
char word2[11][21] = { "grace","aaaa","tree","tree","smallberg","computation","ucla_professor","smallberg","michael","grace","Michael" };
int separation[11] = { -7,4,6,7,3,-5,7,8,12,9,12 };
char word3[8][21] = { "","bigbro","bb","blizzard1","biu","ben","blizzard","brobig" };
char word4[8][21] = { "rua","brobig","ben","blizzard","GG","Bb","blizzard1","bigbro" };
char word5[6][21] = { "peter","gg","peters","michellee","tetete","gesports" };
char word6[6][21] = { "peters","samuel","peters","momomomo","hahahaha","virtuspro" };
int separation2[6] = { 32,1,32,4,4,11 };
int separation1[8] = { 7,2,3,5,5,17,21,8 };

int n = 6;
int count = makeProper(word5, word6, separation2, n);
cerr << "the number is " << count << endl;
for (int b = 0; b < n; b++) {
cerr << word5[b] << ", " << word6[b] << ", " << separation2[b] << endl;
};*/

/*char text1[250] = "!!!?this is test of my project 5 for CS31. I want to check whether it can find out and remove all characters,like !! or#, except for letters and spaces.";
adjust(text1);
for (int b = 0; text1[b] != '\0'; b++) {
cerr << text1[b];
}*/