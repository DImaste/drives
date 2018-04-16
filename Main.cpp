//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include <memory>
#include "Main.h"
#include "IteratorThread.h"
#include "SearchThread.h"
#include <string>
#include <vector>

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

	//myIteratorThread = new IteratorThread(PathEdit->Text.c_str(), /*FsType->Text,*/ false);
	//myIteratorThread = new IteratorThread(PathEdit->Text, FsType->Text, false);
	IteratorThread *myIteratorThread1 =  new IteratorThread(PathEdit->Text, FsType->Text,Start->Text ,End->Text ,false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveClick(TObject *Sender)
{

	LogBox->Items->Add("Check that stuff");

	vector<wstring> s;
	s.resize(Television->Items->Count);

	FILE *fp = fopen ( "Attributes.txt","w");

	for (int i=0;i<Television->Items->Count; i++)
		{

			s[i]=wstring(Television->Items->Strings[i].c_str());
			fprintf(fp,"%s\n",s[i]);

		}

	fclose(fp);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StopButtonClick(TObject *Sender)
{
	Application->MessageBoxW(L"Search Terminated!", L"", MB_OK);
	//myIteratorThread1->Terminate();
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


