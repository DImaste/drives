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
	WCHAR *fileName1 = L"\\\\.\\PhysicalDrive0"; // \\.\PhysicalDrive0, \\.\PhysicalDrive1 и т. д.
	WCHAR *fileName2 = L"\\\\.\\C:"; // \\.\C:, \\.\D:

	HANDLE fileHandle = CreateFileW
		(
			fileName, // Имя файла (WCHAR*)
			GENERIC_READ,	  // Режим доступа
			FILE_SHARE_READ | FILE_SHARE_WRITE, // Режим совместной работы
			NULL, // Атрибуты безопасности
			OPEN_EXISTING, // Способ открытия
			FILE_ATTRIBUTE_NORMAL, // Флаги и атрибуты
			NULL // Описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ.
		);

	if(fileHandle == INVALID_HANDLE_VALUE)
		{
			Application->MessageBoxW(L"Невозможно открыть файл", L"", MB_OK);
		}

	BYTE *dataBuffer = new BYTE[2000];  // allocate memory

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	// Задать позицию
	unsigned long currentPosition = SetFilePointer
			(
				fileHandle,
				sectorOffset.LowPart,
				&sectorOffset.HighPart,
				FILE_BEGIN // Точка в файле, относительно которой необходимо позиционироваться (FILE_BEGIN, FILE_CURRENT, FILE_END)
			);

	if(currentPosition != sectorOffset.LowPart)
	{
		Application->MessageBoxW(L"Невозможно задать позицию", L"", MB_OK);
	}

	// Чтение данных
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
		Application->MessageBoxW(L"Невозможно прочесть файл", L"", MB_OK);
	}

	// Закрыть файл
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






