//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFS.h"
#include "Main.h"
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Patterns.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

//---------------------------------------------------------------------------

bool NTFS_FS::ReadBootBlock()
{
	//BYTE *dataBuffer = new BYTE[512];  // allocate memory mbr size - no need dynamic

	BYTE bootSector[512]; // длина загрузочного сектора

	ULONGLONG startOffset = 0;
	LARGE_INTEGER sectorOffset;		// DWORD LowPart, LONG  HighPart, LONGLONG QuadPart
	sectorOffset.QuadPart = startOffset;

	unsigned long currentPosition = SetFilePointer
	(
			fileHandle,
			sectorOffset.LowPart,
			&sectorOffset.HighPart,
			FILE_BEGIN
	);

	if(currentPosition != sectorOffset.LowPart)
	{
			Application->MessageBoxW(L"Dont", L"", MB_OK);
	}

	DWORD bytesToRead = 512;
	DWORD bytesRead;         //already

	bool readResult = ReadFile
	(
			fileHandle,
			bootSector,
			bytesToRead,
			&bytesRead,
			NULL
	);

	if ( !readResult || bytesRead != bytesToRead )
	{
		Application->MessageBoxW(L"ReadMBRError", L"", MB_OK);
		return false;
	}

	infoNTFS = (BOOT_BLOCK*)bootSector;

	BytesPerSector = infoNTFS->BytesPerSector;
	SectorPerCluster = infoNTFS->SectorsPerCluster;
	ClusterSize =  BytesPerSector*SectorPerCluster;
	TotalSectors = infoNTFS->TotalSectors;
	strcpy_s(OEMID, strlen(infoNTFS->OEMID )+1, infoNTFS->OEMID);

	return true;
}
//---------------------------------------------------------------------------

bool NTFS_FS::ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer)
{
	ULONGLONG StartOffset = StartCluster*ClusterSize;
	DWORD BytesToRead = NumberOfClusters*ClusterSize;
	DWORD BytesRead;
    LARGE_INTEGER SectorOffset;
	SectorOffset.QuadPart = StartOffset;

	unsigned long currentPosition = SetFilePointer
		(
			fileHandle,
			SectorOffset.LowPart,
			&SectorOffset.HighPart,
			FILE_BEGIN
		);
	if(currentPosition != SectorOffset.LowPart)
		{
			Application->MessageBoxW(L"DontCluster", L"", MB_OK);
			return false;
		}

	bool Result = ReadFile(fileHandle, dataBuffer, BytesToRead, &BytesRead, NULL);

	if(!Result || BytesRead != BytesToRead)
		{
			Application->MessageBoxW(L"DontReadClusterRead", L"", MB_OK);
			return false;
		}

	return true;

}

//---------------------------------------------------------------------------

HANDLE NTFS_FS::GetFileHandle()
{
	return fileHandle;
}

//---------------------------------------------------------------------------

void NTFS_FS::SetFileHandle(HANDLE FileSystemHandle)
{
	fileHandle = FileSystemHandle;
}

//---------------------------------------------------------------------------

IndexIterator <ClusterDisk> NTFS_FS::*GetClusterIterator()
{
	return new NTFSIterator(this);
}


