//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemClass.h"
#include "NTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemClass *FileSystemClass::CreateFileSystem(UnicodeString diskPath,FSType fsType)
{
	switch (fsType)
	{
			case NTFS: return new NTFS_FS(/*diskPath*/);
	}
}








