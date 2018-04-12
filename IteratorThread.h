//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
#include "string"
#include "FileSystemClass.h"
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
	__fastcall IteratorThread(WCHAR *filePath, wstring fsType,  bool CreateSuspended);

	wstring FsType;


   //	NTFS_FS * mydisk;

	//WCHAR *filePath; //is there a sense?
	//WCHAR *sign ; //is there a sense?
};
//---------------------------------------------------------------------------
#endif
