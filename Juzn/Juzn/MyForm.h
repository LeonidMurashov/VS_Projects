#pragma once

namespace Juzn {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button1;
			 Graphics ^ g;
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
	protected:







	protected:

	protected:
	protected:
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
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(619, 511);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Left;
			this->label1->Location = System::Drawing::Point(3, 5);
			this->label1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 21);
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
			this->trackBar1->Location = System::Drawing::Point(66, 5);
			this->trackBar1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->trackBar1->Size = System::Drawing::Size(107, 21);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.79546F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64.20454F)));
			this->tableLayoutPanel1->Controls->Add(this->trackBar1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button1, 1, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(176, 61);
			this->tableLayoutPanel1->TabIndex = 3;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::tableLayoutPanel1_Paint);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(66, 34);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 24);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Перезапуск";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(619, 511);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		Bitmap^ curr, ^next;
		int w = 100, h = 100, scale = 2;

		bool GetPixel(int x, int y)
		{
			if (x < 0)
				x = w + x;
			if (x >= w)
				x = x - w;

			if (y < 0)
				y = h + y;
			if (y >= h)
				y = y - h;

			return (curr->GetPixel(x*scale, y*scale).ToArgb() == Color::Red.ToArgb());
		}

		void SetPixel(int x, int y, bool live)
		{
			if (x < 0)
				x = w + x;
			if (x >= w)
				x = x - w;

			if (y < 0)
				y = h + y;
			if (y >= h)
				y = y - h;

			for (int i = 0; i < scale-1; i++)
				for (int j = 0; j < scale-1; j++)
					next->SetPixel(x*scale + i, y*scale + j, (live) ? Color::Red : Color::White);
		}

		void GenerateRandom()
		{
			Random ^r = gcnew Random();
			curr = gcnew Bitmap(w*scale, h*scale);
			next = gcnew Bitmap(w*scale, h*scale);

			for (int i = 0; i < w; i++)
				for (int j = 0; j < h; j++)
				SetPixel(i, j, r->NextDouble() < .3f);
			
			/*for (int i = 0; i < w; i++)
				for (int j = 0; j < h; j++)
					SetPixel(i, j, false);

			SetPixel(1 + 5, 1 + 5, true);
			SetPixel(2 + 5, 2 + 5, true);
			SetPixel(3 + 5, 2 + 5, true);
			SetPixel(1 + 5, 3 + 5, true);
			SetPixel(2 + 5, 3 + 5, true);*/


			Bitmap ^s = curr;
			curr = next;
			next = s;

			pictureBox1->BackgroundImage = curr;
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
};
}