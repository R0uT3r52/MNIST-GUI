#pragma once
#include <cmath>
#include <fstream>
#include <vector>
namespace Network {
//		+----------------------+
//		| SOME FUNCS OVER HERE |
//		+----------------------+
	double sigmoid(double x);
	double Softmax();
	int Predicted_Ans(double max);
	void init();
	void FeedForward();
	int Read_Weights();
	void Read_Image(double* arr);
}