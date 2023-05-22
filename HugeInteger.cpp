#include "HugeInteger.h"
#include<fstream>
using namespace std;

HugeInteger::HugeInteger()
{
	Ds = nullptr;
	size = 0;
	IsNeg = false;
}
HugeInteger::HugeInteger(int i)
{
	Ds = new int[1]{ i };
	size = 1;
	IsNeg = false;
}
HugeInteger::HugeInteger(ifstream& fin)
{
	SetInteger(fin);
}
HugeInteger HugeInteger::UnitInteger()
{
	HugeInteger R;
	R.Ds = new int[1]{ 1 };
	R.size = 1;
	return R;

}
HugeInteger HugeInteger::ZeroInteger() const
{
	HugeInteger R;
	R.Ds = new int[1]{ 0 };
	R.size = 1;
	return R;

}
HugeInteger::HugeInteger(const HugeInteger& H)
{
	DeepCopy(H);
}
HugeInteger& HugeInteger::operator=(const HugeInteger& HI)
{
	if (this == &HI)
		return  (*this);
	DeepCopy(HI);
	return (*this);
}

void HugeInteger::RemoveatEnd()
{
	int* heap = new int[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		heap[i] = Ds[i];
	}
	delete[]Ds;
	Ds = heap;
	size--;
}
void HugeInteger::Trim()
{
	if (size != 1)
	{
		for (int i = size - 1; Ds[i] == 0 && i >= 1; i--)
		{
			this->RemoveatEnd();
		}
	}
}
void HugeInteger::SetInteger(ifstream& fin)
{
	char ch;
	string integer;
	fin >> ch;
	if (ch == '+')
		IsNeg = false;
	else if (ch == '-')
		IsNeg = true;
	fin >> integer;
	size = integer.size();
	Ds = new int[size] {};
	for (int i = 0; i < size; i++)
	{
		Ds[i] = integer[size - 1 - i] - 48;
	}
}
void HugeInteger::DeepCopy(const HugeInteger& H)
{
	size = H.size;
	IsNeg = H.IsNeg;
	Ds = new int[size] {};
	for (int i = 0; i < size; i++)
	{
		Ds[i] = H.Ds[i];
	}
}

ostream& operator << (ostream& console, const HugeInteger& HI)
{
	cout << (HI.IsNeg ? '-' : '+');
	for (int i = 0; i < HI.size; i++)
	{
		cout << HI.Ds[HI.size - 1 - i];
	}
	return console;
}
ifstream& operator>>(ifstream& fin, HugeInteger& HI)
{
	HI.SetInteger(fin);
	HI.Trim();
	return fin;
}


int HugeInteger::operator[](int i)const
{

	return ((i >= size) ? 0 : Ds[i]);
}
int& HugeInteger::operator[](int i)
{
	return Ds[i];
}

bool HugeInteger::GreaterThanQuantityWise(const HugeInteger& HI) const
{
	if (size > HI.size)
		return true;
	else if (size < HI.size)
		return false;

	for (int i = size - 1; i >= 0; i--)
	{
		if ((*this)[i] > HI[i])
			return true;
		else if ((*this)[i] < HI[i])
			return false;
	}
	return false;
}
bool HugeInteger::LessThanQuantityWise(const HugeInteger& HI) const
{
	return (HI.GreaterThanQuantityWise(*this));
}
bool HugeInteger::EqualQuantityWise(const HugeInteger& HI) const
{
	return (!this->GreaterThanQuantityWise(HI) && !this->LessThanQuantityWise(HI));
}
bool HugeInteger::check(const HugeInteger& H)const
{
	if (IsNeg == true && H.IsNeg == true)
		return false;
	else if (IsNeg == false && H.IsNeg == false)
		return false;
	return true;
}

