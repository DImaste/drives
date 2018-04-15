//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemClass.h"
#include "NTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemClass::FileSystemClass(UnicodeString diskPath)
{

	fileHandle = CreateFileW(diskPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
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

FileSystemClass *FileSystemClass::CreateFileSystem(FSType fsType)
{
	switch (fsType)
	{
			case NTFS: return new NTFS_FS(/*diskPath*/);

	}
}

// ---------------------------------------------------------------------------
ULONGLONG FileSystemClass::GetTotalClusters( )
{
	return TotalClusters;
}

// ---------------------------------------------------------------------------
UINT32 FileSystemClass::GetBytesPerCluster( )
{
	return BytesPerCluster;
}

// ---------------------------------------------------------------------------
BYTE* NTFS_FS::GetOEMName()
{
	return OEMID;
}

// ---------------------------------------------------------------------------

UINT32 FileSystemClass::GetFirstCluster( )
{
	return BeginCluster;
}







