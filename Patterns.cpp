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

 DriveIterator::DriveIterator(NTFS_FS* fs)
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
	return ( CurrentCluster >= TotalClusters );
}

// ------------------------------------------------------------------------------
ClusterDisk DriveIterator::GetCurrent()
{
	FileSystem->ReadCluster( CurrentCluster, 1, DataBuffer );
	Cluster.assign( DataBuffer, DataBuffer + BytesPerCluster );
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
// ------------------------------------------------------------------------------

// Decorator realization

NTFSDecorator::NTFSDecorator(NTFSClusterIterator * it, int beginCluster, int endCluster) : IteratorDecorator <ClusterDisk> (it)
{
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}

// ------------------------------------------------------------------------------

void NTFSDecorator::First()
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

void NTFSDecorator::Next()
{
	It->Next( );
}

// ------------------------------------------------------------------------------

bool NTFSDecorator::IsDone() const
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

ClusterDisk NTFSDecorator::GetCurrent()
{
	return It->GetCurrent();
}

// ------------------------------------------------------------------------------

int NTFSDecorator::GetCurrentIndex() const
{
	return It->GetCurrentIndex();
}

// ------------------------------------------------------------------------------
