/*

 Copyright (C) 2009 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#pragma once
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

namespace ExampleXll {



	/// <summary>
	/// Summary for Password
	/// </summary>
	public ref class Password : public System::Windows::Forms::Form
	{
	public:
		Password(void)
		{
			InitializeComponent();
		}

		String^ getUserName()
		{
			return this->username->Text;
		}
		
	    String^ getPassWord()
		{
			return this->pw->Text;
		}
		System::Windows::Forms::DialogResult DialogResult;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Password()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  username;
	private: System::Windows::Forms::TextBox^  pw;
	private: System::Windows::Forms::Button^  ok;
	private: System::Windows::Forms::Button^  cancel;

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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->username = (gcnew System::Windows::Forms::TextBox());
			this->pw = (gcnew System::Windows::Forms::TextBox());
			this->ok = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(150, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(295, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"XLL is Password Protected";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(70, 74);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"User Name";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(81, 113);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Password";
			// 
			// username
			// 
			this->username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->username->Location = System::Drawing::Point(188, 71);
			this->username->MaxLength = 10;
			this->username->Name = L"username";
			this->username->Size = System::Drawing::Size(257, 26);
			this->username->TabIndex = 3;
			// 
			// pw
			// 
			this->pw->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->pw->Location = System::Drawing::Point(188, 113);
			this->pw->MaxLength = 10;
			this->pw->Name = L"pw";
			this->pw->Size = System::Drawing::Size(257, 26);
			this->pw->TabIndex = 4;
			this->pw->UseSystemPasswordChar = true;
			// 
			// ok
			// 
			this->ok->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->ok->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ok->Location = System::Drawing::Point(146, 157);
			this->ok->Name = L"ok";
			this->ok->Size = System::Drawing::Size(108, 49);
			this->ok->TabIndex = 5;
			this->ok->Text = L"OK";
			this->ok->UseVisualStyleBackColor = true;
			this->ok->Click += gcnew System::EventHandler(this, &Password::ok_Click);
			// 
			// cancel
			// 
			this->cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancel->Location = System::Drawing::Point(367, 157);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(108, 49);
			this->cancel->TabIndex = 6;
			this->cancel->Text = L"Cancel";
			this->cancel->UseVisualStyleBackColor = true;
			this->cancel->Click += gcnew System::EventHandler(this, &Password::cancel_Click);
			// 
			// Password
			// 
			this->AcceptButton = this->ok;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancel;
			this->ClientSize = System::Drawing::Size(574, 231);
			this->ControlBox = false;
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->ok);
			this->Controls->Add(this->pw);
			this->Controls->Add(this->username);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Password";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DEMONSTRATION ONLY. NO CLAIMS ABOUT SUITABILITY OF THIS EXAMPLE PROJECT ARE MADE";
			this->TopMost = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
#pragma endregion
	private: System::Void cancel_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult =  System::Windows::Forms::DialogResult::Cancel;
			 }
	private: System::Void ok_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult =  System::Windows::Forms::DialogResult::OK;
			 }

	};
}
