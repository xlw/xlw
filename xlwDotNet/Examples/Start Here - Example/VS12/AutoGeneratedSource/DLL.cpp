#include <xlwDotNet.h>
using namespace System;
using namespace Runtime::InteropServices;
using namespace xlwDotNet;

inline std::wstring CLR2WCPP(String^ clrString) {
    System::IntPtr memHandle = Marshal::StringToHGlobalUni(clrString);
    std::wstring result =  (const wchar_t*)(memHandle.ToPointer());
    Marshal::FreeHGlobal(memHandle);
    return result;
}

std::wstring // tests empty args 
DLLEXPORT EmptyArgFunction()
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::EmptyArgFunction(
        )));
DOT_NET_EXCEL_END
}

short // echoes a short 
DLLEXPORT EchoShort(short x)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::EchoShort(
                x
        );
DOT_NET_EXCEL_END
}

MyMatrix // echoes a matrix
DLLEXPORT EchoMat(const MyMatrix& Echoee)
{
DOT_NET_EXCEL_BEGIN
        return *(MyMatrix*)(xlwTypes::MyMatrix::getInner(Example::Class1::EchoMat(
                gcnew xlwTypes::MyMatrix(IntPtr((void*)& Echoee))
        )));
DOT_NET_EXCEL_END
}

MyArray // echoes an array
DLLEXPORT EchoArray(const MyArray& Echoee)
{
DOT_NET_EXCEL_BEGIN
        return *(MyArray*)(xlwTypes::MyArray::getInner(Example::Class1::EchoArray(
                gcnew xlwTypes::MyArray(IntPtr((void*)& Echoee))
        )));
DOT_NET_EXCEL_END
}

CellMatrix // echoes a  CellMatrix
DLLEXPORT EchoCells(const CellMatrix& Echoee)
{
DOT_NET_EXCEL_BEGIN
        return *(CellMatrix*)(xlwTypes::CellMatrix::getInner(Example::Class1::EchoCells(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& Echoee))
        )));
DOT_NET_EXCEL_END
}

double // computes the circumference of a circle 
DLLEXPORT Circ(double Diameter)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::Circ(
                Diameter
        );
DOT_NET_EXCEL_END
}

std::wstring // Concatenates two strings
DLLEXPORT Concat(const std::wstring& str1,const std::wstring& str2)
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::Concat(
                gcnew String(str1.c_str()),
                gcnew String(str2.c_str())
        )));
DOT_NET_EXCEL_END
}

MyArray // computes mean and variance of a range 
DLLEXPORT stats(const MyArray& data)
{
DOT_NET_EXCEL_BEGIN
        return *(MyArray*)(xlwTypes::MyArray::getInner(Example::Class1::stats(
                gcnew xlwTypes::MyArray(IntPtr((void*)& data))
        )));
DOT_NET_EXCEL_END
}

std::wstring // says hello name
DLLEXPORT HelloWorldAgain(const std::wstring& name)
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::HelloWorldAgain(
                gcnew String(name.c_str())
        )));
DOT_NET_EXCEL_END
}

unsigned long // echoes an unsigned integer
DLLEXPORT EchoUL(unsigned long b)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::EchoUL(
                b
        );
DOT_NET_EXCEL_END
}

int // Echoes an integer
DLLEXPORT EchoInt(int b)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::EchoInt(
                b
        );
DOT_NET_EXCEL_END
}

double // tests DoubleOrNothingType
DLLEXPORT EchoDoubleOrNothing(const CellMatrix& x,double defaultValue)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::EchoDoubleOrNothing(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& x)),
                defaultValue
        );
DOT_NET_EXCEL_END
}

double // system clock
DLLEXPORT SystemTime(const CellMatrix& ticksPerSecond)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::SystemTime(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& ticksPerSecond))
        );
DOT_NET_EXCEL_END
}

CellMatrix // echoes arg list
DLLEXPORT EchoArgList(const ArgumentList& args)
{
DOT_NET_EXCEL_BEGIN
        return *(CellMatrix*)(xlwTypes::CellMatrix::getInner(Example::Class1::EchoArgList(
                gcnew xlwTypes::ArgumentList(IntPtr((void*)& args))
        )));
DOT_NET_EXCEL_END
}

