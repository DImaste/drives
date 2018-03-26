//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:

	HANDLE FileSystemHandle;
	SearchThread *MySearchThread;

protected:
	void __fastcall Execute();
public:
	__fastcall IteratorThread(WCHAR *filePath, WCHAR *sign, bool CreateSuspended);

	//WCHAR *filePath; //is there a sense?
	//WCHAR *sign ; //is there a sense?
};
//---------------------------------------------------------------------------
#endif
