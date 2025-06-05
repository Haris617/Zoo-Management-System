#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class RAW {
public:
	void write(string s1, char c1, string s2, int i1, string s3, ofstream& f) {

		f << s1 << "," << c1 << "," << s2 << "," << i1 << "," << s3 << endl;
		f.close();
	}
	void read(ifstream& f) {
		string line;
		while (getline(f, line))
		{
			string tempId = "", tempSpecies = "", tempGender = "", tempHabitatNo = "", tempFeedTime = "";
			int i = 0;

			while (i < line.length() && line[i] != ',')
			{
				tempId += line[i++];
			}
			i++;
			if (i < line.length())
			{
				tempGender += line[i++];
			}
			i++;

			while (i < line.length() && line[i] != ',')
			{
				tempSpecies += line[i++];
			}
			i++;



			while (i < line.length() && line[i] != ',')
			{
				tempHabitatNo += line[i++];
			}
			i++;

			while (i < line.length())
			{
				tempFeedTime += line[i++];
			}


			cout << "ID           :   " << tempId << endl;
			cout << "Gender       :   " << tempGender << endl;
			cout << "Data 1       :   " << tempSpecies << endl;
			cout << "Data 2       :   " << tempHabitatNo << endl;
			cout << "Data 3       :   " << tempFeedTime << endl;
		}

		f.close();
	}
};
class Animal :public RAW {
private:
	string id;
	char gender;
	string species;
	int habitatNo;
	string feedTime;

public:

	Animal()
	{
		id = "";
		gender = ' ';
		species = "";
		habitatNo = 0;
		feedTime = "";
	}

	void inputA()
	{
		string tempId;
		cout << "Enter animal id: ";
		cin >> tempId;

		bool idExists = true;

		while (idExists)
		{
			idExists = false;

			ifstream file("AnimalRecords.txt", ios::in);
			string line;

			while (getline(file, line))
			{
				string idFromFile = "";
				int i = 0;

				while (i < line.length() && line[i] != ',')
				{
					idFromFile += line[i];
					i++;
				}

				if (idFromFile == tempId)
				{
					cout << "Enter Different ID (Id already Taken): ";
					cin >> tempId;
					idExists = true;
					break;
				}
			}

			file.close();
		}

		id = tempId;

		do {
			cout << "Enter gender of animal ('m' for male and 'f' for female): ";
			cin >> gender;
		} while (!(gender == 'm' || gender == 'f'));

		cin.ignore();
		cout << "Enter species of animal: ";
		getline(cin, species);

		cout << "Enter Habitat number of animal: ";
		cin >> habitatNo;
		cin.ignore();

		cout << "Enter feeding time of animal: ";
		getline(cin, feedTime);
	}


	void addAnimal() {
		ofstream f;
		inputA();
		f.open("AnimalRecords.txt", ios::app);
		write(id, gender, species, habitatNo, feedTime, f);

	}
	void displayAnimal() {
		ifstream file;
		string line;

		file.open("AnimalRecords.txt", ios::in);
		read(file);

	}
	int updateAnimal() {
		bool checker = true;
		ofstream f;
		ifstream fl, fl2;
		string line1, word, l[500];
		int find, i = 0, j = 0, linecount = 0;
		fl2.open("AnimalRecords.txt", ios::in);
		while (getline(fl2, line1)) {
			linecount++;
		}
		fl2.close();
		if (linecount >= 500) {
			cout << "Sorry cant update file bigger than 500 lines" << endl;
			return 0;
		}

		do {
			if (!checker)
				cout << "ID does not exist enter different id" << endl;
			cout << "Enter animal id you want to update :";
			cin >> find;
			checker = searchA(find);
		} while (!checker);
		cout << "Enter updated animal data" << endl;
		inputA();

		fl.open("AnimalRecords.txt", ios::in);
		while (getline(fl, line1)) {
			l[j] = line1;
			while (line1[i] != ',') {
				word += line1[i];
				i++;
			}
			if (stoi(word) == find) {
				l[j] = id + "," + species + "," + gender + "," + to_string(habitatNo) + "," + feedTime + "\n";
			}
			i = 0;
			word = "";
			j++;
		}
		fl.close();
		f.open("AnimalRecords.txt", ios::out);
		for (i = 0; i < j; i++) {
			f << l[i] << "\n";

		}
		f.close();

		return 0;

	}
	bool searchA(int f) {
		ifstream fl("AnimalRecords.txt");
		string line1;

		while (getline(fl, line1)) {
			string word = "";
			int i = 0;

			while (line1[i] != ',') {
				word += line1[i];
				i++;
			}

			if (stoi(word) == f) {
				fl.close();
				return true;
			}
		}

		fl.close();
		return false;
	}
	void searchById()
	{
		string searchId;
		cout << "Enter ID to search: ";
		cin >> searchId;

		ifstream file("AnimalRecords.txt");
		string line;
		bool found = false;

		while (getline(file, line))
		{
			string tempId = "", tempSpecies = "", tempGender = "", tempHabitatNo = "", tempFeedTime = "";
			int i = 0;

			while (i < line.length() && line[i] != ',')
			{
				tempId += line[i++];
			}
			i++;

			while (i < line.length() && line[i] != ',')
			{
				tempSpecies += line[i++];
			}
			i++;

			if (i < line.length())
			{
				tempGender += line[i++];
			}
			i++;

			while (i < line.length() && line[i] != ',')
			{
				tempHabitatNo += line[i++];
			}
			i++;

			while (i < line.length())
			{
				tempFeedTime += line[i++];
			}

			if (tempId == searchId)
			{
				cout << "\nAnimal Found:\n";
				cout << "ID           :   " << tempId << endl;
				cout << "Species      :   " << tempSpecies << endl;
				cout << "Gender       :   " << tempGender << endl;
				cout << "Cage Number  :   " << tempHabitatNo << endl;
				cout << "Feeding Time :   " << tempFeedTime << endl;
				found = true;
				break;
			}
		}

		if (!found)
		{
			cout << "Animal with ID " << searchId << " not found.\n";
		}

		file.close();
	}

};

