#pragma once

#include "TextDialog.h"
#include <vector>
//#include <cliext/vector>
std::vector<std::vector<bool>> figure;
namespace Juzn {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	//using namespace cliext;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::RadioButton^  Check_Glider;
	private: System::Windows::Forms::RadioButton^  Check_Dot;
	private: System::Windows::Forms::RadioButton^  Check_Rifle;

	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::TextBox^  h_line;
	private: System::Windows::Forms::TextBox^  w_line;

	private: System::Windows::Forms::CheckBox^  checkBox1;

	public:
		MyForm(void)
		{
			InitializeComponent();			
			GenerateRandom();

			//g = pictureBox1->CreateGraphics();
			//g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
			
			//
			//TODO: добавьте код конструктора
			//

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->Check_Glider = (gcnew System::Windows::Forms::RadioButton());
			this->Check_Dot = (gcnew System::Windows::Forms::RadioButton());
			this->Check_Rifle = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->h_line = (gcnew System::Windows::Forms::TextBox());
			this->w_line = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(887, 645);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->Location = System::Drawing::Point(3, 5);
			this->label1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Скорость";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trackBar1
			// 
			this->trackBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->trackBar1->LargeChange = 2;
			this->trackBar1->Location = System::Drawing::Point(80, 5);
			this->trackBar1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->trackBar1->Size = System::Drawing::Size(93, 16);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				44.31818F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.68182F)));
			this->tableLayoutPanel1->Controls->Add(this->trackBar1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button1, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->button2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->button3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->Check_Glider, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->Check_Dot, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->Check_Rifle, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->checkBox1, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->radioButton1, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->h_line, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->w_line, 0, 5);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 6;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 26)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 26)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(176, 161);
			this->tableLayoutPanel1->TabIndex = 3;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::tableLayoutPanel1_Paint);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(80, 29);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 21);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Перезапуск";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(3, 29);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(71, 21);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Пауза";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button3->Location = System::Drawing::Point(3, 56);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(71, 20);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Очистить";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// Check_Glider
			// 
			this->Check_Glider->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Check_Glider->AutoSize = true;
			this->Check_Glider->Location = System::Drawing::Point(80, 82);
			this->Check_Glider->Name = L"Check_Glider";
			this->Check_Glider->Size = System::Drawing::Size(93, 20);
			this->Check_Glider->TabIndex = 6;
			this->Check_Glider->Text = L"Глайдер";
			this->Check_Glider->UseVisualStyleBackColor = true;
			// 
			// Check_Dot
			// 
			this->Check_Dot->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Check_Dot->AutoSize = true;
			this->Check_Dot->Checked = true;
			this->Check_Dot->Location = System::Drawing::Point(3, 82);
			this->Check_Dot->Name = L"Check_Dot";
			this->Check_Dot->Size = System::Drawing::Size(71, 20);
			this->Check_Dot->TabIndex = 7;
			this->Check_Dot->TabStop = true;
			this->Check_Dot->Text = L"Точка";
			this->Check_Dot->UseVisualStyleBackColor = true;
			// 
			// Check_Rifle
			// 
			this->Check_Rifle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Check_Rifle->AutoSize = true;
			this->Check_Rifle->Location = System::Drawing::Point(80, 108);
			this->Check_Rifle->Name = L"Check_Rifle";
			this->Check_Rifle->Size = System::Drawing::Size(93, 21);
			this->Check_Rifle->TabIndex = 8;
			this->Check_Rifle->Text = L"Ружьё";
			this->Check_Rifle->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(80, 56);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(93, 20);
			this->checkBox1->TabIndex = 9;
			this->checkBox1->Text = L"Замкнутость";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(3, 108);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(71, 21);
			this->radioButton1->TabIndex = 10;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Своя";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::radioButton1_MouseClick);
			// 
			// h_line
			// 
			this->h_line->Location = System::Drawing::Point(80, 135);
			this->h_line->Name = L"h_line";
			this->h_line->Size = System::Drawing::Size(93, 20);
			this->h_line->TabIndex = 11;
			this->h_line->Text = L"100";
			// 
			// w_line
			// 
			this->w_line->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->w_line->Location = System::Drawing::Point(3, 135);
			this->w_line->Name = L"w_line";
			this->w_line->Size = System::Drawing::Size(71, 20);
			this->w_line->TabIndex = 12;
			this->w_line->Text = L"100";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(194, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(10, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L" ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(887, 645);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Bitmap^ curr, ^next;
		int w, h, scale = 2;
		int red = Color::Red.ToArgb();

		bool GetPixel(int x, int y)
		{
			if (checkBox1->Checked)
			{
				if (x < 0)
					x = w + x;
				if (x >= w)
					x = x - w;

				if (y < 0)
					y = h + y;
				if (y >= h)
					y = y - h;
			}
			else if (x < 0 || x >= w || y < 0 || y >= h)
				return false;

			return (curr->GetPixel(x*scale, y*scale).ToArgb() == red);
		}

		void SetPixel(int x, int y, bool live)
		{
			if (checkBox1->Checked)
			{
				if (x < 0)
					x = w + x;
				if (x >= w)
					x = x - w;

				if (y < 0)
					y = h + y;
				if (y >= h)
					y = y - h;
			}
			else if (x < 0 || x >= w || y < 0 || y >= h)
				return;

			for (int i = 0; i < scale-1; i++)
				for (int j = 0; j < scale-1; j++)
					next->SetPixel(x*scale + i, y*scale + j, (live) ? Color::Red : Color::White);
		}

		void SetWH()
		{
			w = Convert::ToInt32(w_line->Text);
			h = Convert::ToInt32(h_line->Text);
			scale = (int)std::fmax(std::round((float)200 / (float)std::fmax(w, h)), 2);
		}

		void GenerateRandom()
		{
			SetWH();

			Random ^r = gcnew Random();
			curr = gcnew Bitmap(w*scale, h*scale);
			next = gcnew Bitmap(w*scale, h*scale);

			for (int i = 0; i < w; i++)
				for (int j = 0; j < h; j++)
				SetPixel(i, j, r->NextDouble() < .5f);
			
			Bitmap ^s = curr;
			curr = next;
			next = s;

			pictureBox1->BackgroundImage = curr;
			//pictureBox1->Invalidate();
		}

		bool IsAlive(int x, int y)
		{
			int neighbors = 0;
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					if (Math::Abs(i) + Math::Abs(j) != 0)
						neighbors += (int)GetPixel(x + i, y + j);
			if (GetPixel(x, y))
				return neighbors > 1 && neighbors < 4;
				//return neighbors == 3 || neighbors == 5;
			else
				return neighbors == 3;
		}


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		delete next;
		next = gcnew Bitmap(w*scale, h*scale);


		/*for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			if (curr->GetPixel(i, j).ToArgb() == Color::Red.ToArgb())//Color::Red)
			int a = 5;*/

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				if (IsAlive(i, j))
					SetPixel(i, j, true);
				else
					SetPixel(i, j, false);
			}

		// swap
		Bitmap ^s = curr;
		curr = next;
		next = s;

		pictureBox1->BackgroundImage = curr;
		pictureBox1->Invalidate();

	}
	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
		timer1->Interval = Math::Pow(2, trackBar1->Value);
	} 
