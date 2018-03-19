//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystem.h"
#include "Main.h"
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)



using namespace std;

/*
NTFS_FS::NTFS_FS()
{

}

NTFS_FS::ReadFile()
{
	WCHAR *fileName1 = L"\\\\.\\PhysicalDrive0"; // \\.\PhysicalDrive0, \\.\PhysicalDrive1 � �. �.
	WCHAR *fileName2 = L"\\\\.\\C:"; // \\.\C:, \\.\D:

	HANDLE fileHandle = CreateFileW
		(
			fileName, // ��� ����� (WCHAR*)
			GENERIC_READ,	  // ����� �������
			FILE_SHARE_READ | FILE_SHARE_WRITE, // ����� ���������� ������
			NULL, // �������� ������������
			OPEN_EXISTING, // ������ ��������
			FILE_ATTRIBUTE_NORMAL, // ����� � ��������
			NULL // ��������� (�������������) ����� ������� � ������� ������� GENERIC_READ.
		);

	if(fileHandle == INVALID_HANDLE_VALUE)
		{
			Application->MessageBoxW(L"���������� ������� ����", L"", MB_OK);
		}

	BYTE *dataBuffer = new BYTE[2000];  // allocate memory

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	// ������ �������
	unsigned long currentPosition = SetFilePointer
			(
				fileHandle,
				sectorOffset.LowPart,
				&sectorOffset.HighPart,
				FILE_BEGIN // ����� � �����, ������������ ������� ���������� ����������������� (FILE_BEGIN, FILE_CURRENT, FILE_END)
			);

	if(currentPosition != sectorOffset.LowPart)
	{
		Application->MessageBoxW(L"���������� ������ �������", L"", MB_OK);
	}

	// ������ ������
	bool readResult = ReadFile
			(
				fileHandle,
				dataBuffer,
				bytesToRead,
				&bytesRead,
				NULL
			);

	if(!readResult || bytesRead != bytesToRead)
	{
		Application->MessageBoxW(L"���������� �������� ����", L"", MB_OK);
	}

	// ������� ����
	CloseHandle(fileHandle);

}

 int NTFS_FS::GetDiskInfo()
{


	return ClusterSize;
}



int NTFS_FS::GetClusterSize()
{
	int ClusterSize = 4096;

	return ClusterSize;
}

__int64 NTFS_FS::GetFileSystemSize()
{

	return FileSystemSize;
}


*/



	PDISKHANDLE OpenDisk(LPCTSTR disk)
{
	PDISKHANDLE tmpDisk;
	DWORD read;
	tmpDisk = new DISKHANDLE;
	memset(tmpDisk, 0, sizeof(DISKHANDLE));
	tmpDisk->fileHandle = CreateFile(disk, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (tmpDisk->fileHandle != INVALID_HANDLE_VALUE)
	{
		ReadFile(tmpDisk->fileHandle, &tmpDisk->NTFS.bootSector, sizeof(BOOT_BLOCK), &read, NULL);
		if (read==sizeof(BOOT_BLOCK))
		{
			if (strncmp("NTFS",(const char*) &tmpDisk->NTFS.bootSector.Format, 4)==0)
			{
				//tmpDisk->type = NTFSDISK;
				tmpDisk->NTFS.BytesPerCluster = tmpDisk->NTFS.bootSector.BytesPerSector * tmpDisk->NTFS.bootSector.SectorsPerCluster;
				tmpDisk->NTFS.BytesPerFileRecord = tmpDisk->NTFS.bootSector.ClustersPerFileRecord < 0x80 ? tmpDisk->NTFS.bootSector.ClustersPerFileRecord * tmpDisk->NTFS.BytesPerCluster: 1 <<(0x100 - tmpDisk->NTFS.bootSector.ClustersPerFileRecord);

				tmpDisk->NTFS.complete = FALSE;
				tmpDisk->NTFS.MFTLocation.QuadPart = tmpDisk->NTFS.bootSector.MftStartLcn * tmpDisk->NTFS.BytesPerCluster;
				tmpDisk->NTFS.MFT = NULL;
				tmpDisk->IsLong = FALSE;
				tmpDisk->NTFS.sizeMFT = 0;
			}
			else
			{

				//tmpDisk->type = UNKNOWN;
				//tmpDisk->lFiles = NULL;
				Application->MessageBoxW(L"�� ������� ������� ����", L"", MB_OK);
			}
		}
		return tmpDisk;
	}

	delete tmpDisk;
	return NULL;
};