class Zookeeper : public RAW {
private:

	string id;
	string name;
	char gender;
	string shift;
	int salary;

public:

	Zookeeper()
	{
		id = "";
		name = "";
		gender = ' ';
		shift = "";
		salary = 0;
	}


	void inputZ()
	{
		string tempId;
		cout << "Enter Zookeeper id: ";
		cin >> tempId;

		bool idExists = true;

		while (idExists)
		{
			idExists = false;

			ifstream file("Zookeeper.txt");
			string line;

			while (getline(file, line))
			{
				string idFromFile = "";
				int i = 0;

				while (i < line.length() && line[i] != ',')
				{
					idFromFile += line[i];
					i++;
				}

				if (idFromFile == tempId)
				{
					cout << "Enter Different ID (Id already Taken): ";
					cin >> tempId;
					idExists = true;
					break;
				}
			}

			file.close();
		}

		id = tempId;

		do {
			cout << "Enter gender of ZooKeeper( 'm'for male and 'f' for female) :";
			cin >> gender;
		} while (!(gender == 'm' || gender == 'f'));

		cout << "Enter Name : ";
		cin.ignore();
		getline(cin, name);


		cout << "Enter Shift :";
		cin >> shift;

		cout << "Enter Salary :";
		cin >> salary;
	}

	void addZookeeper() {
		ofstream f;
		inputZ();
		f.open("ZooKeeper.txt", ios::app);
		write(id, gender, name, salary, shift, f);

	}

	void updateZookeeper() {
		ofstream f;
		ifstream fl;
		string line1, word, l[50];

		int find, i = 0, j = 0;
		cout << "Enter Zookeeper id you want to update :";
		cin >> find;
		cout << "Enter updated Zookeeper data" << endl;
		inputZ();

		fl.open("Zookeeper.txt", ios::in);
		while (getline(fl, line1)) {
			l[j] = line1;
			while (line1[i] != ',') {
				word += line1[i];
				i++;
			}
			if (stoi(word) == find) {
				l[j] = id + "," + gender + "," + name + "," + shift + "," + to_string(salary) + "\n";
			}
			i = 0;
			word = "";
			j++;
		}
		fl.close();
		f.open("Zookeeper.txt", ios::out);
		for (i = 0; i < j; i++) {
			f << l[i] << "\n";

		}
		f.close();



	}

	void displayZookeeper()
	{
		ifstream file;

		file.open("Zookeeper.txt", ios::in);
		read(file);
	}

