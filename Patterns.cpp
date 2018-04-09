//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------

#include "Patterns.h"
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
#pragma package(smart_init)

ArrayIterator::ArrayIterator(int Index,int TotalClusters)
 {
	index = Index;
	totalClusters=TotalClusters;

 }

 void ArrayIterator::First()
 {
   index=0;
 }

void ArrayIterator::Next()
 {
   index++;
 }

 bool  ArrayIterator::IsDone()
 {
   return (index>=totalClusters);
 }

 int  ArrayIterator::GetCurrent()
 {
   return index;
 }
