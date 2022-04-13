//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ������������ ���������
void TForm1::test() {
	 Button1->Click();
	 for(int i = 0; i < 30; i++) {
		 if(questions[i].getCorrectAnswers() == 1) {
			 RadioButton1->Checked = true;
		 } else if (questions[i].getCorrectAnswers() == 2) {
			 RadioButton2->Checked = true;
		 } else if (questions[i].getCorrectAnswers() == 3) {
			 RadioButton3->Checked = true;
		 } else if (questions[i].getCorrectAnswers() == 4) {
			 RadioButton4->Checked = true;
		 }
         Button1->Click();
	 }
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Button1->Caption = "������ ������������";
}

// ������ ������ ������������/����������� �����
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(!startTest) {
		openTest();
	} else {
		setAnswer();
		numberOfQuestion += 1;

		if(numberOfQuestion >= 30) {
			for(int i = 0; i < 30; i++) {
				if(questions[i].isCorrectAnswer(ans[i])) {
					correctAnswers += 1;
				}
			}
			ShowMessage("���������: " + FloatToStr(round((double(correctAnswers) / 30 * 100))) + "%" + sLineBreak
						+ "���������� �������: " + IntToStr(correctAnswers) + sLineBreak
						+ "����� ��������: " + IntToStr(30));
			//enableRadioButtons(false);
			correctAnswers = 0;
			numberOfQuestion -= 1;
			RadioButton1->Color = clRed;
			Close();
			return;
		}
	}
	setNumberOfQuestion();
	loadQuestion();
	if(ans[numberOfQuestion] != 0) {
		getAnswer();
	} else {
		clearRadioButtons();
    }
}

// ��������� ������ ��� ������ � �������� ������������
void TForm1::openTest() {
    Button1->Caption = "����������� �����";
		startTest = true;
		RadioButton1->Visible = true;
		RadioButton2->Visible = true;
		RadioButton3->Visible = true;
		RadioButton4->Visible = true;
		switch (ComboBox1->ItemIndex) {
			case 0:
				name = "���������";
				break;
			case 1:
				name = "������������ �����������������";
				break;
			case 2:
				name = "���������� �������� � ��������� �������� ����������";
				break;
			case 3:
				name = "������ �����";
				break;
			case 4:
				name = "�����������";
				break;
			case 5:
				name = "������ ����������� � �������� ������������";
				break;
			case 6:
				name = "������ �������������� ����������";
				break;
			case 7:
				name = "������ ��������������";
				break;
			case 8:
				name = "���������� ���������� �������������� ����������";
				break;
			default:
				name = "���������";
		}
		loadDataBase(name);
		if(ADOQuery1->RecordCount == 0 || ADOQuery2->RecordCount == 0) return;
		for(int i = 0; !ADOQuery1->Eof && !ADOQuery2->Eof; i++) {
			questions[i].setQuestion(ADOQuery1->FieldByName("Quest")->AsString);
			String answers[4] = {ADOQuery2->FieldByName("A")->AsString,
								ADOQuery2->FieldByName("B")->AsString,
								ADOQuery2->FieldByName("C")->AsString,
								ADOQuery2->FieldByName("D")->AsString};
			questions[i].setAnswers(answers);
			questions[i].setTrueAnswer(ADOQuery1->FieldByName("trueAnswer")->AsInteger);
			ADOQuery1->Next();
			ADOQuery2->Next();
		}
		int rnd;
		Testing temp;
		srand(time(0));
		for(int i = 0; i < ADOQuery1->RecordCount; i++) {
			rnd = rand() % 150;
			temp = questions[rnd];
			questions[rnd] = questions[i];
			questions[i] = temp;
		}
		ComboBox1->Visible = false;
}

