//---------------------------------------------------------------------------

#ifndef FileSystemH
#define FileSystemH

typedef struct {
	UCHAR Jump[3];
	UCHAR Format[8];
	USHORT BytesPerSector;
	UCHAR SectorsPerCluster;
	USHORT BootSectors;
	UCHAR Mbz1;
	USHORT Mbz2;
	USHORT Reserved1;
	UCHAR MediaType;
	USHORT Mbz3;
	USHORT SectorsPerTrack;
	USHORT NumberOfHeads;
	ULONG PartitionOffset;
	ULONG Rserved2[2];
	ULONGLONG TotalSectors;
	ULONGLONG MftStartLcn;
	ULONGLONG Mft2StartLcn;
	ULONG ClustersPerFileRecord;
	ULONG ClustersPerIndexBlock;
	ULONGLONG VolumeSerialNumber;
	UCHAR Code[0x1AE];
	USHORT BootSignature;
}BOOT_BLOCK, *PBOOT_BLOCK;


 class NTFS_FS
{
private:
	int ClusterSize;
	__int64 Size;
	wstring FileName;      	//путь к файлу или диску
	WCHAR *FileName;

public:

	NTFS_FS();		//конструктор класса

	int GetClusterSize();		// набор внешних данных - интерфейс класса
	__int64 GetFileSystemSize();
	intReadCluster(BYTE *outData);



};


//---------------------------------------------------------------------------
#endif
