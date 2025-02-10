#include<iostream>
using namespace std;
int main() {
	int num=10;
	int*ptr=& num ;
	cout << "Before Modify :" <<endl;
	cout << "num ="<<num << endl;
	cout << "ADRESS :" << ptr << endl;
	cout << "Value :" <<*ptr<< endl;
	*ptr = 50;
	cout << "After Modify :"<<endl;
	cout << "num =" << num << endl;
	cout << "ADRESS :" << ptr << endl;
	cout << "Value :" << *ptr << endl;
	return 0;
}