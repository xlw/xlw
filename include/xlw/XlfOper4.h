
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfOper4_H
#define INC_XlfOper4_H

/*!
\file XlfOper4.h
\brief Declares class XlfOper4.
*/

// $Id: XlfOper4.h 340 2007-10-14 15:40:31Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfRef.h>
#include <xlw/MyContainers.h>
#include <vector>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

class XlfRef;
class CellMatrix;

//! Wrapper around a pointer to the XLOPER Excel data structure.
/*!
This class eases the work of marshalling and unmarshalling data to
the Excel XLOPER format (including memory).

XlfOper4 holds a pointer to a XLOPER.

\warning It is important \e not to add any data members or virtual member
functions to this class because the library heavily relies on the fact that
LPXLOPER and XlfOper4 have the same size. It allows the library to interpret
any LPXLOPER sent by Excel as an XlfOper4.
*/
class EXCEL32_API XlfOper4
{
public:
    //! \name Structors and Static Members
    /*!
    See also the Set function that corresponds to each type.
    */
    //@{
    //! Default ctor.
    XlfOper4();
    //! Copy ctor.
    XlfOper4(const XlfOper4& oper);
    //! XLOPER * ctor.
    /*!
    Shallow copy of a pointer to XLOPER.
    \param lpxloper Pointer to XLOPER.
    */
    XlfOper4(LPXLOPER lpxloper);
    //! double ctor.
    XlfOper4(double value);
    //! short ctor.
    XlfOper4(short value);
    //! short or error ctor.
    XlfOper4(short value, bool Error);
    //! boolean ctor.
    XlfOper4(bool value);
    //! 0 terminated character string ctor.
    XlfOper4(const char *value);
    //!  string ctor.
    XlfOper4(const std::string& value);
    //! CellMatrix ctor.
    XlfOper4(const CellMatrix& value);
    //! MyMatrix ctor.
    XlfOper4(const MyMatrix& value);
    //! MyArray ctor.
    XlfOper4(const MyArray& value);
    //! XlfRef ctor.
    XlfOper4(const XlfRef& range);
    //! Container ctor.
    template <class FwdIt>
    XlfOper4(WORD rows, BYTE cols, FwdIt start)
    {
        Allocate();
        Set(rows,cols,start);
    }
    //! Constructs an Excel error.
    /*!
    Unlike other XlfOper4, the return value is not allocated on the internal
    buffer to avoid allocating more memory. Instead it is allocated on a
    shared static XLOPER.

    FIXME above no longer true after changes for thread safety

    \arg error One of the values listed below and defined in xlcall32.h

    \code
    #define xlerrNull    0      // No info
    #define xlerrDiv0    7      // Division by 0
    #define xlerrValue   15     // Bad value
    #define xlerrRef     23     // Bad reference
    #define xlerrName    29     // Bad name
    #define xlerrNum     36     // Bad number
    #define xlerrNA      42     // Not available
    \endcode

    \sa XlfOper4::SetError(WORD)
    */
    static XlfOper4 Error(WORD);
    //! Dtor
    /*!
    Calls Deallocate() to free the XLOPER allocated by the XLL. XLOPER allocated
    by Excel remain under Excel responsability.

    Calls FreeAuxiliaryMemory if the XLOPER is marked by XlfOper4::Call as an
    XLOPER returned by MS Excel and if the type matches one of xltypeStr,
    xltypeRef, xltypeMulti, xltypeBigData.
    */
    ~XlfOper4();
    //@}

    //! \name Memory Management
    //@{
    //! Free auxiliary memory associated with the XLOPER.
    void FreeAuxiliaryMemory() const;
    //@}

    //! \name Operators
    //@{
    //! Assignment operator.
    XlfOper4& operator=(const XlfOper4& xloper);
    //! Cast to XLOPER *.
    operator LPXLOPER();
    //@}

