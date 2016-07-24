#pragma once
#include <stdio.h>
#include <iostream>
#include "DataAnalisys\DataAnalisys.h"
#include "Reader\reader.h"
#include "OpenGl\OpenGl.h"
#include <locale.h>
#include <string.h>
using namespace std;
using namespace System;
namespace DebugDataAnalisys {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Interfaz
	/// </summary>
	public ref class Interfaz : public System::Windows::Forms::Form
	{
	public:
		Interfaz(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			Puntos = gcnew List<Punto3D^>();
			setlocale(LC_NUMERIC, "es_ES");
			Conclusiones = gcnew List<double>(2);
			Conclusiones->Add(0);
			Conclusiones->Add(0);
			ArrayDataAnalisys = gcnew cli::array<Object^>(SIZE_ARRAY_ANALISYS);
			ArrayDataReader = gcnew cli::array<Object^>(SIZE_ARRAY_READER);
			Obstaculos = gcnew List<Obstaculo^>();
			Flags = gcnew cli::array<bool>(SIZE_ARRAY_FLAGS);
			Dibujador = gcnew OpenGl(Threads);
			Analisys = gcnew DataAnalisys(Puntos, Obstaculos, ArrayDataAnalisys, Conclusiones, Flags, Threads, Dibujador);
			/*-------------------------------------------------------------------------------------------*/
			/*-----------------------------------Fin parametros------------------------------------------*/
			/*-------------------------------------------------------------------------------------------*/
#pragma endregion
#pragma region Ajuste
			/*-------------------------------------------------------------------------------------------*/
			/*----------------------------------Ajuste de parametros-------------------------------------*/
			/*-------------------------------------------------------------------------------------------*/
#pragma region Flags
			Flags[FLAG_TRATAMIENTO] = false;
			Flags[FLAG_LOG] = false;
			Flags[FLAG_WARNING] = false;
			Flags[FLAG_PAUSA] = false;
			Flags[FLAG_ANALISYS] = true;
			Flags[FLAG_OPENGL] = true;
			Flags[FLAG_LOCK] = false;
			Flags[FLAG_ANALIZAR] = false;
#pragma endregion
#pragma region ArrayDataAnalisys
			ArrayDataAnalisys[HORIZONTAL_RESOLUTION] = ((2 * 20 * 0.000002304 * 180) * 16) + (2 * 20 * 0.00001843 * 180);
			ArrayDataAnalisys[VERTICAL_RESOLUTION] = 2;
			ArrayDataAnalisys[OPENING] = 180;
			ArrayDataAnalisys[CAR_VELOCITY] = 10;
			ArrayDataAnalisys[INFORME_ANALISYS] = "";
			ArrayDataAnalisys[FRECUENCIA] = 20;
#pragma endregion
#pragma region ArrayDataReader
			ArrayDataReader[INFORME] = "";
			ArrayDataReader[Hz] = 10;

#pragma endregion
			/*-------------------------------------------------------------------------------------------*/
			/*---------------------------------------Fin de ajuste---------------------------------------*/
			/*-------------------------------------------------------------------------------------------*/
#pragma endregion

#pragma region Lectura
			/*-------------------------------------------------------------------------------------------*/
			/*----------------------------------Lectura de fichero-------------------------------------*/
			/*-------------------------------------------------------------------------------------------*/



			/*-------------------------------------------------------------------------------------------*/
			/*--------------------------------------Fin de lectura---------------------------------------*/
			/*-------------------------------------------------------------------------------------------*/
#pragma endregion

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Interfaz()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  ConsolaReader;
	private: System::Windows::Forms::TextBox^  ConsolaAnalisys;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TextBox^  Consola;
	private: System::Windows::Forms::TextBox^  Hercios;


	private: System::Windows::Forms::Button^  Cargar;
	private: System::Windows::Forms::TextBox^  Frame;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::CheckBox^  lock;
	private: System::Windows::Forms::TextBox^  numlock;








	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->ConsolaReader = (gcnew System::Windows::Forms::TextBox());
			this->ConsolaAnalisys = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Consola = (gcnew System::Windows::Forms::TextBox());
			this->Hercios = (gcnew System::Windows::Forms::TextBox());
			this->Cargar = (gcnew System::Windows::Forms::Button());
			this->Frame = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->lock = (gcnew System::Windows::Forms::CheckBox());
			this->numlock = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 53);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Activar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Interfaz::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Interfaz::openFileDialog1_FileOk);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(13, 14);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Archivo";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Interfaz::button2_Click);
			// 
			// ConsolaReader
			// 
			this->ConsolaReader->Location = System::Drawing::Point(189, 14);
			this->ConsolaReader->Multiline = true;
			this->ConsolaReader->Name = L"ConsolaReader";
			this->ConsolaReader->Size = System::Drawing::Size(862, 138);
			this->ConsolaReader->TabIndex = 2;
			// 
			// ConsolaAnalisys
			// 
			this->ConsolaAnalisys->Location = System::Drawing::Point(189, 169);
			this->ConsolaAnalisys->Multiline = true;
			this->ConsolaAnalisys->Name = L"ConsolaAnalisys";
			this->ConsolaAnalisys->Size = System::Drawing::Size(862, 138);
			this->ConsolaAnalisys->TabIndex = 3;
			// 
			// checkBox1
			// 
			this->checkBox1->Appearance = System::Windows::Forms::Appearance::Button;
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(13, 98);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(47, 23);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"Pausa";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Interfaz::checkBox1_CheckedChanged);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Interfaz::timer1_Tick);
			// 
			// Consola
			// 
			this->Consola->Location = System::Drawing::Point(189, 330);
			this->Consola->Multiline = true;
			this->Consola->Name = L"Consola";
			this->Consola->Size = System::Drawing::Size(862, 138);
			this->Consola->TabIndex = 5;
			// 
			// Hercios
			// 
			this->Hercios->Location = System::Drawing::Point(13, 132);
			this->Hercios->Name = L"Hercios";
			this->Hercios->Size = System::Drawing::Size(33, 20);
			this->Hercios->TabIndex = 6;
			this->Hercios->Text = L"10";
			// 
			// Cargar
			// 
			this->Cargar->Location = System::Drawing::Point(52, 132);
			this->Cargar->Name = L"Cargar";
			this->Cargar->Size = System::Drawing::Size(85, 20);
			this->Cargar->TabIndex = 7;
			this->Cargar->Text = L"Sel velocidad";
			this->Cargar->UseVisualStyleBackColor = true;
			this->Cargar->Click += gcnew System::EventHandler(this, &Interfaz::Cargar_Click);
			// 
			// Frame
			// 
			this->Frame->Location = System::Drawing::Point(94, 169);
			this->Frame->Name = L"Frame";
			this->Frame->Size = System::Drawing::Size(33, 20);
			this->Frame->TabIndex = 8;
			this->Frame->Text = L"0";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 169);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Analizar";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Interfaz::button3_Click);
			// 
			// lock
			// 
			this->lock->Appearance = System::Windows::Forms::Appearance::Button;
			this->lock->AutoSize = true;
			this->lock->Checked = true;
			this->lock->CheckState = System::Windows::Forms::CheckState::Checked;
			this->lock->Location = System::Drawing::Point(13, 210);
			this->lock->Name = L"lock";
			this->lock->Size = System::Drawing::Size(37, 23);
			this->lock->TabIndex = 12;
			this->lock->Text = L"lock";
			this->lock->UseVisualStyleBackColor = true;
			this->lock->CheckedChanged += gcnew System::EventHandler(this, &Interfaz::lock_CheckedChanged);
			// 
			// numlock
			// 
			this->numlock->Location = System::Drawing::Point(80, 210);
			this->numlock->Name = L"numlock";
			this->numlock->Size = System::Drawing::Size(33, 20);
			this->numlock->TabIndex = 13;
			this->numlock->Text = L"30";
			// 
			// Interfaz
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1123, 480);
			this->Controls->Add(this->numlock);
			this->Controls->Add(this->lock);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->Frame);
			this->Controls->Add(this->Cargar);
			this->Controls->Add(this->Hercios);
			this->Controls->Add(this->Consola);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->ConsolaAnalisys);
			this->Controls->Add(this->ConsolaReader);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Interfaz";
			this->Text = L"Interfaz";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Interfaz::Interfaz_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		/*-------------------------------------------------------------------------------------------*/
		/*---------------------------Parametros necesarios-------------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/
		cli::array<Thread^>^ Threads = gcnew cli::array<Thread^>(NUMERO_THREADS);
		//Lista de puntos
		List<Punto3D^>^ Puntos;

		//Lista de obstaculos
		List<Obstaculo^>^ Obstaculos;

		//Parametros de Analisys
		cli::array<Object^>^ ArrayDataAnalisys;
		cli::array<Object^>^ ArrayDataReader;

		//Flags
		cli::array<bool>^ Flags;

		//Conclusiones
		List<double>^ Conclusiones;

		String^ informe;
		String ^ entrada;
		String^ path;
		StreamReader^ sr;
		String^ interno;
		OpenGl^ Dibujador;
		DataAnalisys^ Analisys;
		DataReader^ Reader;

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (Threads[THREAD_READER])
			Threads[THREAD_READER]->Abort();
		Reader = gcnew DataReader(Puntos, ArrayDataReader, interno, Flags, Threads, Dibujador);
		Consola->AppendText("Reader arrancado\r\n");
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		interno = openFileDialog1->FileName;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
		Consola->AppendText("Fichero seleccionado:  " + interno + "\r\n");
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (checkBox1->Checked) {
			checkBox1->Text = "Pausa";
			Flags[FLAG_PAUSA] = false;
			Consola->AppendText("Flags[FLAG_PAUSA]->" + Flags[FLAG_PAUSA] + "\r\n");
		}
		else {
			checkBox1->Text = "Play";
			Flags[FLAG_PAUSA] = true;
			Consola->AppendText("Flags[FLAG_PAUSA]->" + Flags[FLAG_PAUSA] + "\r\n");
		}
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (!Flags[FLAG_PAUSA]) {
			ConsolaAnalisys->AppendText(ArrayDataAnalisys[INFORME_ANALISYS]->ToString());
			ConsolaReader->AppendText(ArrayDataReader[INFORME]->ToString());
			ArrayDataAnalisys[INFORME_ANALISYS] = "";
			ArrayDataReader[INFORME] = "";
			if (Reader && Reader->newFrame) {
				Frame->Text = Convert::ToString(Reader->frame);
				Reader->newFrame = false;
			}
		}
		else if (Reader && Reader->newFrame) {
			ConsolaReader->AppendText(ArrayDataReader[INFORME]->ToString());
			ArrayDataReader[INFORME] = "";
		}
	}
	private: System::Void Cargar_Click(System::Object^  sender, System::EventArgs^  e) {
		ArrayDataReader[Hz] = Convert::ToInt32(Hercios->Text);
		ArrayDataAnalisys[INFORME_ANALISYS] = Convert::ToInt32(Hercios->Text);
	}
	private: System::Void Interfaz_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (Threads[THREAD_READER])
			Threads[THREAD_READER]->Abort();
		if (Threads[THREAD_ANALISIS])
			Threads[THREAD_ANALISIS]->Abort();
		if (Threads[THREAD_OPENGL])
			Threads[THREAD_OPENGL]->Abort();
		if (Threads[THREAD_GPS])
			Threads[THREAD_GPS]->Abort();
	}
	private: System::Void lock_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (!lock->Checked) {
			if (Convert::ToInt32(numlock->Text) > Convert::ToInt32(Frame->Text)) {
				Flags[FLAG_LOCK] = true;
				lock->Text = "locked";
				Reader->numSelector = Convert::ToInt32(numlock->Text);
			}
		}
		else {
			Flags[FLAG_LOCK] = false;
			lock->Text = "lock";
		}
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		Flags[FLAG_ANALIZAR] = true;
	}
	};
}
