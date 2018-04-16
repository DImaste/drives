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

//typedef vector <BYTE> ClusterDisk;


enum FSType
{
	NTFS,
	FAT,
	exFAT

};



class FileSystemClass
{
	public :

		FileSystemClass() {};
		~FileSystemClass() {};

		static FileSystemClass *CreateFileSystem(UnicodeString diskPath,FSType fsType);

		virtual DriveIterator <ClusterDisk> * GetClusterIterator()=0;
		virtual bool ReadBootBlock() const=0;
		virtual bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer) const=0;
		virtual void DestroyFileSystem(HANDLE FileSystemHandle);
		virtual int GetFirstCluster() = 0;
		virtual HANDLE GetFileHandle()=0;
		virtual UINT16 GetBytesPerSector()=0;
		virtual BYTE* GetOEMName()=0;
		virtual BYTE GetSectorPerCluster()=0;
		virtual ULONGLONG GetTotalSectors()=0;
		virtual void SetFileHandle(HANDLE FileSystemHandle)=0;
} ;


#endif
