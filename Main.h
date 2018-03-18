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
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *PathEdit;
	TVirtualStringTree *ResultTree;
	TButton *SearchButton;
	TListBox *Television;
	TButton *ReadBuffer;
	TLabeledEdit *ByteEdit;
	TListBox *LogBox;
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall ReadBufferClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
