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
		virtual void First() = 0; //������ �������
		virtual void Next() = 0;
		virtual bool IsDone() const =0;
		virtual Type GetCurrent() const = 0;
}


class ArrayIterator : public Iterator <BYTE> //�������� ��� �� ����� � ������������ ����� ����� ������ ��������
{
private:

		BYTE *Container;  //��������� �� ������ ����������
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
		virtual void First() {CurrentIndex=0; } //������ ���������
		virtual void Next()  {CurrentIndex++; }
		virtual bool IsDone() const {return (CurrentIndex>=�ontainerSize);}	//������� ���������� isdone, ����� ������� ������� �������
		virtual BYTE GetCurrent() {return Container(CurrentIndex);}

}