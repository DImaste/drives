//---------------------------------------------------------------------------

#ifndef PatternsH
#define PatternsH
//---------------------------------------------------------------------------
#include <windows.h>
#include "NTFS.h"
#include "FileSystemClass.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>

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
  class DriveIterator : public Iterator <ClusterDisk>
{
private:
	//FileSystemClass *FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	DriveIterator(/*FileSystemClass *FileSystem;*/);
	~DriveIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;

} ;

//---------------------------------------------------------------------------

// MAYBE Its wrong Inheritance
class NTFSIterator : public DriveIterator
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
//Decorator Class

class DriveDecorator : public DriveIterator
{
protected:
	int BeginCluster;
	int EndCluster;
	DriveIterator *It;

public:

	DriveDecorator(DriveIterator * it, int beginCluster, int endCluster);

	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------
#endif
