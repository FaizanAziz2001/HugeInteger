#pragma once
#include<fstream>
#include<iostream>
using namespace std;

class HugeInteger
{
	int* Ds;
	int size;
	int IsNeg;

public:
	
	HugeInteger UnitInteger();
	HugeInteger ZeroInteger() const;
	HugeInteger();
	HugeInteger(int);
	HugeInteger(ifstream& fin);
	HugeInteger(const HugeInteger& H);
	void RemoveatEnd();
	void Trim();
	void SetInteger(ifstream& fin);
	void DeepCopy(const HugeInteger& H);

	friend ostream& operator << (ostream&, const HugeInteger&);
	friend ifstream& operator>>(ifstream&, HugeInteger&);
	
	int operator[](int)const;
	int& operator[](int);

	HugeInteger& operator=(const HugeInteger& HI);
	HugeInteger ADDQuantityWise(const HugeInteger& HI) const;
	HugeInteger SUBQuantityWise(const HugeInteger& HI) const;
	
	const HugeInteger operator++(int);
	const HugeInteger operator--(int);
	HugeInteger operator+(const HugeInteger& H)const;
	HugeInteger& operator++();
	HugeInteger& operator--();
	HugeInteger operator-(const HugeInteger& H)const;
	HugeInteger operator-() const;
	HugeInteger& operator+=(const HugeInteger& H);
	HugeInteger& operator-=(const HugeInteger& H);
	
	HugeInteger operator* (const HugeInteger& H) const;
	HugeInteger operator*= (const HugeInteger& H) const;
	HugeInteger operator/ (const HugeInteger& H) const;
	HugeInteger operator& (const HugeInteger& H) const;
	HugeInteger operator&= (const HugeInteger& H) const;
	HugeInteger operator/= (const HugeInteger& H) const;

	bool GreaterThanQuantityWise(const HugeInteger& HI) const;
	bool LessThanQuantityWise(const HugeInteger& HI) const;
	bool EqualQuantityWise(const HugeInteger& HI) const;
	bool operator<(const HugeInteger& H)const;
	bool operator<=(const HugeInteger& H)const;
	bool operator>(const HugeInteger& H)const;
	bool operator>=(const HugeInteger& H)const;
	bool operator==(const HugeInteger& H)const;
	bool operator!=(int)const;
	bool check(const HugeInteger& H)const;
	~HugeInteger();
};

