//---------------------------------------------------------------------------

#ifndef PatternsH
#define PatternsH
//---------------------------------------------------------------------------
#include <windows.h>
#include "FileSystem.h"
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
#endif


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
	virtual int GetCurrentIndex() const = 0;
} ;

//Iterator Class

  class DriveIterator : public Iterator < ClusterDisk >
{
private:
	NTFS_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	DriveIterator(NTFS_FS* fs);
	virtual ~DriveIterator();
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const ;
	virtual ClusterDisk GetCurrent();
	virtual int GetCurrentIndex() const ;

} ;

//Template Decorator

template <class Type>
class Decorator : public Iterator <Type>
{
protected:
	Iterator <Type> *It;
	Decorator() {};

public:
	Decorator(Iterator <Type> * it) {It = it;}
	virtual ~Decorator() { delete It;}
	virtual void First()  { It->First(); }
	virtual void Next()  {	It->Next();}
	virtual bool IsDone() const  {return It->IsDone();}
	virtual Type GetCurrent()  {return It->GetCurrent();}
	virtual int GetCurrentIndex() const {return It->GetCurrentIndex();}
} ;

//Decorator Class

class DriveDecorator : public Decorator <ClusterDisk>
{
protected:
	int BeginCluster;
	int EndCluster;

public:
	DriveDecorator(DriveIterator * it, int beginCluster, int endCluster);

	//virtual ~DriveDecorator();
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const ;
	virtual ClusterDisk GetCurrent();
	virtual int GetCurrentIndex() const ;
} ;


