//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystem.h"
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

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



int NTFS_FS::GetClusterSize()
{
	int ClusterSize = 4096;

	return ClusterSize;
}

__int64 NTFS_FS::GetFileSystemSize()
{

	return FileSystemSize;
}






