Xlw User Contributed Files - Fortran
===================================

BLAS http://www.netlib.org/blas/
LAPACK http://www.netlib.org/lapack/

Demonstrates using Excels FP array type in handwritten code.

There are 2 ways of using this project.
1) Copy xll into the directory containing the BLAS and LAPACK dlls
2) Set the environment variable FORTRAN_DLL_DIR to the location of the 
   dlls you want to use.

You can get BLAS/LAPACK dlls with various licences from

1) http://www.fi.muni.cz/~xsvobod2/misc/lapack/

Get the shared version (statically-linked, release) version.

2) AMD ACML http://developer.amd.com/cpu/libraries/acml/Pages/default.aspx

3) AMD ACML GPU http://developer.amd.com/gpu/acmlgpu/Pages/default.aspx

4) Intel MKL C:\Program Files (x86)\Intel\Compiler\11.0\061\cpp\Documentation\mkl\mkl_documentation.htm

The library probably works with other implementations as well, let us know of any successes or failures in the
xlw-users@lists.sourceforge.net mailing list


Intel MKL Building a custom Dll
===============================

MKL doesn't ship with a dll with the correct exports, this must be built manually.

Go to the mkl\tools\builder dirctory in a visual studio command box (on my machine this is 
C:\Program Files\Intel\Compiler\11.0\061\cpp\mkl\tools\builder)

and build the 32 bit dlls

nmake ia32 threading=sequential BUF_LIB= export=blas_cdecl_list name=mkl_blas
nmake ia32 threading=sequential BUF_LIB= export=lapack_cdecl_list name=mkl_lapack

and in a 64-bit command box build the 64-bit dll's if required

nmake em64t threading=sequential BUF_LIB= export=blas_cdecl_list name=mkl_blas_x64
nmake em64t threading=sequential BUF_LIB= export=lapack_cdecl_list name=mkl_lapack_x64





