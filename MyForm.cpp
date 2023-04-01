#include "MyForm.h"
#include "Network.h"
#include <Windows.h>
#include <fstream>
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Network;
[STAThreadAttribute]


int BMP2TXT(double* arr) {
	std::fstream file;
	file.open("Data\\image.txt", std::fstream::out);
	for (int i = 0; i < 784; i++) {
		if (i % 28 == 0 && i != 0) {
			file << "\n";
		}
		file << arr[i] / 128 << " ";
	}
	file.close();
	return 0;
}

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project1::MyForm form;
	Application::Run(% form);

}

//	+---------------------+
//	| SOME WINFORMS TRASH |
//	+---------------------+
System::Void Project1::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	button1->Text = "Î÷èñòèòü";
	label1->Text = ""; label2->Text = "";
	int f;
	init();
	f = Read_Weights();
	if (f == 0) {
		label2->Text = "Weights Loaded";
	}
	else {
		MessageBox::Show("There is some problem with your weights2.txt file. Check its location, it must be in 'Data/weights2.txt'", "File not found");
		Application::Exit();
	}
	
	Draw = false;
	Bitmap^ Img = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
	canvas = Graphics::FromImage(Img);
	pictureBox1->Image = Img;
}
System::Void Project1::MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (Draw) {
		canvas->FillEllipse(Brushes::Green, e->X, e->Y, 22, 22);
		pictureBox1->Invalidate();
	}
}
System::Void Project1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	//clear button
	canvas->Clear(SystemColors::MenuText);
	label1->Text = "";
	label2->Text = "";
	GC::Collect();
	pictureBox1->Invalidate();
}
System::Void Project1::MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Draw = true;
	pictureBox1->Invalidate();
}
System::Void Project1::MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Draw = false;
	pictureBox1->Invalidate();
}
System::Void Project1::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Bitmap^ img = gcnew Bitmap(pictureBox1->Image, 28, 28);
	Color pixelcolor;
	double predicted;
	int num, k = -1;

	double* arr = new double[784];
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			pixelcolor = img->GetPixel(j, i);
			k += 1;
			arr[k] = Convert::ToDouble(pixelcolor.G);
		}
	}
	Read_Image(arr);
	FeedForward();
	predicted = Softmax();
	num = Predicted_Ans(predicted);
	label1->Text = Convert::ToString(num);
}
System::Void Project1::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	Bitmap^ img = gcnew Bitmap(pictureBox1->Image, 28, 28);
	Color pixelcolor;
	int k = -1;
	double* arr = new double[784];
	label2->Text = "Image written to image.txt";
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			k += 1;
			pixelcolor = img->GetPixel(j, i);
			arr[k] = Convert::ToDouble(pixelcolor.G);
		}
	}
	int r = BMP2TXT(arr);
}
