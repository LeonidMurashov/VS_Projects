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
			this->richTextBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &TextDialog::richTextBox1_MouseDown);
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->button1->Location = System::Drawing::Point(0, 257);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(317, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Выбрать";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TextDialog::button1_Click_1);
			// 
			// TextDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 288);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"TextDialog";
			this->Text = L"TextDialog";
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
	};
}
