//---------------------------------------------------------------------------

#ifndef FileSystemClassH
#define FileSystemClassH

#include <windows.h>
#include "Main.h"
#include <string>
#include <vector>
#include <list>
#include "Patterns.h"

//---------------------------------------------------------------------------


typedef enum
{
	NTFS,

}FSType;

class FileSystemClass
{
	public :

		static FileSystemClass *CreateFileSystem(wstring diskPath,FSType fsType);
		static FileSystemClass *DestroyFileSystem(HANDLE FileSystemHandle);

		virtual Iterator<ClusterDisk> *GetClusterIterator()=0;
		virtual bool result const;
		virtual bool ReadBootBlock() const;
		virtual bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer) const;
		virtual HANDLE GetFileHandle()=0;
		virtual UINT16 GetBytesPerSector()=0;
		virtual BYTE* GetOEMName()=0;
		virtual BYTE GetSectorPerCluster()=0;
		virtual ULONGLONG GetTotalSectors()=0;
		virtual void SetFileHandle(HANDLE FileSystemHandle)=0;



} ;













#endif
