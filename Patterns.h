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

#include <iostream>
using namespace std;




//---------------------------------------------------------------------------
#endif




 template <class Type> class Iterator
{
	protected:


	public:
        Iterator() {}
		virtual ~Iterator() {}
		virtual void First() = 0; //первый элемент
		virtual void Next() = 0;
		virtual bool IsDone(); //const =0;
		virtual Type GetCurrent(); //const = 0;
} ;


class ArrayIterator : public Iterator <int>  //исходный код не пишут в заголовочном файле здесь просто наглядно
{
	   // typedef Iterator <BYTE> Parent;
protected:
	   int totalClusters;
	   int index;

public:
		ArrayIterator(int Index ,int TotalClusters) ;
		~ArrayIterator() {}
		void First();
		void Next();
		bool IsDone();
		int GetCurrent();

}   ;