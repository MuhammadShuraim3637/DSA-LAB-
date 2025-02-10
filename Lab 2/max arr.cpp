#include<iostream>
using namespace std;
int find_max_value(int arr[],int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
int main() {
	int n;
	cout << "ENTER THE SIZE OF ARRAY :" << endl;
	cin >> n;
	int* arr = new int[n];
	cout << "Enter "<< n << " Elements" << endl;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << "Maximum value in the array: " << find_max_value(arr, n) << endl;
	delete[] arr;
	return 0;
}
