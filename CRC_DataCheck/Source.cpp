#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int> parseInt(string a) {
	vector<int> result(a.length(), 0);
	for (int i = 0; i < a.length(); i++)
		result[i] = a[i] == '0' ? 0 : 1;
	return result;

}
vector<int> add(vector<int> a, vector<int> b, int c=0) {
	vector<int> sum(a.size(), 0);
	while (b.size() != a.size())
		b.insert(b.begin(), 0);

	for (int i = sum.size() - 1; i >= 0; i--) {
		sum[i] = ((a[i] ^ b[i]) ^ c); // c is carry
		c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
	}

	return sum;
}


// Divides and return the remainder
vector<int> divide(vector<int> data, vector<int> crc) {
	// Adding 0 to data
	vector<int> result = data;
	for (int i = 0; i < crc.size() - 1; i++)
		result.push_back(0);

	for (int i = 0; i <= result.size() - crc.size();) {
		// Using XOR for dividing
		for (int j = 0; j < crc.size(); j++)
			result[i + j] = result[i + j] ^ crc[j];

		// Move i to the next 0 for division again

		while (result[i] != 1) {
			i++;
			if (i == result.size())
				break;
		}
	}
	
	return vector<int>(result.end() - crc.size() + 1, result.end());
}

int main() {
	string temp;
	
	cout << "=======\nSender\n=======\n";
	cout << "Enter the CRC Code: ";
	cin >> temp;
	vector<int> crc = parseInt(temp);

	cout << "Enter the data: ";
	cin >> temp;
	vector<int> data = parseInt(temp);

	vector<int> rem = divide(data, crc);
	cout << "Remainder is: ";
	for (auto i : rem)
		cout << i;

	cout << "\nMessage to be transmitted: ";
	vector<int> trans = data;
	trans.insert(trans.end(), rem.begin(), rem.end());
	for (auto i : trans)
		cout << i;


	cout << "\n\n\n=========\nReciever\n=========\n";
	cout << "\nTransmitted data is: ";
	for (auto i : trans)
		cout << i;

	cout << "\nCRC is: ";
	for (auto i : crc)
		cout << i;

	cout << "\nDividing...";
	rem = divide(trans, crc);

	bool valid = true;
	cout << "\nRemainder is: ";
	for (auto i : rem){
		cout << i;
		if (i != 0)
			valid = false;
	}

	cout << endl;
	if (valid)
		cout << "\nData is correct!";
	else
		cout << "\nData is faulty!";


	cout << endl;
	system("PAUSE");
	return 0;
}