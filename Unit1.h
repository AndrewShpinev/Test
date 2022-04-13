//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class Testing {
private:
	String question;
	String answers[4];
	int trueAnswer;

public:

	int getCorrectAnswers();

	String getQuestion();

	void setQuestion(String question);

	String getAnswers(int number);

	void setAnswers(String answers[4]);

	void setTrueAnswer(int trueAnswer);

	bool isCorrectAnswer(int answer);
};

class TForm1 : public TForm
{
__published:
	TGroupBox *GroupBox1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TButton *Button1;
	TLabel *Label1;
	TADOConnection *ADOConnection1;
	TDataSource *DataSource1;
	TDataSource *DataSource2;
	TADOQuery *ADOQuery1;
	TADOQuery *ADOQuery2;
	TButton *Button2;
	TComboBox *ComboBox1;
	TImage *Image1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
public:
    bool startTest = false;
	int numberOfQuestion = 0;
	int correctAnswers = 0;
    String name;
	int *ans;

	void clearRadioButtons();
	void enableRadioButtons(bool enable);
	void getAnswer();
	void loadDataBase(String nameDB);
	void loadQuestion();
	void openTest();
	void setAnswer();
	void setColor();
	void setNumberOfQuestion();
	void test();

	Testing *questions;
	__fastcall TForm1(TComponent* Owner);
	_fastcall ~TForm1();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
