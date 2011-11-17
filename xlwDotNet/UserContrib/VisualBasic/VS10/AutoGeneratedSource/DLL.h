#ifndef DLL_H
#define DLL_H

#define ERRCELLS_NOT_REQUIRED

#include <xlwDotNet.h>

//<xlw:libraryname=Template


std::wstring // Hello World
HelloWorld();

CellMatrix // Echo a matrix
EchoMatrix(const CellMatrix& theMatrix // Matrix
);

#endif 
