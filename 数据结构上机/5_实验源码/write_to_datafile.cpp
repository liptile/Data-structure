/*
  先编译执行write_to_datafile.cpp 生成整数随机序列
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int main() {
	// 随机数生成器和分布设置
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis_rows(1, 200); // 行数范围 1-200
	uniform_int_distribution<> dis_cols(1, 100);  // 列数范围 1-100
	uniform_int_distribution<> dis_values(0, 1000); // 整数值范围 0-1000
	
	// 生成随机行数和列数
	int rows = dis_rows(gen);
	int cols = dis_cols(gen);
	
	// 生成随机整数矩阵
	vector<vector<int>> matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			matrix[i][j] = dis_values(gen);
		}
		// 对每一行进行排序
		sort(matrix[i].begin(), matrix[i].end());
	}
	
	// 将矩阵写入文件
	ofstream outfile("datafile.txt");
	
	// 写入矩阵数据
	for (const auto& row : matrix) {
		for (const auto& value : row) {
			outfile << value << " ";
		}
		outfile << endl;
	}
	
	outfile.close();
	cout << "Write successfully" << endl;
	return 0;
}

