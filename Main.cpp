//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "IteratorThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TMainForm *MainForm;

// This file includes only the created form and the button event handler

//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchButtonClick(TObject *Sender)
{
	IteratorThread *myIteratorThread = new IteratorThread(PathEdit->Text.c_str(), false);

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ReadBufferClick(TObject *Sender)
{
  //	SearchThread *mySearchThread = new SearchThread(/*something*/);

}

//---------------------------------------------------------------------------

