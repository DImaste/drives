//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------

#include "Patterns.h"
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Main.h"
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

 //Iterator realization
/*
 DriveIterator::DriveIterator()
{
   //	FileSystem = fs;
   //	CurrentCluster = 0;
   //	BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
	DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void DriveIterator::First()
{
	CurrentCluster = 0;
}

// ------------------------------------------------------------------------------
void DriveIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool DriveIterator::IsDone() const
{
   //	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	//return (CurrentCluster >= TotalClusters);
	return true;
}

// ------------------------------------------------------------------------------
ClusterDisk DriveIterator::GetCurrent()
{
   //	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
   //	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	//Cluster=0;
	return Cluster;
}

// ------------------------------------------------------------------------------
DriveIterator::~DriveIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int DriveIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}
*/

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

//NTFS Iterator

 NTFSIterator::NTFSIterator(NTFS_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = 0;
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void NTFSIterator::First()
{
	CurrentCluster = 0;
}

// ------------------------------------------------------------------------------
void NTFSIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool NTFSIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk NTFSIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
NTFSIterator::~NTFSIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int NTFSIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

//FAT Iterator

 FATIterator::FATIterator(FAT_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = 0;
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void FATIterator::First()
{
	CurrentCluster = 0;
}

// ------------------------------------------------------------------------------
void FATIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool FATIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk FATIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
FATIterator::~FATIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int FATIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

//exFAT Iterator

 exFATIterator::exFATIterator(exFAT_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = 0;
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void exFATIterator::First()
{
	CurrentCluster = 0;
}

// ------------------------------------------------------------------------------
void exFATIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool exFATIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk exFATIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
exFATIterator::~exFATIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int exFATIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

// Decorator realization

DriveDecorator::DriveDecorator(DriveIterator * it, int beginCluster, int endCluster)
{
	It= it;
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}

// ------------------------------------------------------------------------------

void DriveDecorator::First()
{
	for (It->First(); !It->IsDone(); It->Next())
	{
		if (It->GetCurrentIndex() == BeginCluster)
		{
			break;
		}
	}
}

// ------------------------------------------------------------------------------

void DriveDecorator::Next()
{
	It->Next( );
}

// ------------------------------------------------------------------------------

bool DriveDecorator::IsDone() const
{
	if (It->GetCurrentIndex() > EndCluster || It->IsDone())
	{
		return true;
	}
	else
	{
		return It->IsDone();
	}
}

// ------------------------------------------------------------------------------

ClusterDisk DriveDecorator::GetCurrent()
{
	return It->GetCurrent();
}

// ------------------------------------------------------------------------------

int DriveDecorator::GetCurrentIndex() const
{
	return It->GetCurrentIndex();
}

// ------------------------------------------------------------------------------