private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	GenerateRandom();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (timer1->Enabled)
	{
		button2->Text = "Пуск";
		timer1->Enabled = false;
	}
	else
	{
		button2->Text = "Пауза";
		timer1->Enabled = true;
	}
}

public: Point GetMousePositionWindowsForms()
{
	System::Drawing::Point point = Control::MousePosition;
	return Point(point.X, point.Y);
}
		/*
public static void Copy(Bitmap target, Bitmap source, int x, int y)
{
	Graphics g = Graphics::FromImage(target);
	g.DrawImage(source, x, y);
}*/

private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = (double)(e->Location.X+5) / ((double)pictureBox1->Width / (double)w), y = (double)(e->Location.Y+5) / ((double)pictureBox1->Height / (double)h);
	
	Bitmap ^s = curr;
	curr = next;
	next = s;
	//next = curr->Clone(curr->GetBounds(System::Drawing:), curr->PixelFormat));

	//label2->Text = (!GetPixel(x, y)).ToString();

	if (Check_Dot->Checked)
		SetPixel(x, y, e->Button == System::Windows::Forms::MouseButtons::Left);
	else if (Check_Glider->Checked)
	{
		SetPixel(0 + x, 0 + y, true);
		SetPixel(1 + x, 1 + y, true);
		SetPixel(2 + x, 1 + y, true);
		SetPixel(0 + x, 2 + y, true);
		SetPixel(1 + x, 2 + y, true);
	}
	else if (Check_Rifle->Checked)
	{
		bool b[9][36] = {
			{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
			{1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,},
			{1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
			{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,},
			{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,}, };

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 36; j++)
				SetPixel(x + j, y + i, b[i][j]);
	
	}
	else if (radioButton1->Checked)
	{
		for (int i = 0; i < figure.size(); i++)
			for (int j = 0; j < figure[i].size(); j++)
				SetPixel(x + j, y + i, figure[i][j]);
	}
	Bitmap ^c = curr;
	curr = next;
	next = c;

	pictureBox1->BackgroundImage = curr;
	pictureBox1->Invalidate();
}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

	SetWH();

	Random ^r = gcnew Random();
	curr = gcnew Bitmap(w*scale, h*scale);
	next = gcnew Bitmap(w*scale, h*scale);

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			SetPixel(i, j, false);

	/*int a = w / 2, b = h / 2;
	SetPixel(1 + a, 1 + b, true);
	SetPixel(2 + a, 2 + b, true);
	SetPixel(3 + a, 2 + b, true);
	SetPixel(1 + a, 3 + b, true);
	SetPixel(2 + a, 3 + b, true);*/


	Bitmap ^s = curr;
	curr = next;
	next = s;

	pictureBox1->BackgroundImage = curr;

}
private: System::Void radioButton1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	

	TextDialog^ testDialog = gcnew TextDialog;

	// Show testDialog as a modal dialog and determine if DialogResult = OK.
	
	System::Windows::Forms::DialogResult a = testDialog->ShowDialog(this);
	//if (a == System::Windows::Forms::DialogResult::OK)
	{
		String ^str = testDialog->richTextBox1->Text;
		//label2->Text = s;
		figure.clear();
		figure.push_back(std::vector<bool>());
		int i = 0;
		for (int k = 0; k < str->Length; k++)
		{
			if (str[k] != '\n')
				if (str[k] == 'O' || str[k] == '.')
					figure[i].push_back((str[k] == 'O') ? 1 : 0);
			else
			{
				figure.push_back(std::vector<bool>());
				i++;
			}
		}
	}
		// Read the contents of testDialog's TextBox.
	//	this->txtResult->Text = testDialog->TextBox1->Text;
	
	delete testDialog;
}

	

};
}