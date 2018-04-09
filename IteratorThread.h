//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
//#include "FileSystem.h"

//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:

	HANDLE FileSystemHandle;
	SearchThread *MySearchThread;

protected:
	void __fastcall Execute();
	WCHAR* path;
	vector < BYTE > CurrentCluster;

public:
	__fastcall IteratorThread(WCHAR *filePath,  bool CreateSuspended);
   //	NTFS_FS * mydisk;

	//WCHAR *filePath; //is there a sense?
	//WCHAR *sign ; //is there a sense?
};
//---------------------------------------------------------------------------
#endif