    //! \name Inspectors
    //@{
    //! Is the data missing ?
    bool IsMissing() const;
    //! Is the data an error ?
    bool IsError() const;
    //! Is the data a reference ?
    bool IsRef() const;
    //! Is the data a sheet reference ?
    bool IsSRef() const;
    //! Is the data an array ?
    bool IsMulti() const;
    //! Is the data a number ?
    bool IsNumber() const;
    //! Is the data a string ?
    bool IsString() const;
    //! Is the data a null value ?
    bool IsNil() const;
    //! Is the data a boolean ?
    bool IsBool() const;
    //! Is the data an integer ?
    bool IsInt() const;

    //! Return the type code
    WORD xltype() const;
    //@}

    //! \name Conversions
    //@{
    //! Converts to a double.
    /*!
    Attempts to convert the implict object to a double. If pxlret is not null
    the method won't throw and the Excel return code will be returned in this
    variable.

    \sa XlfOper4::ConvertToDouble.
    */
    double AsDouble(int * pxlret = 0) const;
    //! Converts to a double with error identifer.
    double AsDouble(const std::string& ErrorId, int * pxlret = 0) const;

    //! Lets the user choose how to convert a range in a vector<double>
    /*!
    Default policy is UniDimensional. The 2 others are typically to facilitate conversion
    to matrix classes.

    \sa ConvertToDoubleVector, AsDoubleVector.
    */
    enum DoubleVectorConvPolicy
    {
        /*! Generates an error if the range is not uni dimensional (one row or one column). */
        UniDimensional,
        /*! Flattens the range in a C-like way (rows are continuous). */
        RowMajor,
        /*! Flattens the range in a Fortran-like way (columns are continuous). */
        ColumnMajor
    };

