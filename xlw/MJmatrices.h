//
//
//                          MJmatrices.h
//
//
/*
    a simple matrix class
    it has been kept so that its interface is minimal to facilitate interchange
    with other matrix classes


  */
#ifndef MJMATRICES_H
#define MJMATRICES_H


#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif


class MJMatrix
{
public:

    explicit MJMatrix(unsigned long Rows_=0, unsigned long Cols_=0);
    MJMatrix(const MJMatrix& original);

    MJMatrix& operator=(const MJMatrix& original);
    
    ~MJMatrix();
    
    inline const double& operator()(unsigned long i, unsigned long j) const;
    inline double& operator()(unsigned long i, unsigned long j);

    inline double* operator[](unsigned long i);
    inline const double* const operator[](unsigned long i) const;

    inline unsigned long rows() const;
    inline unsigned long columns() const;

    inline MJMatrix& operator+=(const MJMatrix& addend);

    MJMatrix& resize(unsigned long rows, unsigned long columns);


private:
    unsigned long Rows;
    unsigned long Columns;
    double** RowStarts;
    double* Start;

    void Create();
    void Create(unsigned long rows, unsigned long cols);
};

inline const double& MJMatrix::operator()(unsigned long i, unsigned long j) const
{
#ifdef _DEBUG
if (i >= Rows || j >= Columns)
    throw("index out of bounds");
#endif
    return RowStarts[i][j];
}

inline double& MJMatrix::operator()(unsigned long i, unsigned long j)
{
#ifdef _DEBUG
if (i >= Rows || j >= Columns)
    throw("index out of bounds");
#endif

    return RowStarts[i][j];
}

inline const double* const MJMatrix::operator[](unsigned long i) const
{
#ifdef _DEBUG
if (i >= Rows )
    throw("index out of bounds");
#endif

    return RowStarts[i];
}



inline double*  MJMatrix::operator[](unsigned long i)
{
#ifdef _DEBUG
if (i >= Rows )
    throw("index out of bounds");
#endif

    return RowStarts[i];
}

inline unsigned long MJMatrix::rows() const
{
    return Rows;
}

inline unsigned long MJMatrix::columns() const
{
    return Columns;
}   


inline MJMatrix& MJMatrix::operator+=(const MJMatrix& addend)
{
#ifdef _DEBUG
    if (addend.rows() != rows() || addend.columns() != columns())
        throw("bad addition");
#endif

    double* i = Start;
    double *j = addend.Start;
    double* end = Start+Rows*Columns;
    while (i != end)
    {
        *i += *j;
        ++i;
        ++j;
    }

    return *this;

}


#endif
