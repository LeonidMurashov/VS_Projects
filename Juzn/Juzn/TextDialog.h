#pragma once

namespace Juzn {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TextDialog
	/// </summary>
	public ref class TextDialog : public System::Windows::Forms::Form
	{
	public:
		TextDialog(void)
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
		~TextDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Button^  horiz_button;
	private: System::Windows::Forms::Button^  vert_button;


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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->horiz_button = (gcnew System::Windows::Forms::Button());
			this->vert_button = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(0, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(317, 288);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &TextDialog::richTextBox1_TextChanged);
			this->richTextBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &TextDialog::richTextBox1_MouseDown);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(217, 29);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Выбрать";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TextDialog::button1_Click_1);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				81.99234F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.00766F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				45)));
			this->tableLayoutPanel1->Controls->Add(this->button1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->horiz_button, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->vert_button, 2, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 253);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(317, 35);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// horiz_button
			// 
			this->horiz_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->horiz_button->Location = System::Drawing::Point(226, 3);
			this->horiz_button->Name = L"horiz_button";
			this->horiz_button->Size = System::Drawing::Size(42, 29);
			this->horiz_button->TabIndex = 2;
			this->horiz_button->Text = L">";
			this->horiz_button->UseVisualStyleBackColor = true;
			this->horiz_button->Click += gcnew System::EventHandler(this, &TextDialog::horiz_button_Click);
			// 
			// vert_button
			// 
			this->vert_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->vert_button->Location = System::Drawing::Point(274, 3);
			this->vert_button->Name = L"vert_button";
			this->vert_button->Size = System::Drawing::Size(40, 29);
			this->vert_button->TabIndex = 3;
			this->vert_button->Text = L"^";
			this->vert_button->UseVisualStyleBackColor = true;
			this->vert_button->Click += gcnew System::EventHandler(this, &TextDialog::vert_button_Click);
			// 
			// TextDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 288);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"TextDialog";
			this->Text = L"Вставьте свою структуру";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void richTextBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (Clipboard::ContainsText() && e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			richTextBox1->Text = Clipboard::GetText();			
		}

	}
	private: System::Void horiz_button_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		auto lines = richTextBox1->Text->Split('\n');
		richTextBox1->Clear();
		for (int i = 0; i < lines->Length; i++)
		{
			array<wchar_t>^ ar_ch = lines[i]->Trim()->ToCharArray();
			ar_ch->Reverse(ar_ch);
			lines[i] = gcnew String(ar_ch);

			richTextBox1->AppendText(lines[i]);
			richTextBox1->AppendText("\n");
		}
		richTextBox1->Text = richTextBox1->Text->Trim();
	}
	private: System::Void vert_button_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		auto lines = richTextBox1->Text->Split('\n');
		Array::Reverse(lines);
		richTextBox1->Clear();
		for (int i = 0; i < lines->Length; i++)
		{
			richTextBox1->AppendText(lines[i]->Trim());
			richTextBox1->AppendText("\n");
		}
		richTextBox1->Text = richTextBox1->Text->Trim();
	}
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	String ^str = richTextBox1->Text;
	if (str->Contains("$") && str->Contains("b") && str->Contains("o"))
	{
		vert_button->Visible = false;
		horiz_button->Visible = false;
	}
	else
	{
		vert_button->Visible = true;
		horiz_button->Visible = true;
	}
}
};
}
