//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemClass.h"
#include "NTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemClass *FileSystemClass::CreateFileSystem(UnicodeString diskPath,FSType fsType)
{
	FileSystemClass * FS;
	switch (fsType)
	{
			case NTFS: FS = new NTFS_FS(/*diskPath*/);
			break;
            case FAT: FS = new FAT_FS(/*diskPath*/);
			break;



			return FS;

	}
}








