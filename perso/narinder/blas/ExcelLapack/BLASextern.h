

#ifndef LAPACK_EXTERNAL_HEADER
#define LAPACK_EXTERNAL_HEADER


extern void daxpy_(int *n, double *alpha, double *x, int *incx, double *y, int *incy);
extern void dcopy_(int *n, double *x, int *incx, double *y, int *incy);
extern double ddot_(int *n, double *x, int *incx, double *y, int *incy);
extern void dgbmv_(char *trans, int *m, int *n, int *kl, int *ku, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy);
extern void dgemm_(char *transa, char *transb, int *m, int *n, int *k, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc);
extern void dgemv_(char *trans, int *m, int *n, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy);
extern void dger_(int *m, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *a, int *lda);
extern double dnrm2_(int *n, double *x, int *incx);
extern void drot_(int *n, double *x, int *incx, double *y, int *incy, double *c, double *s);
extern void drotg_(double *a, double *b, double *c, double *s);
extern void drotm_(int *n, double *x, int *incx, double *y, int *incy, double *param);
extern void drotmg_(double *d1, double *d2, double *b1, double *b2, double *param);
extern void dsbmv_(char *uplo, int *n, int *k, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy);
extern void dscal_(int *n, double *alpha, double *x, int *incx);
extern void dspmv_(char *uplo, int *n, double *alpha, double *ap, double *x, int *incx, double *beta, double *y, int *incy);
extern void dspr_(char *uplo, int *n, double *alpha, double *x, int *incx, double *ap);
extern void dspr2_(char *uplo, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *ap);
extern void dswap_(int *n, double *x, int *incx, double *y, int *incy);
extern void dsymm_(char *side, char *uplo, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc);
extern void dsymv_(char *uplo, int *n, double *alpha, double *a, int *lda, double *x, int *incx, double *beta, double *y, int *incy);
extern void dsyr_(char *uplo, int *n, double *alpha, double *x, int *incx, double *a, int *lda);
extern void dsyr2_(char *uplo, int *n, double *alpha, double *x, int *incx, double *y, int *incy, double *a, int *lda);
extern void dsyr2k_(char *uplo, char *trans, int *n, int *k, double *alpha, double *a, int *lda, double *b, int *ldb, double *beta, double *c, int *ldc);
extern void dsyrk_(char *uplo, char *trans, int *n, int *k, double *alpha, double *a, int *lda, double *beta, double *c, int *ldc);
extern void dtbmv_(char *uplo, char *trans, char *diag, int *n, int *k, double *a, int *lda, double *x, int *incx);
extern void dtbsv_(char *uplo, char *trans, char *diag, int *n, int *k, double *a, int *lda, double *x, int *incx);
extern void dtpmv_(char *uplo, char *trans, char *diag, int *n, double *ap, double *x, int *incx);
extern void dtpsv_(char *uplo, char *trans, char *diag, int *n, double *ap, double *x, int *incx);
extern void dtrmm_(char *side, char *uplo, char *transa, char *diag, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb);
extern void dtrmv_(char *uplo, char *trans, char *diag, int *n, double *a, int *lda, double *x, int *incx);
extern void dtrsm_(char *side, char *uplo, char *transa, char *diag, int *m, int *n, double *alpha, double *a, int *lda, double *b, int *ldb);
extern void dtrsv_(char *uplo, char *trans, char *diag, int *n, double *a, int *lda, double *x, int *incx);
extern int  idamax_(int *n, double *x, int *incx);


#endif //LAPACK