double // evaluate pay--off
DLLEXPORT PayOffEvaluation(const CellMatrix& OptionPayoff,double Spot)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::PayOffEvaluation(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& OptionPayoff)),
                Spot
        );
DOT_NET_EXCEL_END
}

bool // checks to see if there's an error
DLLEXPORT ContainsError(const CellMatrix& input)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::ContainsError(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& input))
        );
DOT_NET_EXCEL_END
}

bool // checks to see if there's a div by zero
DLLEXPORT ContainsDivByZero(const CellMatrix& input)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::ContainsDivByZero(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& input))
        );
DOT_NET_EXCEL_END
}

double // Gets the thread id
DLLEXPORT GetThreadId()
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::GetThreadId(
        );
DOT_NET_EXCEL_END
}

std::wstring // return a string indicating datatype of OPER/OPER12 input
DLLEXPORT typeString(const CellMatrix& input)
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::typeString(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& input))
        )));
DOT_NET_EXCEL_END
}

std::wstring // return a string indicating datatype of XLOPER/XLOPER12 input
DLLEXPORT typeString2(const CellMatrix& input)
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::typeString2(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)& input))
        )));
DOT_NET_EXCEL_END
}

MyArray // takes double[]
DLLEXPORT CastToCSArray(const MyArray& csarray)
{
DOT_NET_EXCEL_BEGIN
        return *(MyArray*)(xlwTypes::MyArray::getInner(Example::Class1::CastToCSArray(
                gcnew xlwTypes::MyArray(IntPtr((void*)& csarray))
        )));
DOT_NET_EXCEL_END
}

MyArray // takes double[]
DLLEXPORT CastToCSArrayTwice(const MyArray& csarray)
{
DOT_NET_EXCEL_BEGIN
        return *(MyArray*)(xlwTypes::MyArray::getInner(Example::Class1::CastToCSArrayTwice(
                gcnew xlwTypes::MyArray(IntPtr((void*)& csarray))
        )));
DOT_NET_EXCEL_END
}

MyMatrix // takes double[,]
DLLEXPORT CastToCSMatrix(const MyMatrix& csmatrix)
{
DOT_NET_EXCEL_BEGIN
        return *(MyMatrix*)(xlwTypes::MyMatrix::getInner(Example::Class1::CastToCSMatrix(
                gcnew xlwTypes::MyMatrix(IntPtr((void*)& csmatrix))
        )));
DOT_NET_EXCEL_END
}

MyMatrix // takes double[,]
DLLEXPORT CastToCSMatrixTwice(const MyMatrix& csmatrix)
{
DOT_NET_EXCEL_BEGIN
        return *(MyMatrix*)(xlwTypes::MyMatrix::getInner(Example::Class1::CastToCSMatrixTwice(
                gcnew xlwTypes::MyMatrix(IntPtr((void*)& csmatrix))
        )));
DOT_NET_EXCEL_END
}

double // throws an exception of type ArgumentNullException
DLLEXPORT throwString(const std::wstring& err)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::throwString(
                gcnew String(err.c_str())
        );
DOT_NET_EXCEL_END
}

double // throws an exception of type cellMatrixException
DLLEXPORT throwCellMatrix(const std::wstring& err)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::throwCellMatrix(
                gcnew String(err.c_str())
        );
DOT_NET_EXCEL_END
}

double // makes the C Runtime throw an exception
DLLEXPORT throwCError(const std::wstring& err)
{
DOT_NET_EXCEL_BEGIN
        return Example::Class1::throwCError(
                gcnew String(err.c_str())
        );
DOT_NET_EXCEL_END
}

CellMatrix // Obtains historial market data from yahoo
DLLEXPORT GetHistoricDataFromYahoo(const std::wstring& symbol,double beginDate,double endDate)
{
DOT_NET_EXCEL_BEGIN
        return *(CellMatrix*)(xlwTypes::CellMatrix::getInner(Example::Historic::GetHistoricDataFromYahoo(
                gcnew String(symbol.c_str()),
                beginDate,
                endDate
        )));
DOT_NET_EXCEL_END
}

