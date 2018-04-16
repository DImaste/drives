//---------------------------------------------------------------------------

#pragma hdrstop

#include "FAT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "Main.h"
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Patterns.h"
#include "FileSystemClass.h"
//---------------------------------------------------------------------------

using namespace std;

//---------------------------------------------------------------------------
FAT_FS::FAT_FS(/*WCHAR *filePath*/)
{
	fileHandle = CreateFileW(MainForm->PathEdit->Text.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
								);

	if (fileHandle != INVALID_HANDLE_VALUE)
	{
			MainForm->LogBox->Items->Add("Opened Successfully");

			result = true;
	}
	else
	{
			MainForm->LogBox->Items->Add("Can't open drive");
			result = false;
	}

	BytesPerSector=0;
	SectorPerCluster=0;
	TotalSectors=0;
}

//---------------------------------------------------------------------------

bool FAT_FS::ReadBootBlock()
{
	BYTE bootSector[512];

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

	infoFAT = (BOOT_BLOCK_FAT*)bootSector;

	BytesPerReservedArea = infoFAT->reservedArea * infoFAT->bytesPerSector;
	BytesPerCopiesFAT = infoFAT->sizeOfCopiesFAT16 * infoFAT->countOfCopiesFAT
	 * infoFAT->bytesPerSector;
	BytesPerRootDirectory = infoFAT->maxCountOfFiles * 32;
	//BytesPerCluster = infoFAT->bytesPerSector * infoFAT->sectorPerClusterMlt;
	BytesPerSector = infoFAT->bytesPerSector;
	SectorPerCluster = infoFAT->sectorPerClusterMlt;
	ClusterSize =  BytesPerSector*SectorPerCluster;
	BeginCluster = 2;

	if ( infoFAT->countOfSectors16 == 0 )
	{
		TotalClusters = infoFAT->countOfSectors32 / infoFAT->sectorPerClusterMlt;
	}
	else
	{
		TotalClusters = infoFAT->countOfSectors16 / infoFAT->sectorPerClusterMlt;
	}

	strcpy_s(OEMID, strlen(infoFAT->OEMID )+1, infoFAT->OEMID);

	return true;
}
//---------------------------------------------------------------------------

ULONGLONG FAT_FS::GetTotalSectors()
{
	return TotalSectors;
}

//---------------------------------------------------------------------------

BYTE NTFS_FS::GetSectorPerCluster()
{
	return SectorPerCluster;
}

//---------------------------------------------------------------------------

BYTE* NTFS_FS::GetOEMName()
{
	return OEMID;
}

//---------------------------------------------------------------------------

UINT16 NTFS_FS::GetBytesPerSector()
{
	return BytesPerSector;
}

//---------------------------------------------------------------------------

HANDLE FAT_FS::GetFileHandle()
{
	return fileHandle;
}

//---------------------------------------------------------------------------

void FAT_FS::SetFileHandle(HANDLE FileSystemHandle)
{
	fileHandle = FileSystemHandle;
}

//---------------------------------------------------------------------------

 void FAT_FS::Destroy(HANDLE FileSystemHandle)
{
	CloseHandle(FileSystemHandle);
}

//---------------------------------------------------------------------------

DriveIterator <ClusterDisk> * FAT_FS::GetClusterIterator()
{
	return new FATIterator(this);
}

//---------------------------------------------------------------------------

bool FAT_FS::ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer)
{
	ULONGLONG StartOffset = BytesPerReservedArea + BytesPerCopiesFAT + BytesPerRootDirectory
	 + BytesPerCluster * ( StartCluster - BeginCluster );
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

