#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 100; // 要生成的记录数量

// 生成随机电话号码（长度不超过11的数字串）
string Phone() {
	string phone = "1"; // 假设电话号码以1开头
	for (int i = 0; i < 10; ++i) {
		phone += to_string(rand() % 10);
	}
	return phone;
}

// 生成随机用户名（长度不超过20个字符的字符串）
string UserName() {
	string name;
	int length = rand() % 20 + 1; // 用户名长度为1到20个字符
	for (int i = 0; i < length; ++i) {
		name += 'a' + rand() % 26;
	}
	return name;
}

// 生成随机地址（长度不超过50个字符的字符串）
string Address() {
	string address;
	int length = rand() % 50 + 1; // 地址长度为1到50个字符
	for (int i = 0; i < length; ++i) {
		address += 'a' + rand() % 26;
	}
	return address;
}

int main() {
	srand(time(0));
	
	ofstream outFile("data.txt");
	if (!outFile) {
		cerr << "Error opening file!" << endl;
		return 1;
	}
	
	for (int i = 0; i < N; ++i) {
		string phone = Phone();
		string name = UserName();
		string address = Address();
		
		outFile << phone << " " << name << " " << address << endl;
	}
	
	outFile.close();
	cout << "Data generated and written to data.txt" << endl;
	
	return 0;
}

