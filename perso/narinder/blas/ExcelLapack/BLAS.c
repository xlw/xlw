

#include"BLASextern.h"

#define WINAPI  __declspec(dllexport) 


void WINAPI __stdcall daxpy(int *n, double *alpha, double *x, int *incx, double *y, int *incy){
daxpy_(n, alpha, x, incx, y, incy);
}

void WINAPI __stdcall dcopy(int *n, double *x, int *incx, double *y, int *incy){
dcopy_(n, x, incx,y, incy);
}

double WINAPI __stdcall ddot(int *n, double *x, int *incx, double *y, int *incy){
return ddot_(n, x, incx, y, incy);
}

void WINAPI __stdcall dgbmv(char *trans, int *m, int *n, int *kl, int *ku, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy){
dgbmv_(trans, m, n, kl, ku, alpha, a, lda,x, incx, beta, y, incy);
}

void WINAPI __stdcall dgemm(char *transa, char *transb, int *m, int *n, int *k, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc){
dgemm_(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

void WINAPI __stdcall dgemv(char *trans, int *m, int *n, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy){
dgemv_(trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
}

void WINAPI __stdcall dger(int *m, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *a, int *lda){
dger_(m, n, alpha, x, incx, y, incy, a, lda);
}

double WINAPI __stdcall dnrm2(int *n, double *x, int *incx){
return dnrm2_(n, x, incx);
}

void WINAPI __stdcall drot(int *n, double *x, int *incx, double *y, int *incy, double *c, double *s){
drot_(n, x, incx, y, incy, c, s);
}

void WINAPI __stdcall drotg(double *a, double *b, double *c, double *s){
drotg_(a, b, c, s);
}

void WINAPI __stdcall drotm(int *n, double *x, int *incx, double *y, int *incy, double *param){
drotm_(n, x, incx, y, incy, param);
}

void WINAPI __stdcall drotmg(double *d1, double *d2, double *b1, double *b2, double *param){
drotmg_(d1, d2, b1, b2, param);
}

void WINAPI __stdcall dsbmv(char *uplo, int *n, int *k, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy){
dsbmv_(uplo, n, k, alpha, a, lda,x, incx, beta, y, incy);
}

void WINAPI __stdcall dscal(int *n, double *alpha, double *x, int *incx){
dscal_(n, alpha, x, incx);
}


void WINAPI __stdcall dspmv(char *uplo, int *n, double *alpha, double *ap, double *x, int *incx, double *beta, double *y, int *incy){
dspmv_(uplo, n, alpha, ap, x, incx, beta, y, incy);
}

void WINAPI __stdcall dspr(char *uplo, int *n, double *alpha, double *x, int *incx, double *ap){
dspr_(uplo, n, alpha, x, incx, ap);
}

void WINAPI __stdcall dspr2(char *uplo, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *ap){
dspr2_(uplo, n, alpha, x, incx, y, incy, ap);
}

void WINAPI __stdcall dswap(int *n, double *x, int *incx, double *y, int *incy){
dswap_(n,x , incx, y, incy);
}

void WINAPI __stdcall dsymm(char *side, char *uplo, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc){
dsymm_(side, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

void WINAPI __stdcall dsymv(char *uplo, int *n, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy){
dsymv_(uplo, n, alpha, a, lda,x, incx, beta, y, incy);
}

void WINAPI __stdcall dsyr(char *uplo, int *n, double *alpha, double *x, int *incx, double *a, int *lda){
dsyr_(uplo,n, alpha, x, incx, a,lda);
}

void WINAPI __stdcall dsyr2(char *uplo, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *a, int *lda){
dsyr2_(uplo, n, alpha, x, incx, y, incy, a, lda);
}

void WINAPI __stdcall dsyr2k(char *uplo, char *trans, int *n, int *k, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc){
dsyr2k_(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

void WINAPI __stdcall dsyrk(char *uplo, char *trans, int *n, int *k, double *alpha, double *a, int *lda, double *beta, double *c, int *ldc){
dsyrk_(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

void WINAPI __stdcall dtbmv(char *uplo, char *trans, char *diag, int *n, int *k, double *a, int *lda, double *x, int *incx){
dtbmv_(uplo,trans, diag, n, k,a,lda, x, incx);
}

void WINAPI __stdcall dtbsv(char *uplo, char *trans, char *diag, int *n, int *k, double *a, int *lda, double *x, int *incx){
dtbsv_(uplo, trans, diag, n, k, a, lda, x, incx);
}

void WINAPI __stdcall dtpmv(char *uplo, char *trans, char *diag, int *n, double *ap, double *x, int *incx){
dtpmv_(uplo, trans, diag, n, ap, x, incx);
}

void WINAPI __stdcall dtpsv(char *uplo, char *trans, char *diag, int *n, double *ap, double *x, int *incx){
dtpsv_(uplo, trans, diag, n, ap, x, incx);
}

void WINAPI __stdcall dtrmm(char *side, char *uplo, char *transa, char *diag, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb){
dtrmm_(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

void WINAPI __stdcall dtrmv(char *uplo, char *trans, char *diag, int *n, double *a, int *lda, double *x, int *incx){
dtrmv_(uplo, trans,diag, n, a, lda, x, incx);
}

void WINAPI __stdcall dtrsm(char *side, char *uplo, char *transa, char *diag, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb){
dtrsm_(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

void WINAPI __stdcall  dtrsv(char *uplo, char *trans, char *diag, int *n, double *a, int *lda, double *x, int *incx){
dtrsv_(uplo, trans, diag, n, a, lda, x, incx);
}

int WINAPI __stdcall idamax(int *n, double *x, int *incx){
return idamax_(n, x, incx);
}