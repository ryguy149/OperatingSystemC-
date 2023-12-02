/*	Ryan Fleury and Maveric Muscat
	04/28/2021
	Project 3

*/

#include <fstream>
#include <iomanip>
#include <time.h>
#include <string>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm> 
#include <math.h> 

using namespace std;

#define SERVICE_MODE	0
#define NORMAL_MODE		1

const char* strPrompt[] = { "[SERVICE MODE]", "[NORMAL MODE]" };

string strLine;
string strCommand;
string strSwitch;
string strOption;
string savedPassword;
string typedPassword;


void statusCmd(void);
void removeCmd(vector <string> s);
void helpCmd(void);

void addCmd(vector <string> s);
void addCoinInMachine(vector <string> coin);
void addColaInMachine(vector <string> cola);
void addBillInMachine(vector <string> bill);
void addCupsInMachine(vector <string> cola);

void removeBillInMachine(vector <string> bill);
void removeCoinInMachine(vector <string> coin);
void removeColaInMachine(vector <string> coin);

string password;

int mode = SERVICE_MODE;

double amountDeposited = 0.0;

int totalOneDollarBills = 0;
int totalFiveDollarBills = 0;
int totalNickels = 0;
int totalDimes = 0;
int totalQuarters = 0;
int totalCoke = 0;
int totalPepsi = 0;
int totalRC = 0;
int totalJolt = 0;
int totalFaygo = 0;
int totalCups = 0;
bool check = false;

void tokenize(string const& str, const char delim, vector<string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

int main(void)

{
	vector<string> out;
	cout << "Please Enter a command and its parameter(s) (type HELP for list of commands, EXIT to quit)\n\n";
	out.push_back("start");//used to get in while loop. need to initalize vector out

	while (out.front() != "EXIT")
	{
		out.clear();
		check = false;

		cout << strPrompt[mode] << ">";
		//cin >> strLine;
		string input;
		getline(cin, input);
		string s = input;

		
		transform(s.begin(), s.end(), s.begin(), ::toupper);
		
		const char delim = ' ';

		tokenize(s, delim, out);
		
		for (auto& s : out)
		{
			cout << s << endl;
		}

		if (out.size() == 0) {
			cout << "error please enter a command!" << endl; 
			out.push_back("start");
			continue;
		}

		if (out.front() == "LOCK" && mode == SERVICE_MODE)
		{
			try {
				mode = NORMAL_MODE;
				out.erase(out.begin());
				password = out.front();
			}
			catch (...) {
				cout << "password input error";
			}

		}

		if (out.front() == "UNLOCK" && mode == NORMAL_MODE)
		{
			try {
				out.erase(out.begin());
				if(password == out.front())
				mode = SERVICE_MODE;
				
			}
			catch (...) {
				cout << "password input error";
			}

		}

		if (out.front() == "STATUS")
		{
			statusCmd();
		}

		if (out.front() == "HELP")
		{
			helpCmd();
		}

		if (out.front() == "BILL")
		{
			out.push_back("1");
			out.erase(out.begin());
			addBillInMachine(out);
		}

		if (out.front() == "COIN")
		{
			out.push_back("1");
			out.erase(out.begin());
			addCoinInMachine(out);
		}

		if (out.front() == "RETURN" )
		{
			cout << "Returning $" << amountDeposited << endl;
			

			if (remainder(amountDeposited, 5) == 0 && totalFiveDollarBills > (amountDeposited / 5.00)) {
				if (amountDeposited / 5 < totalFiveDollarBills) {
					cout << "change is " << amountDeposited / 1 << " Five's" << endl;
					totalFiveDollarBills = totalFiveDollarBills - int(amountDeposited / 5);
					amountDeposited = 0.0;
				}
			}
			else if (remainder(amountDeposited, 1) == 0 && totalOneDollarBills > (amountDeposited / 1.00))
			{
				if (amountDeposited / 1 < totalOneDollarBills) {
					cout << "change is " << amountDeposited / 1 << " One's" << endl;
					totalOneDollarBills = totalOneDollarBills - int(amountDeposited / 1); 
					amountDeposited = 0.0;
				}
			}
			else if (remainder(amountDeposited, 0.25) == 0 && totalQuarters > (amountDeposited / 0.25))
			{
				if (amountDeposited / 0.25 < totalQuarters) {
					cout << "change is " << amountDeposited / 0.25 << " Quarters's" << endl;
					totalQuarters = totalQuarters - int(amountDeposited / 0.25);
					amountDeposited = 0.0;
				}
			}
			else if (remainder(amountDeposited, 0.10) == 0 && totalDimes > (amountDeposited / 0.10))
			{
				if (amountDeposited / 0.10 < totalDimes) {
					cout << "change is " << amountDeposited / 0.05 << " Quarters's" << endl;
					totalDimes = totalDimes - int(amountDeposited / 0.10);
					amountDeposited = 0.0;
				}
			}
			else {
				cout << "cannot give proper change sorry for the inconvienicence!" << endl; 
			}
			
		}

		if (out.front() == "COLA" && amountDeposited >= 0.75)
		{
			//out.push_back("1");
			out.erase(out.begin());
			removeColaInMachine(out);

		}
		else if(out.front() == "COLA" && amountDeposited < 0.75) {
			cout << "Please deposite more money. Current balance in machine: " << amountDeposited << endl;
		}

		if (out.front() == "ADD" && SERVICE_MODE == mode)
		{
			//cout << "First element: " out[1] << out[2];
			out.erase(out.begin());
			//cout << out.front(); 
			addCmd(out);
		}
		if (out.front() == "REMOVE" && SERVICE_MODE == mode)
		{
			//cout << "First element: " out[1] << out[2];
			out.erase(out.begin());
			//cout << out.front(); 
			removeCmd(out);
		}

	}

}

void removeCmd(vector <string> s)
{
	if (s.front() == "COIN") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			removeCoinInMachine(s);
		}
	}
	else if (s.front() == "BILL") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			removeBillInMachine(s);
		}
	}

	else {
		cout << "invalid command";
	}

}



