//---------------------------------------------------------------------------

#ifndef PatternIteratorH
#define PatternIteratorH
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
 typedef vector < BYTE > ClusterDisk;


  template < class Type >
class Iterator
{
protected:

public:
	Iterator( )  {};
	virtual ~Iterator( )  {};
	virtual void First( ) = 0;
	virtual void Next( ) = 0;
	virtual bool IsDone( ) const = 0;
	virtual Type GetCurrent( ) = 0;
	virtual int GetCurrentIndex( ) const = 0;
} ;


  class NTFSClusterIterator : public Iterator < ClusterDisk >
{
private:
	NTFS_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	NTFSClusterIterator(NTFS_FS* fs);
	virtual ~NTFSClusterIterator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;

} ;



 /*


 template <class Type> class Iterator
{
	protected:
		Iterator() {};

	public:

		virtual ~Iterator() {} ;
		virtual void First() = 0; //первый элемент
		virtual void Next() = 0;
		virtual bool IsDone() =0; //const =0;
		virtual void GetCurrent(Type *buffer); //const = 0;
} ;


class ArrayIterator : public Iterator <BYTE>  //исходный код не пишут в заголовочном файле здесь просто наглядно
{

protected:

public:
		ArrayIterator(NTFS_FS* Fs);
		~ArrayIterator() {};
		void First();
		void Next();
		bool IsDone();
		void GetCurrent(BYTE *buffer);
		__int64 GetCurrentIndex() {return index;};

private:
		NTFS_FS *fs;
		__int64 container_size;
		__int64 index;
		int CurrentCluster;
		int BytesPerCluster;
		BYTE * DataBuffer;

}   ;*/

template < class Type >
class IteratorDecorator : public Iterator < Type >
{
protected:
	Iterator < Type > *It;
	IteratorDecorator( ) {};

public:
	IteratorDecorator( Iterator < Type > * it ) {It = it;}
	virtual ~IteratorDecorator( ) { delete It;}
	virtual void First( )  { It->First( ); }
	virtual void Next( )  {	It->Next( );}
	virtual bool IsDone( ) const  {return It->IsDone( );}
	virtual Type GetCurrent( )  {return It->GetCurrent( );}
	virtual int GetCurrentIndex( ) const {return It->GetCurrentIndex( );}
} ;

class NTFSDecorator : public IteratorDecorator < ClusterDisk >
{
protected:
	int BeginCluster;
	int EndCluster;

public:
	NTFSDecorator(
		NTFSClusterIterator * it,
		int                   beginCluster,
		int                   endCluster );

	virtual ~NTFSDecorator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;
} ;


