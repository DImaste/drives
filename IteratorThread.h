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
	UnicodeString Path;
	UnicodeString StringTypeFs;
	FSType StructTypeFs;
	UnicodeString StartCluster;
	UnicodeString EndCluster;

	vector <BYTE> CurrentCluster;

public:

	//__fastcall IteratorThread(WCHAR *filePath, /*wstring fsType, */ bool CreateSuspended);

	__fastcall IteratorThread(UnicodeString filePath, UnicodeString fsType,
	UnicodeString startCluster,UnicodeString endCluster, bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
