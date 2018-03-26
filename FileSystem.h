//---------------------------------------------------------------------------

#ifndef FileSystemH
#define FileSystemH

//---------------------------------------------------------------------------
#endif

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Main.h"



#pragma pack(push,1)


typedef struct
{

	BYTE Jump[3];
	BYTE OEMID[8];
	UINT16 BytesPerSector;
	BYTE SectorsPerCluster;
	BYTE padding1[2];
	BYTE padding2[5];
	BYTE typeStore;
	BYTE padding3[2];
	BYTE padding4[8];
	BYTE padding5[4];
	BYTE padding6[4];
	ULONGLONG TotalSectors;
	ULONGLONG MftStartLcn;
	ULONGLONG Mft2StartLcn;
	BYTE sizeMFT;
	BYTE padding7[3];
	BYTE sizeIndex;
	BYTE padding8[3];
	ULONGLONG VolumeSerialNumber;
	BYTE padding9[ 4 ];
	BYTE padding10[ 426 ];
	BYTE Checksum[ 2 ];


	/*        //NOT ALL THE RECORD :(
	UCHAR Jump[3];       // 0x00 for what?
	ULONGLONG OEMID[8];     // 0x03
	UINT16 BytesPerSector;    //0x0B - 0x0002
	BYTE SectorsPerCluster;  // 0x0D - 0x08
	WORD ReservedSectors;   // 0x0E - 0x0000
	BYTE MediaDescriptor;   //  0x15 - 0xF8
	WORD SectorsPerTrack;  // 0x18 - 0x0000
	WORD NumberOfHeads;  //0x1A - 0xFF00
	ULONGLONG TotalSectors; // 0x28 - 0x4AF57F0000000000
	ULONGLONG MftStartLcn;   // 0x30 - 0x0400000000000000
	ULONGLONG Mft2StartLcn;   // 0x38 - 0x54FF070000000000
	DWORD ClustersPerFileRecord; //0x40 - 0xF6000000
	BYTE ClustersPerIndexBlock; //0x44 - 0x01
	ULONGLONG VolumeSerialNumber;   // 0x48 - 0x14A51B74C91B741C
	DWORD Checksum; //0x50 - 0x00000000    */
}BOOT_BLOCK;

#pragma pack(pop)

 class NTFS_FS
{
protected:
	HANDLE fileHandle;
	UINT16 BytesPerSector;
	BYTE SectorPerCluster;
	ULONGLONG TotalSectors;
	BYTE OEMID[9];

private:

	BOOT_BLOCK* infoNTFS;
	int ClusterSize;
	__int64 Size;

public:
	bool result;
	NTFS_FS()	;  	//конструктор класса
	bool ReadBootBlock();
	bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer);
	HANDLE NTFS_FS::GetFileHandle();
	UINT16 NTFS_FS::GetBytesPerSector();
	BYTE* NTFS_FS::GetOEMName();
	BYTE NTFS_FS::GetSectorPerCluster();
	ULONGLONG NTFS_FS::GetTotalSectors();
	void NTFS_FS::SetFileHandle(HANDLE FileSystemHandle);

};

class Container
{
//public
// bool result;

};





