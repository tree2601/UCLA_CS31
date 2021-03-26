#include<iostream>
#include<string>
using namespace std;

int main() {
	
	cout << "Odometer at start: ";
	int start;
	cin >> start;

	cout << "Odometer at end: ";
	int end;
	cin >> end;

	cout << "Rental days: ";
	int days;
	cin >> days;
	cin.ignore(1000, '\n');

	cout << "Customer name: ";
	string username;
	getline(cin,username);
	
	cout << "Luxury car? ";
	string luxury;
	getline(cin, luxury);

	cout << "Month (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;

	double charge=0;
	if (luxury == "y")
		charge = days * 61;
	else if (luxury == "n")
		charge = days * 33;

	int miles = end - start;
	if (miles <= 100)
		charge = charge + 0.27*miles;
	else if (miles <= 400)
	{
		if (month == 12 || month == 1 || month == 2 || month == 3)
			charge = charge + 27 + (miles - 100)*0.27;
		else 
			charge = charge + 27 + (miles - 100)*0.21;
	}
	else if (miles > 400)
	{
		if (month == 12 || month == 1 || month == 2 || month == 3)
			charge = charge + 27+ 81 + (miles - 400)*0.19;
		else 
			charge = charge + 21 +63 + (miles - 400)*0.19;
	}
	cout << "---" << endl;
	if (start <= 0)
		cout << "The starting odometer reading must be nonnegative." << endl;
	else if (miles < 0)
		cout << "The final odometer reading must be at least as large as the starting reading.";
	else if (days <= 0)
		cout << "The number of rental days must be positive.";
	else if (username == "")
		cout << "You must enter a customer name.";
	else if (luxury != "y"&&luxury != "n")
		cout << "You must enter y or n.";
	else if (month < 1 || month>12)
		cout << "The month number must be in the range 1 through 12.";
	else
		cout << "The rental charge for customer is $" << charge;

	
}