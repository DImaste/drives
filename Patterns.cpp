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

 //Iterator realization

 DriveIterator::DriveIterator(/*NTFS_FS* fs*/)
{
	FileSystem = fs;
	CurrentCluster = 0;
	BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
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
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk DriveIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
DriveIterator::~DriveIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

//rename
int DriveIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}
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