	void searchZookeeper()
	{
		string searchId;
		cout << "Enter ID to search: ";
		cin >> searchId;

		ifstream file("Zookeeper.txt");
		string line;

		bool found = false;

		while (getline(file, line))
		{
			string tempName = "", tempGender = "", tempAssignedArea = "", tempShift = "", tempSalary = "";
			int i = 0;

			string idFromFile = "";

			while (i < line.length() && line[i] != ',')
			{
				idFromFile += line[i];
				i++;
			}

			if (idFromFile == searchId)
			{
				i++;


				while (i < line.length() && line[i] != ',')
				{
					tempName += line[i];
					i++;
				}

				i++;


				if (i < line.length())
				{
					tempGender = line[i];
					i++;
				}

				i++;


				while (i < line.length() && line[i] != ',')
				{
					tempAssignedArea += line[i];
					i++;
				}

				i++;


				while (i < line.length() && line[i] != ',')
				{
					tempShift += line[i];
					i++;
				}

				i++;

				while (i < line.length())
				{
					tempSalary += line[i];
					i++;
				}





				cout << "\nZookeeper Found:\n";
				cout << "ID             :   " << idFromFile << endl;
				cout << "name           :   " << tempName << endl;
				cout << "Gender         :   " << tempGender << endl;
				cout << "Assigned Area  :   " << tempAssignedArea << endl;
				cout << "Shift          :   " << tempShift << endl;
				cout << "Salary          :   " << tempSalary << endl;


				found = true;
				break;
			}
		}

		if (!found)
		{
			cout << "Zookeeper with ID " << searchId << " not found.\n";
		}

		file.close();
	}
};
bool login() {
	string name, password, l, word;
	ifstream fl2;
	ofstream fl;
	int i;
	bool found1 = false, found2 = false;
	fl.open("login.txt", ios::out);
	fl << "zoo" << endl;
	fl << "1234";
	fl.close();
	cout << "Enter name :";
	getline(cin, name);
	cout << "Enter password :";
	getline(cin, password);
	fl2.open("login.txt", ios::in);
	while (getline(fl2, l)) {
		for (i = 0; i < l.length(); i++) {
			word += l[i];
		}
		if (word == name) {
			found1 = true;
		}
		if (word == password) {
			found2 = true;
		}
		i = 0;
		word = "";
	}
	fl2.close();
	if (found1 && found2) {
		return true;
	}
	else
	{
		return false;
	}
}

class Person{
public:
	virtual void addVisitor() = 0;
	virtual void showRevenue() = 0;
};

class Visitor : public Person
{
private:
	int ticketPrice;

public:
	Visitor() {
		ticketPrice = 50;
	}

	void addVisitor() {
		int members;
		cout << "\nTicket Price is: Rs. " << ticketPrice << endl;
		cout << "How many members do you want to add? ";
		cin >> members;

		int price = members * ticketPrice;

	
		int totalRevenue = 0;

		
		ifstream inFile("revenue.txt");
		
			inFile >> totalRevenue;
			inFile.close();
		

	
		totalRevenue += price;

	
		ofstream outFile("revenue.txt", ios::trunc);
		
			outFile << totalRevenue;
			outFile.close();
	

		cout << "Total Price : " << price << endl;
	}

	void showRevenue() {
		int totalRevenue = 0;
		ifstream inFile("revenue.txt");
		
			inFile >> totalRevenue;
	

		cout << "\nTotal Revenue: Rs. " << totalRevenue << endl;
	}

	void clearRevenue()
	{
		ofstream outFile("revenue.txt", ios::trunc);
		outFile << 0;
		outFile.close();

		cout << "Revenue Cleared from File" << endl;

	}
};


void menu()
{
	cout << "Press 1 for add Animal" << endl;
	cout << "Press 2 for update Animal" << endl;
	cout << "Press 3 for Search Animal (by ID)" << endl;
	cout << "Press 4 for Display Animals" << endl;
	cout << "Press 5 to add zookeeper" << endl;
	cout << "Press 6 to update zookeeper" << endl;
	cout << "Press 7 to Search zookeeper" << endl;
	cout << "Press 8 to Display zookeeper" << endl;
	cout << "Press 9 to Add Visitor" << endl;
	cout << "Press 10 to Display Revenue From Visitors" << endl;
	cout << "Press 11 to Clear Revenue" << endl;
	cout << "Press 0 to exit" << endl;


}
int main() {

	Visitor v;

	bool checker;
	Animal a;
	Zookeeper z;
	int x;
	checker = login();
	if (checker) {
		cout << "Login successful" << endl;
	}
	else {
		cout << "Wrong Id or password" << endl;
		cout << "access denied" << endl;
		return 1;
	}
	while (true)
	{
		menu();
		cout << "Choose Option : ";
		cin >> x;

		if (x == 1)
		{
			a.addAnimal();
		}

		else if (x == 2)
		{
			a.updateAnimal();

		}

		else if (x == 3)
		{
			a.searchById();

		}

		else if (x == 4)
		{
			a.displayAnimal();

		}

		else if (x == 5)
		{
			z.addZookeeper();

		}

		else if (x == 6)
		{
			z.updateZookeeper();

		}

		else if (x == 7)
		{
			z.searchZookeeper();

		}

		else if (x == 8)
		{
			z.displayZookeeper();

		}
		
		else if (x == 9)
		{
			v.addVisitor();

		}

		else if (x == 10)
		{
			v.showRevenue();

		}

		else if (x == 11)
		{
			v.clearRevenue();

		}



		else if (x == 0) {
			break;
		}

	}

	system("pause");
	return 0;

}
