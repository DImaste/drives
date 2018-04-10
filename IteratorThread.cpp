//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include <windows.h>
#include "IteratorThread.h"
#include "Patterns.h"
#include "FileSystem.h"


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
	path= filePath;
	//mydisk = new NTFS_FS(path);

}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	// bool result=false;

	 NTFS_FS *mydisk = new NTFS_FS();
	// NTFS_FS mydisk = NTFS_FS();

	/*
	 FileSystemHandle = mydisk.GetFileHandle();
	 */
	  FileSystemHandle = mydisk->GetFileHandle();


	 int BytesPerCluster;
	 int TotalClusters;


		if (mydisk->result)
		{
			MainForm->LogBox->Items->Add("Ok");

			mydisk->SetFileHandle(FileSystemHandle);

			if (FileSystemHandle == 0)
			{
				Application->MessageBoxW(L"Handle Lost", L"", MB_OK);
			}

			if (mydisk->ReadBootBlock())
				{
					/*
					TotalClusters = mydisk.GetTotalSectors( ) / mydisk.GetSectorPerCluster( );
					BytesPerCluster = mydisk.GetBytesPerSector() * mydisk.GetSectorPerCluster( );
					int TotalSectors  = mydisk.GetTotalSectors();
					int BytesPerSector = mydisk.GetBytesPerSector();
				   //	int OEMID = mydisk

				   */

					TotalClusters = mydisk->GetTotalSectors( ) / mydisk->GetSectorPerCluster( );
					BytesPerCluster = mydisk->GetBytesPerSector() * mydisk->GetSectorPerCluster( );
					int TotalSectors  = mydisk->GetTotalSectors();
					int BytesPerSector = mydisk->GetBytesPerSector();


					MainForm->Television->Items->Add("Sector Size = "+ IntToStr(BytesPerSector)+" Bytes" );
					MainForm->Television->Items->Add("Total Sectors = "+ IntToStr(TotalSectors));
					MainForm->Television->Items->Add("Cluster Size = "+ IntToStr(BytesPerCluster)+" Bytes");
					MainForm->Television->Items->Add("Total Clusters = "+ IntToStr(TotalClusters));

					MainForm->LogBox->Items->Add("Read MBR successfully!");
				}
			else
				{
					MainForm->LogBox->Items->Add("Read MBR Error!");
				}
		}
	else
		{
			MainForm->LogBox->Items->Add("nOk");
		}

	//Это неправильно, нужно вынести это в конструктор переборного потока

	int BeginCluster;
	int EndCluster;

	if  (MainForm->End->Text=="end")
	{
		BeginCluster = StrToInt(MainForm->Start->Text);
		EndCluster = TotalClusters;
	}
	else
	{
	   BeginCluster = StrToInt(MainForm->Start->Text) ;
	   EndCluster = StrToInt(MainForm->End->Text);
	}


	int clusterSize = BytesPerCluster;
	BYTE *dataBuffer = new BYTE[clusterSize];


	DriveIterator *It  =new DriveIterator( mydisk );

	//	DriveIterator *ArrIterator = new DriveDecorator( new DriveIterator( &mydisk ), BeginCluster, EndCluster );

	DriveDecorator *ArrIterator = new DriveDecorator( It, BeginCluster, EndCluster );

	MySearchThread = new SearchThread(dataBuffer,clusterSize,false, TotalClusters);  //new thread

	if (memcmp(mydisk->GetOEMName(), "\x4e\x54\x46\x53\x20\x20\x20\x20",  8) == 0 )
		{
			for (ArrIterator->First(); !ArrIterator->IsDone(); ArrIterator->Next())
				{
				   /*	if (!mydisk.ReadCluster( i, 1, dataBuffer ) )
						{
							Application->MessageBoxW(L"ReadClusterError", L"", MB_OK);
							break;
						}   */

						 CurrentCluster = ArrIterator->GetCurrent();


					// Заблокировать доступ к буферу
					//BufferAccessCS->Enter();

					// Разблокировать доступ к буферу
					//BufferAccessCS->Leave();

					// Выставить флаг готовности буфера
					MySearchThread->BufferReadyEvent->SetEvent();

					// Ожидать окончания копирования буфера
					while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
						{
						}

					MySearchThread->SetCurrentCluster(ArrIterator->GetCurrentIndex());

					MySearchThread->BufferCopiedEvent->ResetEvent();

					if ( Terminated )
						{
							break;
						}
				}

			MainForm->LogBox->Items->Add("Read Clusters succesfully!");
		}
	else
		{
			Application->MessageBoxW(L"NotNTFS", L"", MB_OK);
			//break;
        }

	// Завершить поиск
	MySearchThread->Terminate();

	CloseHandle(FileSystemHandle);
	delete[] dataBuffer;
	delete[] It;
	delete[] ArrIterator;
}
//---------------------------------------------------------------------------


