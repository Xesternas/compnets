#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

string* predmet = new string[4];


struct Student
{
	string Client;
	string Name;
	int val[4];
}A;

int answer;
int pred_size;

int main() {
	string nameR = "REQUEST.bin";
	ofstream f_REQ;
	ifstream f_ANS;
	cout << "Client: " << endl;
	cin >> A.Client;
	string nameA = A.Client + ".bin";
	predmet[0] = "OOP";
	predmet[1] = "Physic";
	predmet[2] = "Math";
	predmet[3] = "DIf";
	while (true)
	{
		cout << "Enter Name: " << endl;
		cin >> A.Name;
		for (int i = 0; i < 4; i++) {
			cout << predmet[i] << " grade: " << endl;
			cin >> A.val[i];
		}

		f_REQ.open(nameR, ios::app | ios::binary);
		f_REQ.write((char*)&A, sizeof(A));
		f_REQ.close();

		cout << "Wait..." << endl;
		f_ANS.open(nameA, ios::binary);
		while (!f_ANS.is_open())
		{
			f_ANS.open(nameA, ios::binary);
		}
		f_ANS.seekg(0, ios::end);
		pred_size = f_ANS.tellg(); 
		while (pred_size >= (int)f_ANS.tellg())
		{
			Sleep(100);
			f_ANS.seekg(0, ios::end);
		}
		
		f_ANS.seekg(pred_size, ios::beg);
		f_ANS.read((char*)&answer, sizeof(answer));
		f_ANS.close();
		cout << answer << endl;
		switch (answer)
		{
		case 30000: cout << "No scholarship" << endl;
			break;
		case 40000: cout << "Scholarship = 1800" << endl;
			break;
		case 50000: cout << "Scholarship = 2500" << endl;
			break;
		default: cout << "No scholarship" << endl;
			if (answer % 10 == 1) cout << "OOP" << endl;
			if (answer % 100 / 10 == 1) cout << "Physic" << endl;
			if (answer % 1000 / 100 == 1) cout << "Math" << endl;
			if (answer % 10000 / 1000 == 1) cout << "Dif" << endl;
			break;
		}
	}

	return 0;
}
