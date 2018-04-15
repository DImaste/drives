//---------------------------------------------------------------------------

#ifndef FileSystemClassH
#define FileSystemClassH

#include <windows.h>
#include "Main.h"
#include <string>
#include <vector>
#include <list>
#include "Patterns.h"
#include "NTFS.h"


//---------------------------------------------------------------------------

//typedef vector <BYTE> ClusterDisk;


typedef enum FSType
{
	NTFS
} FSTypes;

class FileSystemClass
{
	protected:
		HANDLE fileHandle;
		UINT16 BytesPerSector;
		BYTE SectorPerCluster;
		ULONGLONG TotalSectors;
		BYTE OEMID[9];
		//WCHAR* path;

	public :

		FileSystemClass(UnicodeString diskPath) ;
		~FileSystemClass() {};
		//FileSystemClass *DestroyFileSystem(HANDLE FileSystemHandle);

		static FileSystemClass *CreateFileSystem(FSType fsType);
		virtual DriveIterator <ClusterDisk> * GetClusterIterator()=0;
		virtual bool ReadBootBlock() const=0;
		virtual bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer) const=0;

		void DestroyFileSystem(HANDLE FileSystemHandle);
		int GetFirstCluster() = 0;
		HANDLE GetFileHandle()=0;
		UINT16 GetBytesPerSector()=0;
		BYTE* GetOEMName()=0;
		BYTE GetSectorPerCluster()=0;
		ULONGLONG GetTotalSectors()=0;
		void SetFileHandle(HANDLE FileSystemHandle)=0;
} ;


#endif
