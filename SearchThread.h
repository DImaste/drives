//---------------------------------------------------------------------------

#ifndef SearchThreadH
#define SearchThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
//---------------------------------------------------------------------------
// Критическая секция добавления результатов поиска
	//TCriticalSection *BufferAccessCS;
//---------------------------------------------------------------------------
const int WaitDelayMs = 2000;
//---------------------------------------------------------------------------

typedef struct
{
	__int64 currentCluster;
	BYTE signature[5];
	BYTE extensionFile[5];
} FileTree;


class SearchThread : public TThread
{
private:
	int ClusterSize;
	BYTE *OutBufferPtr;
	BYTE *DataBuffer;
	int CurrentCluster;
	BYTE signature[5];
	BYTE extensionFile[5];


	void CopyData();
	void SearchData();
	void __fastcall AddMatch();
	void __fastcall CompleteSearch();


protected:
	void __fastcall Execute();
public:
	__fastcall SearchThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended);
	 void SetCurrentCluster(int Cluster);

	// События, используемые для синхронизации
	TEvent *BufferReadyEvent;
	TEvent *BufferCopiedEvent;
};
//---------------------------------------------------------------------------
#endif