void addCmd(vector <string> s)
{
	if (s.front() == "COIN") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			check = true;
			addCoinInMachine(s);
		}
	}
	else if (s.front() == "COLA") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			addColaInMachine(s);
		}
	}
	else if (s.front() == "BILL") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			check = true;
			addBillInMachine(s);
		}
	}
	else if (s.front() == "CUPS") {
		s.erase(s.begin());
		if (s.size() != 0)
		{
			addCupsInMachine(s);
		}
	}
	else {
		cout << "invalid command";
	}

}





void addCupsInMachine(vector <string> cups) {
	try
	{
		string hold = cups.front();
		totalCups = totalCups + (1 * stod(hold));
		statusCmd();
	}
	catch (...) {
		cout << "please enter a valid argument" << endl;
	}
}





void addBillInMachine(vector <string> bill)
{
	string hold = bill.front();
	try
	{
		if (stod(hold) == 1) {
			bill.erase(bill.begin());
			string hold = bill.front();
			totalOneDollarBills = totalOneDollarBills + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (1 * stod(hold));
			
			statusCmd();
		}
		else if (stod(hold) == 5) {
			bill.erase(bill.begin());
			string hold = bill.front();
			totalFiveDollarBills = totalFiveDollarBills + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (5 * stod(hold));
			
			statusCmd();
		}
		else {
			cout << "Not a valid bill to be added [1, 5]" << endl;
		}
	}
	catch (...) {
		cout << "value error" << endl;
	}
}




void addCoinInMachine(vector <string> coin)
{
	string hold = coin.front();
	try
	{
		if (stod(hold) == 5) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalNickels = totalNickels + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.05 * stod(hold));
			
			statusCmd();
		}
		else if (stod(hold) == 10) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalDimes = totalDimes + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.10 * stod(hold));
			
			statusCmd();
		}
		else if (stod(hold) == 25) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalQuarters = totalQuarters + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.25 * stod(hold));
			
			statusCmd();
		}
		else {
			cout << "Not a valid coin to be added [5,10,25]" << endl;
		}
	}
	catch (invalid_argument)
	{
		if (hold == "NICKEL")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalNickels = totalNickels + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.05 * stod(hold));

			statusCmd();
		}
		else if (hold == "DIME")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalDimes = totalDimes + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.10 * stod(hold));

			statusCmd();
		}
		else if (hold == "QUARTER")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalQuarters = totalQuarters + (1 * stod(hold));
			if (check == false)
			amountDeposited = amountDeposited + (0.25 * stod(hold));

			statusCmd();
		}
		else {
			cout << "Not a valid coin to be added [NICKEL, DIME, QUARTER]" << endl;
		}

	}
}





