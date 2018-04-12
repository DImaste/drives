//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "IteratorThread.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *PathEdit;
	TVirtualStringTree *ResultTree;
	TButton *SearchButton;
	TListBox *Television;
	TLabeledEdit *Start;
	TListBox *LogBox;
	TButton *Save;
	TButton *StopButton;
	TProgressBar *Progress;
	TLabeledEdit *End;
	TComboBox *FsType;
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall SaveClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall ResultTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVSTTextType TextType, UnicodeString &CellText);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

	IteratorThread * myIteratorThread;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
