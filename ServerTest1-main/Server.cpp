#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#include <string>

struct Student
{
	string Client;
	string Name;
	int val[4];
}B;

int size_pred;
int answer;

int main() {
	ifstream fR;
	ofstream fA;
	string nameR = "REQUEST.bin";
	cout << "server is working" << endl;

	while (true)
	{

		fR.open(nameR, ios::binary);
		while (!fR.is_open())
		{
			fR.open(nameR, ios::binary);
		}
		fR.seekg(0, ios::end);
		while (size_pred >= (int)fR.tellg()) {
			Sleep(100);
			fR.seekg(0, ios::end);
		}
		fR.seekg(size_pred, ios::beg);
		fR.read((char*)&B, sizeof(B));
		size_pred = fR.tellg();
		fR.close();
		cout << "New data from " + B.Client << endl;

		answer = 60000;
		for (int i = 0; i < 4; i++)
		{
			switch (B.val[i])
			{
			case 5: if (answer >= 50000) answer = 50000;

				break;
			case 4: if (answer >= 40000) answer = 40000;

				break;
			case 3: if (answer >= 30000) answer = 30000;

				break;
			case 2: if (answer > 22000) answer = 20000;
				if (answer >= 20000)
					answer = answer + pow(10, i);
				break;
			}
		}
		fA.open(B.Client + ".bin", ios::binary | ios::app);
		fA.write((char*)&answer, sizeof(answer));
		fA.close();
	}
	return 0;
}
