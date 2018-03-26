//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include <memory>
#include "Main.h"
#include "IteratorThread.h"
#include "FileSystem.h"
#include "SearchThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace std;

// This file includes only the created form and the button event handler

//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchButtonClick(TObject *Sender)
{
	ResultTree->Clear();
	Television->Clear();
	LogBox->Items->Add("   ");
	LogBox->Items->Add("------New Search------");
	LogBox->Items->Add("   ");
	myIteratorThread = new IteratorThread(PathEdit->Text.c_str(),ByteEdit->Text.c_str(), false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveClick(TObject *Sender)
{

 FILE *fp = fopen ( "Attributes.txt","w");
  for ( int ii=0; ii<Television->GetCount(); ii++ )
  {
	int size = Television->GetTextLen();
	//char str[MAX_PATH]={0};
	//WCHAR* str ;//AX_PATH]={0};
	std::auto_ptr <WCHAR> Buffer(new WCHAR[size]);
	Television->GetTextBuf(Buffer.get(),size);   //(ii,str);
	LogBox->Items->Add(size);
	fprintf(fp,"%s\n",Buffer.get());
  }
  fclose(fp);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StopButtonClick(TObject *Sender)
{
	Application->MessageBoxW(L"Search Terminated!", L"", MB_OK);
	myIteratorThread->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ResultTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
      		if (!Node)
	{
		MessageBoxW(NULL,L"ќшибка выбора Node",L"ќшибка",MB_OK);
		return;
	}
	FileTree * nodeData = (FileTree *)Sender->GetNodeData(Node);
	switch (Column)
	{
	case 0:
		CellText = nodeData->currentCluster;
		break;
	case 1:
		CellText = (char *)nodeData->signature;
		break;
	case 2:
		CellText = (char *)nodeData->extensionFile;
		break;
	}
}
//---------------------------------------------------------------------------

