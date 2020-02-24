#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <leptonica/allheaders.h>
#include <msclr\marshal_cppstd.h>

namespace OCRBinarizationUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pct;

	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::OpenFileDialog^ file1;

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pct = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->file1 = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pct))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Sauvola";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(652, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"label2";
			// 
			// pct
			// 
			this->pct->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pct->Location = System::Drawing::Point(655, 41);
			this->pct->Name = L"pct";
			this->pct->Size = System::Drawing::Size(635, 444);
			this->pct->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pct->TabIndex = 2;
			this->pct->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox2->Location = System::Drawing::Point(12, 41);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(635, 444);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(445, 491);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(413, 26);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Upload image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// file1
			// 
			this->file1->FileName = L"file1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1302, 529);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pct);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pct))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		Pix* mat8ToPix(cv::Mat* mat8)
		{
			Pix* pixd = pixCreate(mat8->size().width, mat8->size().height, 8);
			for (int y = 0; y < mat8->rows; y++) {
				for (int x = 0; x < mat8->cols; x++) {
					pixSetPixel(pixd, x, y, (l_uint32)mat8->at<uchar>(y, x));
				}
			}
			return pixd;
		}

		cv::Mat pix8ToMat(Pix* pix8)
		{
			cv::Mat mat(cv::Size(pix8->w, pix8->h), CV_8UC1);
			uint32_t* line = pix8->data;
			for (uint32_t y = 0; y < pix8->h; ++y) {
				for (uint32_t x = 0; x < pix8->w; ++x) {
					mat.at<uchar>(y, x) = GET_DATA_BYTE(line, x);
				}
				line += pix8->wpl;
			}
			return mat;
		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->file1->Filter = "(*.jpg)|*.jpg";
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ fname;// объ€вление строковой переменной
		file1->ShowDialog();//открываем диалоговое окно
		fname = file1->FileName;//используем переменную дл€ хранени€ имени выбранного файла
		
		cv::Mat img;
		img = imread(msclr::interop::marshal_as<std::string>(fname), cv::IMREAD_COLOR);

		Pix* pixOrg = mat8ToPix(&img);
		Pix* pixb;

		pixSauvolaBinarizeTiled(pixOrg, 8, 0.34, 1, 1, NULL, &pixb);

		img = pix8ToMat(pixb);
		cv::imshow("", img);
		System::Drawing::Graphics^ graphics = pct->CreateGraphics();
		System::IntPtr ptr(img.ptr());
		System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(img.cols, img.rows, img.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
		System::Drawing::RectangleF rect(0, 0, pct->Width, pct->Height);
		graphics->DrawImage(b, rect);

		pixDestroy(&pixOrg);
		pixDestroy(&pixb);
		
		//pct->Image = pix8ToMat(pixb);//загружаем файл в элемент PictureBox
	}
};

}
