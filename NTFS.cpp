//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFS.h"
#include "Main.h"
#include <windows.h>

#include "Patterns.h"
#include "FSIterators.h"
#include "FileSystemClass.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

//---------------------------------------------------------------------------
NTFS_FS::NTFS_FS(/*WCHAR *filePath*/)
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

bool NTFS_FS::ReadBootBlock()
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

	infoNTFS = (BOOT_BLOCK_NTFS*)bootSector;

	BytesPerSector = infoNTFS->BytesPerSector;
	SectorPerCluster = infoNTFS->SectorsPerCluster;
	ClusterSize =  BytesPerSector*SectorPerCluster;
	TotalSectors = infoNTFS->TotalSectors;
	strcpy_s(OEMID, strlen(infoNTFS->OEMID )+1, infoNTFS->OEMID);

	return true;
}
//---------------------------------------------------------------------------

ULONGLONG NTFS_FS::GetTotalSectors()
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

 void NTFS_FS::DestroyFileSystem(HANDLE FileSystemHandle)
{
	CloseHandle(FileSystemHandle);
}

//---------------------------------------------------------------------------

DriveIterator <ClusterDisk> * NTFS_FS::GetClusterIterator()
{
	return new NTFSIterator(this);
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