    //! Converts to a std::vector<double>.
    /*!
    Attempts to convert the implict object to a vector of double. If pxlret is
    not null the method won't throw and the Excel return code will be returned
    in this variable.
        
    \sa XlfOper4::ConvertToDoubleVector.
    */
    std::vector<double> AsDoubleVector(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
    std::vector<double> AsDoubleVector(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;

    //! Converts to an array.
    /*!
    Attempts to convert the implict object to an array.  Does this by calling
    AsDoubleVector.  If pxlret is not null the method won't throw and the Excel
    return code will be returned in this variable.
    */
    MyArray AsArray(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
    MyArray AsArray(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;

    //! Converts to a short.
    short AsShort(int * pxlret = 0) const;
    //! Converts to a short with error identifer.
    short AsShort(const std::string& ErrorId, int * pxlret = 0) const;

    //! Converts to a bool.
    bool AsBool(int * pxlret = 0) const;
    //! Converts to a bool with error identifer.
    bool AsBool(const std::string& ErrorId,int * pxlret = 0) const;

    //! Converts to an int.
    int AsInt(int * pxlret = 0) const;
    //! Converts to an int with error identifer.
    int AsInt(const std::string& ErrorId,int * pxlret = 0) const;

    //! Converts to a char *.
    /*!
    Attempts to convert the implict object to a char string. If pxlret is not
    null the method won't throw and the Excel return code will be returned in
    this variable.

    \sa XlfOper4::ConvertToString.

    The XLL allocates the memory on its own buffer. This buffer is automatically
    freed when a function of the XLL is called again. Note that coerce to
    a char string is the slowest cast of all.
    */
    char * AsString(int * pxlret = 0) const;
    //! Converts to a char * with error identifer.
    char * AsString(const std::string& ErrorId,int * pxlret = 0) const;

    //! Converts to a cell Matrix.
    CellMatrix AsCellMatrix( int * pxlret=0) const;
    //! Converts to a cell Matrix with error identifer.
    /*!
    Attempts to convert the implict object to a cell matrix. If pxlret is
    not null the method won't throw and the Excel return code will be returned
    in this variable.

    \sa XlfOper4::ConvertToCellMatrix.
    */
    CellMatrix AsCellMatrix( const std::string& ErrorId,int * pxlret=0) const;

    //! Converts to a matrix.
    /*!
    Attempts to convert the implict object to a matrix. If pxlret is
    not null the method won't throw and the Excel return code will be returned
    in this variable.

    \sa XlfOper4::ConvertToMatrix.
    */
    MyMatrix AsMatrix( int * pxlret=0) const;
    //! Converts to a matrix with error identifer.
    MyMatrix AsMatrix( const std::string& ErrorId,int * pxlret=0) const;

    //! Converts to a XlfRef.
    /*!
    Attempts to convert the implict object to an XlfRef. If pxlret is not null
    the method won't throw and the Excel return code will be returned in this
    variable.

    \sa XlfOper4::ConvertToRef.
    */
    XlfRef AsRef(int * pxlret = 0) const;
    //@}

    //! \name XLOPER Reference Management
    //@{
    //! Gets the internal LPXLOPER.
    LPXLOPER GetLPXLOPER() const;
    //@}

    //! \name Setters
    //@{
    //! Set the underlying XLOPER * to lpxloper.
    XlfOper4& Set(LPXLOPER lpxloper);
    //! Set to a double.
    XlfOper4& Set(double value);
    //! Set to a short.
    XlfOper4& Set(short value);
    //! Set to a boolean.
    XlfOper4& Set(bool value);
    //! Set to a zero-terminated character string.
    /*!
    If no memory can be allocated on xlw internal buffer, the XlfOper4 is set
    to an invalid state and the string is not copied.

    The Excel API supports strings of 256 bytes.  The 0th byte holds the length
    of the string and the remaining 255 bytes hold the string data which is not
    null terminated.

    Here xlw uses the 0th byte for the string length, then at the 1st byte
    starts a string which _is_ null terminated.  In theory this allows a pointer
    to the 1st byte to be passed to C string functions requiring null termination
    e.g. strcpy.

    \note A string longer than 254 characters is truncated. A warning
    is issued in debug mode.
    */
    XlfOper4& Set(const char *value);
    //! Set to a cell matrix.
    XlfOper4& Set(const CellMatrix& cells);
    //! Set to a  matrix.
    XlfOper4& Set(const MyMatrix& matrix);
    //! Set to an array.
    XlfOper4& Set(const MyArray& values);
    //! Set to a range.
    /*!
    If no memory can be allocated on xlw internal buffer, the XlfOper4 is set
    to an invalid state and the XlfRef is not copied.
    */
    XlfOper4& Set(const XlfRef& range);
    //! Set to a short or error, bool for disambiguation.
    XlfOper4& Set(short value, bool Error);
    //! Set to an error value.
    /*!
    \sa XlfOper4::Error(WORD)
    */
    XlfOper4& SetError(WORD error);
    //! Set to an array.
    /*!
    \param r number of rows in the array
    \param c number of columns in the array
    \param it iterator pointing to the begining of a container
    of size r x c (at least) that contain the data.
    \warning Data are to be stored row-wise.
    */
    template<class FwdIt>
    XlfOper4& Set(WORD r, BYTE c, FwdIt it)
    {
        lpxloper_->xltype = xltypeMulti;
        lpxloper_->val.array.rows = r;
        lpxloper_->val.array.columns = c;
        lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
        for (size_t i = 0; i < size_t(r*c); ++i, ++it)
            lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper4(*it);
        return *this;
    }
    //@}

private:
    //! \name Manage XLOPER Reference
    //@{
    //! Internal LPXLOPER.
    LPXLOPER lpxloper_;
    //@}

    //! \name Coercion
    //@{
    //! Coerces method is called by conversion operators if needed (never by the user).
    /*!
    \param type is an integer indicating the target type we want to coerce to.
    \param result is the XLOPER where to store the output.
    */
    int Coerce(short type, XlfOper4& result) const;
    //@}

    //! \name Memory Management
    //@{
    //! Reserves memory in XLL buffer (garbage collected).
    /*!
    Allocates 16 bits (size of a XLOPER) on the temporary buffer
    stored by XlfExcel with a call to XlfExcel::GetMemory().

    \warning Each XlfOper4 allocation causes a call to Allocate which in turn
    reserve the necessary number of bytes in the internal buffer. The
    problem is that even temporary XlfOper4 used inside the xll function use
    this internal buffer. This buffer is not freed before the next call to
    the xll to ensure Excel can use the data before they are freed. This
    causes a bottleneck if the function uses many temporary XlfOper4 (see
    Deallocate()).

    \return \c xlretSuccess or \c xlretInvXloper if no memory is could
    be allocated.
    */
    int Allocate();

    //! Anticipates deallocation if possible.
    /*!
    Do nothing. May be implemented later to avoid overload of the internal
    buffer by temporary XLOPER allocated by the XLL.
    */
    void Deallocate();

    //! Internally used to flag XLOPER returned by Excel.
    /*!
    This bit is currently unused by Microsoft Excel. We set it
    to indicate that the LPXLOPER (passed by Excel) holds some extra
    memory to be freed.

    This bit is controled in ~XlfOper4 to know if the DLL should release
    auxiliary memory or not by a call to FreeAuxiliaryMemory.
    */
    static int xlbitFreeAuxMem;
    //@}

    //! \name Error Handling
    //@{
    //! Throws an exception when critical errors occur.
    /*!
    Throws an exception if the argument is anything other than xlretSuccess.

    Events that require an immediate return to excel (uncalculated cell, abort,
    stack overflow and invalid OPER (potential memory exhaustion)) throw an
    XlfException.

    Other events throw std::runtime_error.
    */
    int ThrowOnError(int) const;

    //! Throws an exception when critical errors occur but passes on an identifier to help track it down.
    /*!
    Throws an exception if the argument is anything other than xlretSuccess.

    Events that require an immediate return to excel (uncalculated cell, abort,
    stack overflow and invalid OPER (potential memory exhaustion)) throw an
    XlfException.

    Other events throw std::runtime_error. The Identifier is tagged on to the error message to help track down
    problems.
    */
    int ThrowOnError(int, const std::string& identifier) const;
    //@}

    //! \name Conversions
    //@{
    //! Attempts conversion to double and returns Excel error code.
    /*!
    Converts the data in the range in a vector of double according to the specified policy.

    \pre All values in the range should be convertible to a double.
        
    \return xlretFailed if the policy is UniDimensional and the range is not uni dimensional
    and xlretSuccess otherwise or whatever error occurs during coercing the data to double.

    \sa DoubleVectorConvPolicy
    */
    int ConvertToDoubleVector(std::vector<double>&, DoubleVectorConvPolicy policy = UniDimensional) const;
    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDouble(double&) const throw();
    //! Attempts conversion to short and returns Excel error code.
    /*!
    Attempts to convert the implict object to a short. If pxlret is not null
    the method won't throw and the Excel return code will be returned in this
    variable.

    \sa XlfOper4::ConvertToShort.
    */
    int ConvertToShort(short&) const throw();
    //! Attempts conversion to bool and returns Excel error code.
    /*!
    Attempts to convert the implict object to a bool. If pxlret is not null
    the method won't throw and the Excel return code will be returned in this
    variable.

    \sa XlfOper4::ConvertToBool.
    */
    int ConvertToBool(bool&) const throw();
    //! Attempts conversion to int and returns Excel error code.
    int ConvertToInt(int&) const throw();
    //! Attempts conversion to string and returns Excel error code.
    int ConvertToString(char *&) const throw();
    //! Attempts conversion to CellMatrix and returns Excel error code.
    int ConvertToCellMatrix( CellMatrix& output) const;
    //! Attempts conversion to Matrix and returns Excel error code.
    /*! converts the XlfOper4 to a matrix, since if its a valid matrix
    its also a valid cellmatrix we convert to cell matrix first,
    note this necessitates passing as a P not an R.
    */
    int ConvertToMatrix( MyMatrix& output) const;

    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToRef(XlfRef&) const throw();
    //! Attempts conversion to XlRef and returns Excel error code.
    int XlfOper4::ConvertToErr(WORD& e) const throw();
    //@}

    friend class XlfExcel;
};

#ifdef NDEBUG
#include <xlw/XlfOper4.inl>
#endif

#endif

