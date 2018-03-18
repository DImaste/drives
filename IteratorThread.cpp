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


	// ������� �������� �������
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	// ���������� ������ ��������

	clusterSize = NTFS.GetClusterSize();


	BYTE *dataBuffer = new BYTE[clusterSize];


	MySearchThread = new SearchThread(dataBuffer,clusterSize,false);  //new thread



	// ������� ��������� �����
	for(int i = 0; i<100; i++)
	{
		// ������������� ������ � ������
		//BufferAccessCS->Enter();

		// ������� ������ � ��������� �����
		Sleep(50);

		// �������������� ������ � ������
		//BufferAccessCS->Leave();

		// ��������� ���� ���������� ������
		MySearchThread->BufferReadyEvent->SetEvent();



		// ������� ��������� ����������� ������
		while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
		{
		}

		MySearchThread->BufferCopiedEvent->ResetEvent();
	}

	// ��������� �����
	MySearchThread->Terminate();

	delete[] dataBuffer;
}
//---------------------------------------------------------------------------