// ��������� ���� ������
void TForm1::loadDataBase(String name) {
    ADOConnection1->Connected = false;
	ADOConnection1->ConnectionString =  "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="
							+ ExtractFilePath(Application->ExeName) +"\\DB\\" + name + ".mdb";
	ADOQuery1->Connection = ADOConnection1;
	ADOQuery2->Connection = ADOConnection1;
	DataSource1->DataSet = ADOQuery1;
	DataSource2->DataSet = ADOQuery2;
	ADOQuery1->SQL->Add("Select * From Question");
	ADOQuery2->SQL->Add("Select * From Answers");
	ADOConnection1->Connected = true;
	ADOQuery1->Active = true;
	ADOQuery2->Active = true;

    questions = new Testing[ADOQuery1->RecordCount];
	ans = new int[ADOQuery1->RecordCount];
}

// ����������/������������ �����������
void TForm1::enableRadioButtons(bool enable) {
	RadioButton1->Enabled = enable;
	RadioButton2->Enabled = enable;
	RadioButton3->Enabled = enable;
	RadioButton4->Enabled = enable;
}

// ��������� ������ � ���������� �������
void TForm1::loadQuestion() {
	Label1->Caption = questions[numberOfQuestion].getQuestion();
	RadioButton1->Caption = questions[numberOfQuestion].getAnswers(0);
	RadioButton2->Caption = questions[numberOfQuestion].getAnswers(1);
	RadioButton3->Caption = questions[numberOfQuestion].getAnswers(2);
	RadioButton4->Caption = questions[numberOfQuestion].getAnswers(3);
}

// ��������� ������� ������, ������ ������������� �� ����� �������
void TForm1::getAnswer() {
	if(ans[numberOfQuestion] == 1) {
		RadioButton1->Checked = true;
	} else if(ans[numberOfQuestion] == 2) {
		RadioButton2->Checked = true;
	} else if(ans[numberOfQuestion] == 3) {
		RadioButton3->Checked = true;
	} else if(ans[numberOfQuestion] == 4) {
		RadioButton4->Checked = true;
	} else {
		clearRadioButtons();
	}
}

// ������������� ��� ��������� ������������� �������� ������
void TForm1::setAnswer() {
	if(RadioButton1->Checked == true) {
		ans[numberOfQuestion] = 1;
	} else if(RadioButton2->Checked == true) {
		ans[numberOfQuestion] = 2;
	} else if(RadioButton3->Checked == true) {
		ans[numberOfQuestion] = 3;
	} else if(RadioButton4->Checked == true) {
		ans[numberOfQuestion] = 4;
	} else {
		ans[numberOfQuestion] = 0;
	}
}

// ������� ���� ������
void TForm1::clearRadioButtons() {
	RadioButton1->Checked = false;
	RadioButton2->Checked = false;
	RadioButton3->Checked = false;
	RadioButton4->Checked = false;
}

// ���������� ���������� ����� �� ������
int Testing::getCorrectAnswers() {
	return trueAnswer;
}

// ���������� ������
String Testing::getQuestion() {
	return question;
}

// ������������� ������
void Testing::setQuestion(String question) {
	this->question = question;
}

// ���������� ������� ������
String Testing::getAnswers(int number) {
	return answers[number];
}

// ������������� 4 �������� ������
void Testing::setAnswers(String answers[4]) {
	for(int i = 0; i < 4; i++) {
		this->answers[i] = answers[i];
	}
}

// ������������� ���������� ����� �� ������
void Testing::setTrueAnswer(int trueAnswer) {
	this->trueAnswer = trueAnswer;
}

// ��������� ������������ ������ ������� �������������
bool Testing::isCorrectAnswer(int answer) {
	return trueAnswer == answer;
}

// ������������� ����� ������� �� GroupBox
void TForm1::setNumberOfQuestion() {
	GroupBox1->Caption = name + " ������ �" + IntToStr(numberOfQuestion + 1);
}

// ������ ��������� � ����������� �������
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(numberOfQuestion - 1 <0) return;
	numberOfQuestion -= 1;
	setNumberOfQuestion();
	loadQuestion();
	getAnswer();
}

// ����������
TForm1::~TForm1() {
	delete [] ans;
	delete [] questions;
}
//---------------------------------------------------------------------------

// ������������ ���������
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//test();
}
//---------------------------------------------------------------------------

