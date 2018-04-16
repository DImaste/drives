//---------------------------------------------------------------------------

#ifndef PatternsH
#define PatternsH
//---------------------------------------------------------------------------
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>

#include "NTFS.h"
#include "FAT.h"
#include "exFAT.h"

using namespace std;

//---------------------------------------------------------------------------

typedef vector <BYTE> ClusterDisk;

 // Template Iterator

  template <class Type>
class Iterator
{
protected:

public:
	Iterator()  {};
	virtual ~Iterator()  {};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Type GetCurrent() = 0;
	//virtual int GetCurrentIndex() const = 0;
} ;

//---------------------------------------------------------------------------


//Iterator Class
template <class Type>
  class DriveIterator : public Iterator <Type>
{
private:

public:
	DriveIterator() {};
	~DriveIterator() {} ;
	virtual void First()=0;
	virtual void Next()=0;
	virtual bool IsDone() const =0 ;
	virtual Type GetCurrent()=0;
	virtual int GetCurrentIndex() const =0;

} ;

//---------------------------------------------------------------------------


class NTFSIterator : public DriveIterator <ClusterDisk>
{
private:
	NTFS_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	NTFSIterator(NTFS_FS *fs);
	~NTFSIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------

class FATIterator : public DriveIterator <ClusterDisk>
{
private:
	FAT_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	FATIterator(FAT_FS *fs);
	~FATIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------

class exFATIterator : public DriveIterator <ClusterDisk>
{
private:
	exFAT_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	exFATIterator(exFAT_FS *fs);
	~exFATIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;


//---------------------------------------------------------------------------
//Decorator Class

class DriveDecorator : public DriveIterator <ClusterDisk>
{
protected:
	int BeginCluster;
	int EndCluster;
	DriveIterator <ClusterDisk> *It;

public:

	DriveDecorator(DriveIterator <ClusterDisk> * it, int beginCluster, int endCluster);

	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------
#endif
