#include<fstream>
#include <iostream>
#include"HugeInteger.h"
using namespace std;


void Load(HugeInteger*& H, int& Size)
{
	ifstream fin("Ds.txt");
	fin >> Size;
	H = new HugeInteger[Size];
	for (int i = 0; i < Size; i++)
	{
		fin >> H[i];
	}
}

void Printall(HugeInteger* H, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << "Quantity " << i + 1 << " : " << H[i] << endl;
	}
}

void Binary(HugeInteger* H, int size)
{
	char opr{}, dummy{}, cont;
	int rsi{}, loi{}, roi{};

	do
	{
		Printall(H, size);
		cout << endl;
		cout << "Example Format: F2 + F3" << endl;
		cout << "Example Format: F2 - F3" << endl;
		cout << "Example Format: F2 * F3" << endl;
		cout << "Example Format: F2 / F3" << endl;
		cout << "Example Format: F2 % F3" << endl;
		cout << "Example Format: F2 < F3" << endl;
		cout << "Example Format: F2 > F3" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		rsi--; loi--; roi--;

		switch (opr)
		{
		case '+':
			cout << (H[loi] + H[roi]) << endl;
			break;

		case '-':
			cout << (H[loi] - H[roi]) << endl;
			break;

		case '*':
			cout << (H[loi] * H[roi]) << endl;
			break;
		case '/':
			cout << (H[loi] / H[roi]) << endl;
			break;
		case '%':
			cout << (H[loi] & H[roi]) << endl;
			break;
		case '<':
			cout << (H[loi] < H[roi]) << endl;
			break;
		case '>':
			cout << (H[loi] > H[roi]) << endl;
			break;
		}

		cout << endl << endl;
		cout << endl << " Do You Want To Continue?(Y for yes) ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
}

void AccumulateSet(HugeInteger* H, int size)
{

	char opr{}, dummy{}, cont;
	int loi{}, roi{};

	do
	{
		Printall(H, size);
		cout << endl;
		cout << "Example Format: F1 + F2 (for +=)" << endl;
		cout << "Example Format: F1 - F2 (for+-)" << endl;
		cout << "Example Format: F1 * F2 (fast product)" << endl;
		cout << "Example Format: F1 / F2 (fast division)" << endl;
		cout << "Example Format: F1 % F2 (fast mod)" << endl;
		cout << "Example Format: F1 = F2 (for checking quantities)" << endl;
		cout << "Example Format: F1 < F2 (for <=)" << endl;
		cout << "Example Format: F1 > F2 (for >=)" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		loi--; roi--;

		switch (opr)
		{
		case '+':
			cout << (H[loi] += H[roi]) << endl;
			break;

		case '-':
			cout << (H[loi] -= H[roi]) << endl;
			break;
		case '*':
			cout << (H[loi] *= H[roi]) << endl;
			break;
		case '/':
			cout << (H[loi] /= H[roi]) << endl;
			break;
		case '%':
			cout << (H[loi] &= H[roi]) << endl;
			break;
		case '<':
			cout << (H[loi] <= H[roi]) << endl;
			break;
		case '>':
			cout << (H[loi] >= H[roi]) << endl;
			break;
		case '=':
			if (H[loi] == H[roi])
				cout << "Quantities are equal" << endl;
			else
			cout << "Quantities are not equal" << endl;
			break;
		}

		cout << endl << endl;
		cout << endl << " Do You Want To Continue?(Y) ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');

}

int main()
{
	HugeInteger* H{};
	int Size = 0, input;
	Load(H, Size);
	char cont;
	do
	{
		system("cls");
		cout << "Enter task number: " << endl
			<< "1. Multiple Set Operations" << endl
			<< "2. Accumulate Set Operations" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			Binary(H, Size);
			break;

		case 2:
			AccumulateSet(H, Size);
			break;
		}

		cout << "Do you want to continue(Y for yes)";
		cin >> cont;

	} while (cont == 'Y' || cont == 'y');

}