void addColaInMachine(vector <string> cola)
{
	try
	{
		string hold = cola.front();
		if (hold == "COKE")
		{
			cola.erase(cola.begin());
			string hold = cola.front();
			totalCoke = totalCoke + (1 * stod(hold));
			statusCmd();
		}
		else if (hold == "PEPSI")
		{
			cola.erase(cola.begin());
			string hold = cola.front();
			totalPepsi = totalPepsi + (1 * stod(hold));
			statusCmd();
		}
		else if (hold == "RC")
		{
			cola.erase(cola.begin());
			string hold = cola.front();
			totalRC = totalRC + (1 * stod(hold));
			statusCmd();
		}
		else if (hold == "JOLT")
		{
			cola.erase(cola.begin());
			string hold = cola.front();
			totalJolt = totalJolt + (1 * stod(hold));
			statusCmd();
		}
		else if (hold == "FAYGO")
		{
			cola.erase(cola.begin());
			string hold = cola.front();
			totalFaygo = totalFaygo + (1 * stod(hold));
			statusCmd();
		}
		else {
			cout << "Not a valid coin to be added [COKE, PEPSI, RC, JOLT, FAYGO]" << endl;
		}
	}
	catch (...) {
		cout << "please enter a valid argument" << endl;
	}

}









void removeColaInMachine(vector <string> cola) 
{
		try
		{
			string hold = cola.front();
			if (hold == "COKE" && totalCoke > 0 && totalCups > 0)
			{
				cola.erase(cola.begin());
				if (cola.size() != 0 && cola.front() == "[-NO_ICE]")
					cout << "Dispensing coke with no ice." << endl;
					
				totalCups = totalCups - 1;
				totalCoke = totalCoke - (1);
				amountDeposited = amountDeposited - (0.75);
				cout << "Dispensing coke with ice." << endl;

			}
			else if (hold == "PEPSI" && totalPepsi > 0 && totalCups > 0)
			{
				cola.erase(cola.begin());
				if (cola.size() != 0 && cola.front() == "[-NO_ICE]")
					cout << "Dispensing pepsi with no ice" << endl;

				totalCups = totalCups - 1;
				totalPepsi = totalPepsi - (1);
				amountDeposited = amountDeposited - (0.75);
				cout << "Dispensing Pepsi with ice." << endl;

			}
			else if (hold == "RC" && totalRC > 0 && totalCups > 0)
			{
				cola.erase(cola.begin());
				if (cola.size() != 0 && cola.front() == "[-NO_ICE]")
					cout << "Dispensing RC with no ice." << endl;

				totalCups = totalCups - 1;
				totalRC = totalRC - (1 );
				amountDeposited = amountDeposited - (0.75);
				cout << "Dispensing RC with ice." << endl;
			}
			else if (hold == "JOLT" && totalJolt > 0 && totalCups > 0)
			{
				cola.erase(cola.begin());
				if (cola.size() != 0 && cola.front() == "[-NO_ICE]")
					cout << "Dispensing jolt with no ice." << endl;

				totalCups = totalCups - 1;
				totalJolt = totalJolt - (1);
				amountDeposited = amountDeposited - (0.75);
				cout << "Dispensing jolt with ice." << endl;
			}
			else if (hold == "FAYGO" && totalFaygo > 0 && totalCups > 0)
			{
				cola.erase(cola.begin());
				if (cola.size() != 0 && cola.front() == "[-NO_ICE]")
					cout << "Faygo with no ice" << endl;

				totalCups = totalCups - 1;
				totalFaygo = totalFaygo - (1);
				amountDeposited = amountDeposited - (0.75);
			}
			else if(totalFaygo == 0 || totalJolt == 0 || totalRC == 0 || totalPepsi == 0 || totalCoke == 0  || totalCups == 0){
					cout << "This item is out of stock!" << endl;
			}
			else {
				cout << "Not a valid cola [COKE, PEPSI, RC, JOLT, FAYGO]" << endl;
			}
		}
		catch (...) {
			cout << "please enter a valid argument" << endl;
		}

	
}


