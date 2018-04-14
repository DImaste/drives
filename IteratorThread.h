//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
#include "string"
#include "FileSystemClass.h"


//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:

	HANDLE FileSystemHandle;
	SearchThread *MySearchThread;

protected:
	void __fastcall Execute();
	UnicodeString path;
	UnicodeString StringTypeFs;
	FSType StructTypeFs;

	vector <BYTE> CurrentCluster;

public:


	//__fastcall IteratorThread(WCHAR *filePath, /*wstring fsType, */ bool CreateSuspended);

	__fastcall IteratorThread(UnicodeString filePath, UnicodeString fsType, bool CreateSuspended);


   //	NTFS_FS * mydisk;

	//WCHAR *filePath; //is there a sense?
	//WCHAR *sign ; //is there a sense?
};
//---------------------------------------------------------------------------
#endif
