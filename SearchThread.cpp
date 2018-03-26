//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "FileSystem.h"
#include "SearchThread.h"
#include "IteratorThread.h"
#include "Main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SearchThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }

// this file contains reading thread

//---------------------------------------------------------------------------

__fastcall SearchThread::SearchThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	// multithread events
	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);

	//BufferAccessCS = new TCriticalSection;

	CurrentCluster = 0;
	ClusterSize = clusterSize;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[clusterSize];
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::Execute()
{
	while(true)
	{
		// Ждать, пока не будет подготовлен буфер для копирования
		if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
		{
			//if(BufferAccessCS->TryEnter())
			if(true)
			{
				// Скопировать данные
				CopyData();

				// Отпустить буфер
				BufferReadyEvent->ResetEvent();
				BufferCopiedEvent->SetEvent();

				// Запустить поиск
				SearchData();
				//BufferAccessCS->Leave();
			}
		}
		if(Terminated) break;
	}
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	//delete BufferAccessCS;

  // Удалить буфер
	delete[] DataBuffer;
	Synchronize(&CompleteSearch);
}
//---------------------------------------------------------------------------

void SearchThread::SetCurrentCluster(int Cluster)
 {
	CurrentCluster = Cluster;

 }


//---------------------------------------------------------------------------
void SearchThread::CopyData()
{
	memcpy(DataBuffer, OutBufferPtr, ClusterSize);
}

//---------------------------------------------------------------------------
void SearchThread::SearchData()
{

	// Провести поиск
   if ( memcmp( DataBuffer, "\x49\x44\x33\x03", 4 ) == 0 )
	{
		memcpy( signature, "\x49\x44\x33\x03", 4 );
		memcpy( extensionFile, ".mp3", 4 );
		Synchronize(&AddMatch );
	}


	// memcmp
   //	bool matchFound = true;

   /*	if(matchFound)
	{
		Synchronize(&AddMatch);
	} */
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch()
{
	//PVirtualNode newNode = MainForm->ResultTree->AddChild(MainForm->ResultTree->RootNode);

	PVirtualNode newNode = MainForm->ResultTree->AddChild(MainForm->ResultTree->RootNode);
	FileTree* nodeData = (FileTree*)MainForm->ResultTree->GetNodeData(newNode);
	nodeData-> currentCluster = CurrentCluster;
	memcpy(nodeData->signature, signature, 4);
	memcpy(nodeData->extensionFile, extensionFile, 4);

}


//---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch()
{
	Application->MessageBoxW(L"Поиск завершен!", L"", MB_OK);
}