HugeInteger HugeInteger::ADDQuantityWise(const HugeInteger& HI) const
{
	int carry = 0;
	HugeInteger R;
	R.size = size + 1;
	R.Ds = new int[R.size]{};
	for (int i = 0; i < R.size; i++)
	{
		R[i] = ((*this)[i] + HI[i] + carry) % 10;
		carry = ((*this)[i] + HI[i] + carry) / 10;
	}
	R.Trim();
	return R;
}
HugeInteger HugeInteger::SUBQuantityWise(const HugeInteger& HI) const
{
	int carry = 0;
	HugeInteger R;
	R.size = size;
	R.Ds = new int[R.size]{};
	for (int i = 0; i < R.size; i++)
	{
		R.Ds[i] = ((*this)[i] - HI[i] - carry);
		if (R.Ds[i] < 0)
		{
			R.Ds[i] += 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	R.Trim();
	return R;
}


HugeInteger HugeInteger::operator+(const HugeInteger& H) const
{
	HugeInteger R;
	if (IsNeg == H.IsNeg)
	{
		if (this->GreaterThanQuantityWise(H))
			R = this->ADDQuantityWise(H);
		else
			R = H.ADDQuantityWise(*this);
		R.IsNeg = IsNeg;
	}
	else
	{
		if (this->GreaterThanQuantityWise(H))
		{
			R = this->SUBQuantityWise(H);
			R.IsNeg = IsNeg;
		}
		else
		{
			R = H.SUBQuantityWise(*this);
			R.IsNeg = H.IsNeg;
		}

	}

	return R;
}
HugeInteger& HugeInteger::operator++()
{
	*this = *this + UnitInteger();
	return *this;
}
HugeInteger& HugeInteger::operator--()
{
	*this = *this - UnitInteger();
	return *this;
}
HugeInteger HugeInteger::operator-() const
{
	HugeInteger R = *this;
	R.IsNeg = !IsNeg;
	return R;
}
HugeInteger HugeInteger::operator-(const HugeInteger& H)const
{
	HugeInteger R;
	R = *this + (-H);
	if (R != 0)
		return R;
	else
	{
		R.IsNeg =false;
		return R;
	}
}

const HugeInteger HugeInteger::operator--(int i)
{
	HugeInteger temp = *this;
	*this = *this - UnitInteger();
	return temp;
}
const HugeInteger HugeInteger::operator++(int i)
{
	HugeInteger temp = *this;
	*this = *this + UnitInteger();
	return temp;
}

HugeInteger HugeInteger::operator* (const HugeInteger& H) const
{
	HugeInteger R;
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;

	for (HugeInteger I(1); I <= B; I++)
	{
		R = R + (A);
	}

	R.IsNeg = this->check(H);
	return R;
}
HugeInteger HugeInteger::operator/ (const HugeInteger& H) const
{
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;
	HugeInteger I(0);
	if (A >= B && A != 0 && B != 0)
	{
		do
		{
			A = A - (B);
			I++;
		} while (A >= B);
	}

	I.IsNeg = this->check(H);
	return I;
}
HugeInteger HugeInteger::operator& (const HugeInteger& H) const
{
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;
	HugeInteger I(0);
	if (A >= B && A != 0 && B != 0)
	{
		do
		{
			A = A - (B);
			I++;
		} while (A >= B);
	}

	A.IsNeg = this->check(H);
	return A;
}
HugeInteger HugeInteger::operator&= (const HugeInteger& H) const
{
	HugeInteger R = H, Total;
	HugeInteger A = *this, B = H;
	HugeInteger I(1);

	A.IsNeg = false;
	B.IsNeg = false;

	if (B != 0 && A!=0)
	{
		if (*this < H)
		{
			do
			{
				R.IsNeg = false;

				while (R + R <= A)
				{
					R += R;
					I += I;
				}
				A = A - R;
				Total = Total + I;
				I = 1;
				R = H;
			} while (B < A);
		}
	}
	else
	{
		cout << "Undefined" << endl;
		A = 0;
		return A;
	}
	
	A.IsNeg = this->check(H);
	return A;
}
HugeInteger HugeInteger::operator*= (const HugeInteger& H) const
{
	HugeInteger R = *this,B=H,Total,I(1);
	do
	{
		R.IsNeg = false;
		B.IsNeg = false;
		while (I + I <= B)
		{
			R += R;
			I += I;
		}
		Total += R;
		B = B - I;
		R = *this;
		I=1;
	} while (B != 0);

	Total.IsNeg = this->check(H);
	return Total;
}
HugeInteger HugeInteger::operator/= (const HugeInteger& H) const
{

	HugeInteger R = H, Total;
	HugeInteger A = *this, B = H;
	HugeInteger I(1);

	A.IsNeg = false;
	B.IsNeg = false;

	if (A != 0 && B != 0 && A >= B)
	{
		do
		{
			R.IsNeg = false;

			while (R + R <= A)
			{
				R += R;
				I += I;
			}
			A = A - R;
			Total = Total + I;
			I = 1;
			R = H;
		} while (B < A);
	}
	else
		return 0;

	Total.IsNeg = this->check(H);
	return Total;
}
HugeInteger& HugeInteger::operator+=(const HugeInteger& H)
{
	*this = *this + H;
	return *this;
}
HugeInteger& HugeInteger::operator-=(const HugeInteger& H)
{
	*this = *this - H;
	return *this;
}

bool HugeInteger::operator<(const HugeInteger& H)const
{
	if (IsNeg == false && H.IsNeg == true)
	{
		return false;
	}
	else if (IsNeg == true && H.IsNeg == false)
	{
		return true;
	}
	else if (IsNeg == false)
	{
		if (this->GreaterThanQuantityWise(H))
			return false;
		else if (H.GreaterThanQuantityWise(*this))
			return true;
		else
			return false;
	}
	else if (IsNeg == true)
	{
		if (this->GreaterThanQuantityWise(H))
			return true;
		else if (H.GreaterThanQuantityWise(*this))
			return false;
		else
			return true;
	}
}
bool HugeInteger::operator<=(const HugeInteger& H)const
{
	if (*this < H)
		return true;
	else if (H < *this)
		return false;
	else
		return true;

}
bool HugeInteger::operator>(const HugeInteger& H)const
{
	return H < *this;
}
bool HugeInteger::operator>=(const HugeInteger& H)const
{
	return (H <= *this);
}
bool HugeInteger::operator!=(int i) const
{
	return !(size == 1 && Ds[0] == i);
}
bool HugeInteger::operator==(const HugeInteger& H)const
{
	return (!(*this < H) && !(H < *this));
}

HugeInteger::~HugeInteger()
{
	delete[] Ds;
	Ds = nullptr;
}

