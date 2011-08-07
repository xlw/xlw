/*
 Copyright (C) 2011 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/xlw.h>
#include <xlw/XlOpenClose.h>
#include <xlw/xlarray.h>
#include <algorithm>

using namespace xlw;
///////////////////////////////////////////////////////////////////////////////
// list of function pointers to hold fortran functions
///////////////////////////////////////////////////////////////////////////////

int (__cdecl *dpotrf)(char* uplo, int* n, double* a, int* lda, int* info) = 0;
double (__cdecl *ddot)(int* n, double* x, int* incx, double* y, int* incy) = 0;
int (__cdecl *dgetrf)(int* m, int* n, double* a, int* lda, int* ipiv, int* info) = 0;
int (__cdecl *dgetri)(int* n, double* a, int* lda, int* ipiv, double* work, int* lwork, int* info) = 0;
void (__cdecl *dgemm)(char* transa, char* transb, int* m, int* n, int* k, double* alpha, double* a, int* lda, double* b, int* ldb, double* beta, double* c, int* ldc) = 0;

///////////////////////////////////////////////////////////////////////////////
// helper code to find functions in dlls
///////////////////////////////////////////////////////////////////////////////

namespace
{
    //
    // name transforms
    //
    // There are many posible ways of exporting the BLAS/LAPACK
    // function from a dll and each of the library vendors seems to
    // use a slightly different one.
    //
    // here we support sticking a prefix and suffix on the name as well as
    // changing the case to all uppercase
    class NameTransform
    {
    public:
        NameTransform(const std::string& prefix, const std::string& suffix, bool uppercase = false) :
                prefix_(prefix),
                suffix_(suffix),
                uppercase_(uppercase)
        {
        }
        std::string operator()(const std::string& nameToTransform)
        {
            if(uppercase_)
            {
                return prefix_ + StringUtilities::toUpper(nameToTransform) + suffix_;
            }
            else
            {
                return prefix_ + StringUtilities::toLower(nameToTransform) + suffix_;
            }
        }
    private:
        std::string prefix_;
        std::string suffix_;
        bool uppercase_;
    };

    // Function Finder
    // This class first searches a directory for a list of dlls
    // and then for a given string name will search each of the 
    // dlls for each of the different types of export manglings
    // we support
    class FunctionFinder
    {
    public:
        typedef xlw_tr1::shared_ptr<NameTransform> NameTransformPtr;
        FunctionFinder()
        {
            // The supported libraries use the following different methods:
            //
            // 1) Intel's MKL custom : upper case
            //
            // 2) ATI ACML: Fortran functions as upper case (note C function 
            //    variants are also exported as lower case)
            //
            // 3) Native: functions exported as lower case with underline at the end
            //
            // So for each function we need to try the following exports in order
            // 1) All uppercase
            // 2) All lowercase with underline at end
            // 3) All lowercase
            // 4) All uppercase with underscrore at end
            functionNameTransforms_.push_back(NameTransformPtr(new NameTransform("","", true)));
            functionNameTransforms_.push_back(NameTransformPtr(new NameTransform("","_")));
            functionNameTransforms_.push_back(NameTransformPtr(new NameTransform("","")));
            functionNameTransforms_.push_back(NameTransformPtr(new NameTransform("","_", true)));
        }

        ~FunctionFinder()
        {
            std::for_each(dllInstances_.begin(), dllInstances_.end(), FreeLibrary);
        }

        // search for all dll's in the directory 
        // using win32 api
        void findPossibleDlls(const std::string& directory)
        {
            // set the current directory to the directory being searched
            // so that dlls dependent on others in th edirectory load
            // properly
            std::string oldCurentDirectory(StringUtilities::getCurrentDirectory());
            SetCurrentDirectory(directory.c_str());
            std::string searchPath(directory + "\\*.dll");
            WIN32_FIND_DATA findData;
            HANDLE findHandle = FindFirstFile(searchPath.c_str(), &findData);
            BOOL carryOn(findHandle != INVALID_HANDLE_VALUE);
            while(carryOn)
            {
                std::string fullFileName(directory + "\\");
                fullFileName += findData.cFileName;
                HINSTANCE dllInstance = LoadLibrary(fullFileName.c_str());
                if(dllInstance)
                {
                    dllInstances_.push_back(dllInstance);
                }
                carryOn = FindNextFile(findHandle, &findData);
            }
            FindClose(findHandle);
            // be tidy, set back the directory to what it was afterwards
            SetCurrentDirectory(oldCurentDirectory.c_str());
        }
        
        FARPROC findFunction(std::string functionToFind)
        {
            for(size_t i(0); i < functionNameTransforms_.size(); ++i)
            {
                std::string functionName(functionNameTransforms_[i]->operator ()(functionToFind));
                FARPROC pfn = findTransformedFunction(functionName);
                if(pfn)
                {
                    return pfn;
                }
            }
            return 0;
        }
    private:
        FARPROC findTransformedFunction(const std::string& functionName)
        {
            for(size_t i(0); i < dllInstances_.size(); ++i)
            {
                FARPROC pfn = GetProcAddress(dllInstances_[i], functionName.c_str());
                if(pfn)
                {
                    return pfn;
                }
            }
            return 0;
        }
        std::vector<HINSTANCE> dllInstances_;
        std::vector<NameTransformPtr> functionNameTransforms_;
    };

    static FunctionFinder functionFinder;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation code
///////////////////////////////////////////////////////////////////////////////
static void findAFunction(std::pair<std::string, FARPROC*> functionToFind)
{
    FARPROC pfn = functionFinder.findFunction(functionToFind.first);
    *functionToFind.second = pfn;
}

void loadDynamicFunctions()
{
    std::map<std::string, FARPROC*> functionPointers;
    functionPointers["dpotrf"] = (FARPROC*)&dpotrf;
    functionPointers["ddot"] = (FARPROC*)&ddot;
    functionPointers["dgemm"] = (FARPROC*)&dgemm;
    functionPointers["dgetrf"] = (FARPROC*)&dgetrf;
    functionPointers["dgetri"] = (FARPROC*)&dgetri;

    std::string dllDir(StringUtilities::getEnvironmentVariable("FORTRAN_DLL_DIR"));
    if(dllDir.empty())
    {
        dllDir = XlfExcel::Instance().GetXllDirectory();
    }
    functionFinder.findPossibleDlls(dllDir);

    std::for_each(functionPointers.begin(), functionPointers.end(), findAFunction);
}

// Registers loadDynamicFunctions() to be executed by xlAutoOpen
namespace 
{
    MacroCache<Open>::MacroRegistra load_registra("loadDynamicFunctions","loadDynamicFunctions",loadDynamicFunctions);
}

///////////////////////////////////////////////////////////////////////////////
// Wrapper code
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    LPXLARRAY EXCEL_EXPORT fortran_cholesky(LPXLARRAY sym)
    {
        EXCEL_BEGIN;
        if(!dpotrf)
        {
            throw "dportf not found in any dlls";
        }
        int rows;
        int cols;
        double* arrayData;
        extractArrayInfo(sym, rows, cols, arrayData);
        if(rows != cols)
        {
            throw "not a square matrix";
        }

        char lower('L');
        int error(0);

        // The arrays come in in row major order and fortran
        // wants column major, luckily for
        // a symetric matrix this makes no difference.
        // We want the answer as the upper matrix but we ask
        // for the transpose of that to avoid having to switch ourselves
        dpotrf(&lower, &rows, arrayData, &rows, &error);
        if(error)
        {
            throw "dportf failed";
        }

        // Zero out the lower diagonal part of the result
        for(int i(1); i < rows; ++i)
        {
            memset(arrayData + i * rows, 0, sizeof(double) * i);
        }
        return sym;
        EXCEL_END_ARRAY;
    }

    LPXLFOPER EXCEL_EXPORT fortran_inner(LPXLARRAY x, LPXLARRAY y)
    {
        EXCEL_BEGIN;
        if(!ddot)
        {
            throw "ddot not found in any dlls";
        }
        
        int rowsx;
        int colsx;
        double* arrayDatax;
        extractArrayInfo(x, rowsx, colsx, arrayDatax);
        if(rowsx != 1 && colsx != 1)
        {
            throw "x not a vector";
        }

        int rowsy;
        int colsy;
        double* arrayDatay;
        extractArrayInfo(y, rowsy, colsy, arrayDatay);
        if(rowsy != 1 && colsy != 1)
        {
            throw "y not a vector";
        }

        if(rowsx * colsx != colsy * rowsy)
        {
            throw "vectors different sizes";
        }

        int inc(1);
        int n(rowsx * rowsy);
        double result = ddot(&n, arrayDatax, &inc, arrayDatay, &inc);
        return XlfOper(result);
        EXCEL_END;
    }

    LPXLARRAY EXCEL_EXPORT fortran_minverse(LPXLARRAY mat)
    {
        EXCEL_BEGIN;
        if(!dgetrf || !dgetri)
        {
            throw "dportf or dgetri not found in any dlls";
        }
        int rows;
        int cols;
        double* arrayData;
        extractArrayInfo(mat, rows, cols, arrayData);
        if(rows != cols)
        {
            throw "not a square matrix";
        }
        
        // The arrays come in in row major order and fortran
        // wants column major, luckily for this case
        // the inverse of the transpose is the transpose
        // of what we want anyway
        int* pivot = TempMemory::GetMemory<int>(rows);
        int error(0);
        dgetrf(&rows, &rows, arrayData, &rows, pivot, &error);
        if(error)
        {
            throw "getrf failed";
        }
        // get the size of the work array
        int lwork(-1);
        double workSize;
        dgetri(&rows, arrayData, &rows, pivot, &workSize, &lwork, &error);
        if(error)
        {
            throw "dgetri failed while getting work size";
        }
        lwork = (int)workSize;
        double* work = TempMemory::GetMemory<double>(lwork);
        dgetri(&rows, arrayData, &rows, pivot, work, &lwork, &error);
        if(error)
        {
            throw "dgetri failed";
        }
        return mat;
        EXCEL_END_ARRAY;
    }

    LPXLARRAY EXCEL_EXPORT fortran_mmult(LPXLARRAY x, LPXLARRAY y)
    {
        EXCEL_BEGIN;
        if(!dgemm)
        {
            throw "dgemm not found in any dlls";
        }
        
        int rowsx;
        int colsx;
        double* arrayDatax;
        extractArrayInfo(x, rowsx, colsx, arrayDatax);
        if(rowsx < 1 && colsx < 1)
        {
            throw "x not a matrix";
        }

        int rowsy;
        int colsy;
        double* arrayDatay;
        extractArrayInfo(y, rowsy, colsy, arrayDatay);
        if(rowsy < 1 && colsy < 1)
        {
            throw "y not a matrix";
        }

        if(colsx != rowsy)
        {
            throw "Matrices can't be multiplied";
        }

        double* resultData;
        LPXLARRAY result = createTempFpArray(rowsx, colsy, resultData);

        // remember that fortran expects column major matrices
        // and we have row major ones comming in.
        // take advantage of the identity that (XY)' = Y'X'
        // so we get the blas function to calc Y'X' and then
        // the answer is already in the right format
        char trans('N');
        double one(1.0);
        double zero(0.0);
        dgemm(&trans, &trans, &colsy, &rowsx, &colsx, &one, arrayDatay, &colsy, arrayDatax, &colsx, &zero, resultData, &colsy);

        return result;
        EXCEL_END_ARRAY;
    }

}

namespace
{
    const char* LibraryName = "Fortran";

    XLRegistration::Arg fortran_choleskyArgs[]=
    {
        { "sym"," matrix to decompose ","XLW_FP"}
    };

    XLRegistration::XLFunctionRegistrationHelper registerFortran_cholesky("fortran_cholesky",
        "fortran_cholesky", " Returns the Cholesky Decomposition of the matrix ",
        LibraryName, fortran_choleskyArgs, 1 ,false, true,
        "XLW_FP", "" ,false ,false, false);

    XLRegistration::Arg fortran_innerArgs[]=
    {
        { "x"," First Vector ","XLW_FP"},
        { "y"," Second Vector ","XLW_FP"}
    };

    XLRegistration::XLFunctionRegistrationHelper registerfortan_inner("fortran_inner",
        "fortran_inner", " computes the inner product of two vectors ",
        LibraryName, fortran_innerArgs, 2, false, true,
        "", "", false, false, false);

    XLRegistration::Arg fortran_mmultArgs[]=
    {
        { "x"," First Matrix","XLW_FP"},
        { "y"," Second Matrix","XLW_FP"}
    };

    XLRegistration::XLFunctionRegistrationHelper registerfortan_mmult("fortran_mmult",
        "fortran_mmult", " computes the matrix multiple of 2 matrices",
        LibraryName, fortran_mmultArgs, 2, false, true,
        "XLW_FP", "", false, false, false);

    XLRegistration::Arg fortran_minverseArgs[]=
    {
        { "mat"," matrix to invert","XLW_FP"}
    };

    XLRegistration::XLFunctionRegistrationHelper registerFortran_minverse("fortran_minverse",
        "fortran_minverse", " Returns the inverse of the matrix ",
        LibraryName, fortran_minverseArgs, 1 ,false, true,
        "XLW_FP", "" ,false ,false, false);
}
