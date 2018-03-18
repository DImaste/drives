//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IteratorThread.h"
#include "FileSystem.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall IteratorThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }

// this file contains searching iterator class

//---------------------------------------------------------------------------

__fastcall IteratorThread::IteratorThread(WCHAR *filePath, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	NTFS_FS NTFS = new NTFS_FS(); // create instance
	NTFS.GetClusterSize();
	NTFS.GetFileSystemSize();


	// Открыть файловую систему
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	// Определить размер кластера

	clusterSize = NTFS.GetClusterSize();


	BYTE *dataBuffer = new BYTE[clusterSize];


	MySearchThread = new SearchThread(dataBuffer,clusterSize,false);  //new thread



	// Перебор кластеров диска
	for(int i = 0; i<100; i++)
	{
		// Заблокировать доступ к буферу
		//BufferAccessCS->Enter();

		// Считать данные в локальный буфер
		Sleep(50);

		// Разблокировать доступ к буферу
		//BufferAccessCS->Leave();

		// Выставить флаг готовности буфера
		MySearchThread->BufferReadyEvent->SetEvent();



		// Ожидать окончания копирования буфера
		while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
		{
		}

		MySearchThread->BufferCopiedEvent->ResetEvent();
	}

	// Завершить поиск
	MySearchThread->Terminate();

	delete[] dataBuffer;
}
//---------------------------------------------------------------------------
