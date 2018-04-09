//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------

#include "PatternIterator.h"
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
 /*
ArrayIterator::ArrayIterator(NTFS_FS *Fs)
 {
	container_size = fs->GetTotalSectors( ) / fs->GetSectorPerCluster( );
	fs=Fs;
 }

 void ArrayIterator::First()
 {
   index=0;
 }

void ArrayIterator::Next()
 {
   index++;
 }

 bool  ArrayIterator::IsDone()
 {
   return (index>=container_size);
 }

 void  ArrayIterator::GetCurrent(BYTE *buffer)
 {
   fs->ReadCluster(index, 1, buffer);
 }
  */

 NTFSClusterIterator::NTFSClusterIterator(NTFS_FS* fs)
{
	FileSystem = fs;
	CurrentCluster = 0;
	BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
	DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void NTFSClusterIterator::First( )
{
	CurrentCluster = 0;
}

// ------------------------------------------------------------------------------
void NTFSClusterIterator::Next( )
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool NTFSClusterIterator::IsDone( ) const
{
	int TotalClusters = FileSystem->GetTotalSectors( ) / FileSystem->GetSectorPerCluster( );
	return ( CurrentCluster >= TotalClusters );
}

// ------------------------------------------------------------------------------
ClusterDisk NTFSClusterIterator::GetCurrent( )
{
	FileSystem->ReadCluster( CurrentCluster, 1, DataBuffer );
	Cluster.assign( DataBuffer, DataBuffer + BytesPerCluster );
	return Cluster;
}

// ------------------------------------------------------------------------------
NTFSClusterIterator::~NTFSClusterIterator( )
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------
int NTFSClusterIterator::GetCurrentIndex( ) const
{
	return CurrentCluster;
}











NTFSDecorator::NTFSDecorator(NTFSClusterIterator * it, int beginCluster, int endCluster ) : IteratorDecorator < ClusterDisk > (it)
{
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}


void NTFSDecorator::First( )
{
	for ( It->First( ); !It->IsDone( ); It->Next( ) )
	{
		if ( It->GetCurrentIndex( ) == BeginCluster )
		{
			break;
		}
	}
}

void NTFSDecorator::Next( )
{
	It->Next( );
}

bool NTFSDecorator::IsDone( ) const
{
	if ( It->GetCurrentIndex( ) > EndCluster || It->IsDone( ) )
	{
		return true;
	}
	else
	{
		return It->IsDone( );
	}
}

ClusterDisk NTFSDecorator::GetCurrent( )
{
	return It->GetCurrent( );
}

int NTFSDecorator::GetCurrentIndex( ) const
{
	return It->GetCurrentIndex( );
}


