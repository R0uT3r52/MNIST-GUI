#include "Network.h"
double** w1 = new double* [784]; double** w2 = new double* [256]; // inputs - layer1
double* inputs = new double[784]; double* l2 = new double[256];   // l2 - layer2
double* l3 = new double[10]; // l3 - layer3
double* theta2; double* theta3; // try LR = 0.01
double** delta1 = new double* [784]; double** delta2 = new double* [256];
double outputs[10];

double Network::sigmoid(double x) {
	return 1 / (1 + exp(-x));
}
double Network::Softmax() {
	double exps[10];
	double sum_of_exp = 0;
	for (int i = 0; i < 10; i++) {
		exps[i] = exp(l3[i]);
		sum_of_exp += exps[i];
	}
	for (int i = 0; i < 10; i++) {
		outputs[i] = exps[i] / sum_of_exp;
	}
	double max = outputs[0];
	for (int j = 0; j < 10; j++) {
		if (outputs[j] > max) {
			max = outputs[j];
		}
	}
	return max;
}
int Network::Predicted_Ans(double max) {
	for (int i = 0; i < 10; i++) {
		if (max == outputs[i]) {
			return i;
		}
	}
}
void Network::init() {

	for (int i = 0; i < 784; i++) {
		w1[i] = new double[256];
		delta1[i] = new double[256];
	}
	for (int i = 0; i < 256; i++) {
		w2[i] = new double[10];
		delta2[i] = new double[10];
		l2[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		l3[i] = 0;
	}
	theta2 = new double[256];
	theta3 = new double[10];
}
void Network::FeedForward() {
	for (int i = 0; i < 256; i++) {
		l2[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		l3[i] = 0;
	}

	for (int i = 0; i < 784; i++) {
		for (int j = 0; j < 256; j++) {
			l2[j] += w1[i][j] * inputs[i];
		}
	}
	//	+---------------------+
	//	| ACTIVATE L2 NEURONS |
	//	+---------------------+
	for (int i = 0; i < 256; i++) {
		l2[i] = sigmoid(l2[i]);
	}

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 10; j++) {
			l3[j] += w2[i][j] * l2[i];
		}
	}
	//	+---------------------+
	//	| ACTIVATE L3 NEURONS |
	//	+---------------------+
	for (int i = 0; i < 10; i++) {
		l3[i] = sigmoid(l3[i]);
	}
}
int Network::Read_Weights() {
	std::fstream fin;
	fin.open("Data\\weights2.txt");
	if (fin.is_open()) {
		for (int i = 0; i < 784; i++) {
			for (int j = 0; j < 256; j++) {
				fin >> w1[i][j];
			}
		}
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 10; j++) {
				fin >> w2[i][j];
			}
		}
		fin.close();
		return 0;
	}
	else {
		return 1;
	}
}
void Network::Read_Image(double* arr) {
	for (int i = 0; i < 784; i++) {
		inputs[i] = arr[i] / 128;
	}
}