void removeCoinInMachine(vector <string> coin)
{
	string hold = coin.front();
	try
	{
		if (stod(hold) == 5) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalNickels = totalNickels - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.05 * stod(hold));
		}
		else if (stod(hold) == 10) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalDimes = totalDimes - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.10 * stod(hold));
		}
		else if (stod(hold) == 25) {
			coin.erase(coin.begin());
			string hold = coin.front();
			totalQuarters = totalQuarters - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.25 * stod(hold));
		}
		else {
			cout << "Not a valid coin to be added [5,10,25]" << endl;
		}
	}
	catch (invalid_argument)
	{
		if (hold == "NICKEL")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalNickels = totalNickels - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.05 * stod(hold));
		}
		else if (hold == "DIME")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalDimes = totalDimes - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.10 * stod(hold));
		}
		else if (hold == "QUARTER")
		{
			coin.erase(coin.begin());
			string hold = coin.front();
			totalQuarters = totalQuarters - (1 * stod(hold));
			amountDeposited = amountDeposited - (0.25 * stod(hold));
		}
		else {
			cout << "Not a valid coin to be added [NICKEL, DIME, QUARTER]" << endl;
		}

	}
}



void removeBillInMachine(vector <string> bill)
{
	string hold = bill.front();
	try
	{
		if (stod(hold) == 1) {
			bill.erase(bill.begin());
			string hold = bill.front();
			totalOneDollarBills = totalOneDollarBills - (1 * stod(hold));
			amountDeposited = amountDeposited - (1 * stod(hold));
		}
		else if (stod(hold) == 5) {
			bill.erase(bill.begin());
			string hold = bill.front();
			totalFiveDollarBills = totalFiveDollarBills - (1 * stod(hold));
			amountDeposited = amountDeposited - (5 * stod(hold));
		}
		else {
			cout << "Not a valid bill to be added [1, 5]" << endl;
		}
	}
	catch (...) {
		cout << "value error" << endl;
	}
}




void helpCmd(void)
{
	if (mode == 1) //normie mode
	{
		cout << endl <<
			"Commands in Normal Mode are:" << endl <<
			"COIN <value> where value is [5, 10, 25, NICKEL, DIME, QUARTER]" << endl <<
			"Bill <value> where value is 1 5" << endl <<
			"Cola <value> where value is [COKE PEPSI RC JOLT FAYGO [-no_ice]]" << endl <<
			"Return" << endl <<
			"Status" << endl <<
			"Exit" << endl <<
			"Unlock [password]" << endl;
	}

	if (mode == 0) //service mode
	{
		cout << endl <<
			"Commands in Service Mode are:" << endl <<
			"COIN <value> where value is [5, 10, 25, NICKEL, DIME, QUARTER]" << endl <<
			"Bill <value> where value is 1 5" << endl <<
			"Cola <value> where value is [COKE PEPSI RC JOLT FAYGO [-no_ice]]" << endl <<
			"Return" << endl <<
			"Status" << endl <<
			"Exit" << endl <<
			"Add [COLA|CUPS] brand <quantity>" << endl <<
			"Add|Remove [Coins|Bills] <denomination> <quantity>" << endl <<
			"Lock [password]" << endl;
	}
}



void statusCmd(void)
{
	cout << fixed;
	cout << setprecision(2);
	cout << "Money Deposited--- " << amountDeposited << endl;
	cout << "Total # of 1's---- " << totalOneDollarBills << endl;
	cout << "Total # of 5's---- " << totalFiveDollarBills << endl;
	cout << "Total Nickels----- " << totalNickels << endl;
	cout << "Total Dimes------- " << totalDimes << endl;
	cout << "Total Quarters---- " << totalQuarters << endl;
	cout << "Total Coke-------- " << totalCoke << endl;
	cout << "Total Pepsi------- " << totalPepsi << endl;
	cout << "Total RC---------- " << totalRC << endl;
	cout << "Total Jolt-------- " << totalJolt << endl;
	cout << "Total Faygo------- " << totalFaygo << endl;
	cout << "Total Cups-------- " << totalCups << endl;
}