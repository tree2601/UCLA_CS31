using namespace std;
#include<iostream>
#include <cassert>

int appendToAll(string a[], int n, string value) {
	if (n >= 0) {
		for (int i = 0; i < n; i++)
		{
			a[i] += value;
		}
		return n;
	}
	return -1;
}//function 1

int lookup(const string a[], int n, string target) {
	for (int i = 0; i < n; i++) {
		if (a[i] == target)
			return i;
	}
	return -1;
}//function 2;

int positionOfMax(const string a[], int n) {
	if (n > 0) {
		int max = 0;
		string Max = a[0];
		for (int i = 0; i < n; i++)
		{
			if (a[i] > Max) {
				Max = a[i];
				max = i;
			}
		}
		return max;
	}
	return -1;
}//function 3;

int rotateLeft(string a[], int n, int pos) {
	if(n >= 0 && pos >= 0 && pos < n){
		string sample = a[pos];
		for(int i=pos;i<n-1;i++)
		{
			a[i] = a[i + 1];
		}
		a[n - 1] = sample;
		return pos;
}
	return -1;
}//function 4;

int countRuns(const string a[], int n) {
	if (n > 0) {
		int i = 1;
		string sample = a[0];
		for (int k = 0; k < n; k++) {
			if (a[k] != sample)
			{
				sample = a[k];
				i++;
			}
		}
		return i;
	}
	else if (n == 0)
		return 0;
	return -1;
}//function 5;

int flip(string a[], int n) {
	if (n >= 0)//the question of zero;
	{
		int k = 0;
		while(k<=n-1-k)
		{
			string sample = a[k];
			a[k] = a[n - 1 - k];
			a[n - 1 - k] = sample;
			k++;
		}
		return n;
	}
	return -1;
}//function 6;

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 >= 0&&n2>=0){
		int i = 0;
		while (i < n1&&i < n2) {
			if (a1[i] != a2[i])
				return i;
			i++;
		}
		return i;
}
	return -1;

}//function 7;
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 > 0 && n2 >= 0)
	{
		for (int i = 0; i < n1; i++) {
			int k = 0;
			int j = i;
			while (j < n1&&k < n2&&(a1[j] == a2[k])) {
				k++;
				j++;
			}
			if (k == n2)
				return i;
		}
		return -1;
	}
	else if (n1 == 0 && n2 == 0)
		return 0;
	return -1;
}//function 8;

int lookupAny(const string a1[], int n1, const string a2[], int n2){
	if (n1 >= 0 && n2 >= 0) {
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n2; j++) {
				if (a1[i] == a2[j])
					return i;
			}
		}
	}
	return -1;
		

}//function 9;

int divide(string a[], int n, string divider)
{
	if (n >= 0) {
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < n - i-1; j++) {
				if (a[j] > a[j + 1])
				{
					string sample = a[j];
					a[j] = a[j + 1];
					a[j + 1] = sample;
				}
			}
		}
		for (int k = 0; k < n; k++) {
			if (a[k] >= divider)
				return k;
		}
		return n;
	}
	return -1;
}//function 10;

;
int main()
{
	string s1[10] = { "billy","tree","michael","van","grace","","andrews" };
	assert(divide(s1,7,"nmsl")==5&&s1[2]=="billy");

	string s2[] = { "","michael","%%%" };
	int n2 = appendToAll(s2, 3, "666");
	assert(s2[0]=="666"&&s2[2]=="%%%666"&&n2==3);

	string s3[10] = { "billy","tree","michael","van","grace","","van","andrews" };
	int n3 = positionOfMax(s3, 8);
	assert(n3 == 3);

	string s4[10] = { "billy","tree","michael","van","grace","","van","andrews" };
	int n4 = rotateLeft(s4, 8, 4);
	assert( s4[7] == "grace"&&s4[4] == ""&&s4[5] == "van") ;

	string s5[10] = { "billy","tree","michael","van","grace","","van","andrews" };
	int n5 = rotateLeft(s5, 8, 0);
	assert(s5[7] == "billy"&&s5[1]=="michael");

	string s6[10] = { "billy","tree","tree","van","van","van","van","andrews" };
	int n6 = countRuns(s6, 8);
	assert(n6 == 4);

	string s7[10] = { "billy","tree","michael","grace","jimmy","van","van","andrews" };
	int n7 = flip(s7,6);
	assert(n7 == 6 && s7[0] == "van"&&s7[1] == "jimmy"&&s7[4] == "tree");
	int n71 = flip(s7, 1);
	assert(n71 == 1 && s7[0] == "van"&&s7[1] == "jimmy");

	string s81[10] = { "billy","tree","michael","grace","jimmy","van","van","andrews" };
	string s82[10] = { "billy","tree","michael","grace" };
	int n81 = differ(s81, 8, s82, 4);
	assert(n81 == 4);

	string s91[10] = { "billy","tree","michael","grace","jimmy","van","van","andrews" };
	string s92[10] = { "grace","","jimmy","van","van","andrews" };
	int n91 = subsequence(s91, 8, s92, 0);//wait!!!
	assert(n91 == 0);

	string s101[10] = { "billy","tree","michael","grace","jimmy","van","van","andrews" };
	string s102[2] = { "ff" };
	int n101 = lookupAny(s101, 8, s102,1);
	assert(n101 == -1);

	string s111[10] = { "billy","tree","michael","grace","jimmy","van","van","andrews" };
	int n111 = divide(s111, 7, "jimmy");
	assert(n111 ==2  && s111[2] == "jimmy");







	cout << "那真的牛批" << endl;




}// use cerr;