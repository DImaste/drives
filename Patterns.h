//---------------------------------------------------------------------------

#ifndef PatternsH
#define PatternsH
//---------------------------------------------------------------------------
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Main.h"
#include <string>
#include <vector>
#include <list>
#include <stdio.h>




//---------------------------------------------------------------------------
#endif




 template <class Type> class Iterator
{
	protected:
		Iterator() {}

	public:
		virtual ~Iterator() {}
		virtual void First() = 0; //первый элемент
		virtual void Next() = 0;
		virtual bool IsDone() const =0;
		virtual Type GetCurrent() const = 0;
}


class ArrayIterator : public Iterator <BYTE> //исходный код не пишут в заголовочном файле здесь просто наглядно
{
private:

		BYTE *Container;  //указывает на начало контейнера
		int ContainerSize;
		int CurrentIndex;

public:
		ArrayIterator(BYTE *container, int containerSize)
		{
		Container=container;
		ContainerSize=containerSize;
		CurrentIndex=0;
		}
		~ArrayIterator() {}
		virtual void First() {CurrentIndex=0; } //первый элементам
		virtual void Next()  {CurrentIndex++; }
		virtual bool IsDone() const {return (CurrentIndex>=СontainerSize);}	//функция возвращает isdone, когда перешел границу массива
		virtual BYTE GetCurrent() {return Container(CurrentIndex);}

}