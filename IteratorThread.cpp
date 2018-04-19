//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include <windows.h>
#include "IteratorThread.h"
#include "Patterns.h"
#include <iostream>
#include <map>
#include "FileSystemClass.h"

using namespace std;
#pragma package(smart_init)

__fastcall IteratorThread::IteratorThread(UnicodeString filePath, UnicodeString fsType,
UnicodeString startCluster, UnicodeString endCluster, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	Path= filePath;
	StringTypeFs=fsType;
	StartCluster = startCluster;
	EndCluster = endCluster;
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	  FSType StructTypeFs;

	  map <UnicodeString, FSType> mapper;

	  if (mapper.count(StringTypeFs))
	  {
		  StructTypeFs =  mapper[StringTypeFs] ;
      }

	  FileSystemClass *mydisk = FileSystemClass::CreateFileSystem(Path ,StructTypeFs);
	  FileSystemHandle = mydisk->GetFileHandle();


	  int BytesPerCluster;
	  int TotalClusters;

			MainForm->LogBox->Items->Add("Ok");

			mydisk->SetFileHandle(FileSystemHandle);

			if (FileSystemHandle == 0)
			{
				Application->MessageBoxW(L"Handle Lost", L"", MB_OK);
			}

			if (mydisk->ReadBootBlock())
			{
				TotalClusters = mydisk->GetTotalSectors() / mydisk->GetSectorPerCluster( );
				BytesPerCluster = mydisk->GetBytesPerSector() * mydisk->GetSectorPerCluster( );
				int TotalSectors  = mydisk->GetTotalSectors();
				int BytesPerSector = mydisk->GetBytesPerSector();


				MainForm->Television->Items->Add("Sector Size = "+ IntToStr(BytesPerSector)+" Bytes" );
				MainForm->Television->Items->Add("Total Sectors = "+ IntToStr(TotalSectors));
				MainForm->Television->Items->Add("Cluster Size = "+ IntToStr(BytesPerCluster)+" Bytes");
				MainForm->Television->Items->Add("Total Clusters = "+ IntToStr(TotalClusters));

				MainForm->LogBox->Items->Add("Read Boot Record successfully!");
			}
			else
			{
				MainForm->LogBox->Items->Add("Read Boot Record Error!");
			}

	__int64 BeginClusterInt=0;
	__int64 LastClusterInt=0;

	if  (EndCluster=="end" && StartCluster=="start")
	{
		BeginClusterInt = mydisk->GetFirstCluster();
		LastClusterInt = TotalClusters;
	}

	if  (EndCluster!="end" && StartCluster=="start")
	{
		BeginClusterInt = mydisk->GetFirstCluster();
		LastClusterInt = StrToInt(EndCluster);
	}

	if  (EndCluster=="end" && StartCluster!="start")
	{
		BeginClusterInt = StrToInt(StartCluster);
		LastClusterInt = TotalClusters;
	}

	if  (EndCluster!="end" && StartCluster!="start")
	{
		BeginClusterInt = StrToInt(StartCluster);
		LastClusterInt = StrToInt(EndCluster);
	}

	int clusterSize = BytesPerCluster;
	BYTE *dataBuffer = new BYTE[clusterSize];

	DriveIterator <ClusterDisk> *Dec = mydisk->GetClusterIterator();

	//DriveIterator <ClusterDisk> *Dec = new DriveDecorator( It, BeginClusterInt, LastClusterInt );

	MySearchThread = new SearchThread(dataBuffer,clusterSize, false, TotalClusters);  //new thread


		for (Dec->First(); !Dec->IsDone(); Dec->Next())
			{
				CurrentCluster = Dec->GetCurrent();
				MySearchThread->BufferReadyEvent->SetEvent();

				while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
				{
				}

				MySearchThread->SetCurrentCluster(Dec->GetCurrentIndex());

				MySearchThread->BufferCopiedEvent->ResetEvent();

				if ( Terminated )
				{
					break;
				}
			}

			MainForm->LogBox->Items->Add("Read Clusters succesfully!");

	MySearchThread->Terminate();

	mydisk->DestroyFileSystem(FileSystemHandle);

	delete[] dataBuffer;
	delete mydisk;
	delete[] Dec; //decorator
   //	delete[] It;  //iterator

}
//---------------------------------------------------------------------------


