
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "FileSystem.h"
#include "SearchThread.h"
#include "IteratorThread.h"
#include "Main.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

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

__fastcall SearchThread::SearchThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended, int clusterscount )
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	MainForm->Progress->Max = clusterscount;
	point = 1;

	// multithread events
	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);

	//BufferAccessCS = new TCriticalSection;

	CurrentCluster = 0;
	ClusterSize = clusterSize;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[clusterSize];

   //	vector<const char *> signatures;

   signatures.push_back("\x49\x44\x33"); //mp3
   signatures.push_back("\x21\x3C\x61\x72\x63\x68\x3E"); //deb
   signatures.push_back("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"); //png    89 50 4E 47 0D 0A 1A 0A
   signatures.push_back("\x37\x7A\xBC\xAF\x27\x1C"); //7zip    37 7A BC AF 27 1C

  // vector<int> sign_size;

   sign_size.push_back(3);
   sign_size.push_back(7);
   sign_size.push_back(8);
   sign_size.push_back(6);

  // vector<const char *> sign_name;

   sign_name.push_back(".mp3");
   sign_name.push_back(".deb");
   sign_name.push_back(".png");
   sign_name.push_back(".7z ");


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
				MainForm->Progress->Position = point;
				point++;
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
/*
	vector<const char *> signatures;

   signatures.push_back("\x49\x44\x33"); //mp3
   signatures.push_back("\x21\x3C\x61\x72\x63\x68\x3E"); //deb
   signatures.push_back("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"); //png    89 50 4E 47 0D 0A 1A 0A
   signatures.push_back("\x37\x7A\xBC\xAF\x27\x1C"); //7zip    37 7A BC AF 27 1C

   vector<int> sign_size;

   sign_size.push_back(3);
   sign_size.push_back(7);
   sign_size.push_back(8);
   sign_size.push_back(6);

   vector<const char *> sign_name;

   sign_name.push_back(".mp3");
   sign_name.push_back(".deb");
   sign_name.push_back(".png");
   sign_name.push_back(".7z ");

  */


   for (int i=0; i<signatures.size();i++)
	{

	// Провести поиск
		 if ( memcmp( DataBuffer, signatures[i], sign_size[i]) == 0 )
		{
			memcpy( signature, signatures[i], sign_size[i]);
			memcpy( extensionFile, sign_name[i], 4 );
			Synchronize(&AddMatch );
		}


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
