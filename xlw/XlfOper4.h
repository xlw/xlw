
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007 Eric Ehlers
 
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

// $Id: XlfOper.h 381 2007-11-20 13:08:51Z ericehlers $

#include <xlw/XlfOperImpl4.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Wrapper around a pointer to the XLOPER Excel data structure.
/*!
This class eases the work of marshalling and unmarshalling data to
the Excel XLOPER format (including memory).
 
XlfOper holds a pointer to a XLOPER.
 
\warning It is important \e not to add any data members to this class
because the library heavily relies on the fact that LPXLOPER and
XlfOper have the same size. It allows the library to interpret any
LPXLOPER sent by Excel as an XlfOper.
*/
class EXCEL32_API XlfOper4
{
    friend class XlfOperImpl4;
    friend class XlfExcel;

public:

    //! Default ctor.
    XlfOper4() { XlfOperImpl4::instance().Init(xlfOperUnion_); }
    //! Copy ctor.
    XlfOper4(const XlfOper& oper) { *this = oper; }
    //! XLOPER * ctor.
    XlfOper4(LPXLFOPER lpxloper) { xlfOperUnion_.lpxloper4 = reinterpret_cast<LPXLOPER>(lpxloper); }
    //! double ctor.
    XlfOper4(double value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! short ctor.
    XlfOper4(short value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! short or error ctor.
    XlfOper4(short value, bool Error) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! boolean ctor.
    XlfOper4(bool value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! 0 terminated character string ctor.
    XlfOper4(const char *value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //!  string ctor.
    XlfOper4(const std::string& value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //!  wstring ctor.
    XlfOper4(const std::wstring& value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! CellMatrix ctor
    XlfOper4(const CellMatrix& value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! MyMatrix ctor
    XlfOper4(const MyMatrix& value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! MyArray ctor
    XlfOper4(const MyArray& value) { XlfOperImpl4::instance().Init(xlfOperUnion_, value); }
    //! XlfRef ctor.
    XlfOper4(const XlfRef& range) { XlfOperImpl4::instance().Init(xlfOperUnion_, range); }

    //! Dtor
    ~XlfOper4() { XlfOperImpl4::instance().destroy(xlfOperUnion_); }
    //! Free auxiliary memory associated with the XLOPER
    void FreeAuxiliaryMemory() const {
        return XlfOperImpl4::instance().FreeAuxiliaryMemory(xlfOperUnion_); }
    //! Assignment operator
    //XlfOper4& operator=(const XlfOper4& xloper)  {
    //    return XlfOperImpl4::instance().assignment_operator(*this, xloper); }

    //! Is the data missing ?
    bool IsMissing() const {
        return XlfOperImpl4::instance().IsMissing(xlfOperUnion_); }
    //! Is the data an error ?
    bool IsError() const {
        return XlfOperImpl4::instance().IsError(xlfOperUnion_); }

    //! Converts to a double.
    double AsDouble(int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsDouble(xlfOperUnion_, pxlret); }
    //! Converts to a double with error identifer.
    double AsDouble(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsDouble(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a std::vector<double>.
    std::vector<double> AsDoubleVector(
        XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsDoubleVector(xlfOperUnion_, policy, pxlret); }
    std::vector<double> AsDoubleVector(
        const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsDoubleVector(xlfOperUnion_, ErrorId, policy, pxlret); }
 
    //! Converts to an array.
    MyArray AsArray(XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsArray(xlfOperUnion_, policy, pxlret); }
    MyArray AsArray(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsArray(xlfOperUnion_, ErrorId, policy, pxlret); }

    //! Converts to a short.
    short AsShort(int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsShort(xlfOperUnion_, pxlret); }
    //! Converts to a short with error identifer.
    short AsShort(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsShort(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a bool.
    bool AsBool(int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsBool(xlfOperUnion_, pxlret); }
    //! Converts to a bool with error identifer.
    bool AsBool(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsBool(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to an int.
    int AsInt(int *pxlret = 0) {
        return XlfOperImpl4::instance().AsInt(xlfOperUnion_, pxlret); }
    //! Converts to an int with error identifer.
    int AsInt(const std::string& ErrorId, int *pxlret = 0) {
        return XlfOperImpl4::instance().AsInt(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a char *.
    char *AsString(int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsString(xlfOperUnion_, pxlret); }
    //! Converts to a char * with error identifer.
    char *AsString(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsString(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a cell Matrix
    CellMatrix AsCellMatrix(int *pxlret=0) const {
        return XlfOperImpl4::instance().AsCellMatrix(xlfOperUnion_, pxlret); }
    //! Converts to a cell Matrix with error identifer.
    CellMatrix AsCellMatrix(const std::string& ErrorId, int *pxlret=0) const {
        return XlfOperImpl4::instance().AsCellMatrix(xlfOperUnion_, ErrorId, pxlret); }
 
    //! Converts to a matrix
    MyMatrix AsMatrix(int *pxlret=0) const {
        return XlfOperImpl4::instance().AsMatrix(xlfOperUnion_, pxlret); }
    //! Converts to a matrix with error identifer.
    MyMatrix AsMatrix(const std::string& ErrorId, int *pxlret=0) const {
        return XlfOperImpl4::instance().AsMatrix(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a XlfRef.
    XlfRef AsRef(int *pxlret = 0) const {
        return XlfOperImpl4::instance().AsRef(xlfOperUnion_, pxlret); }

    //! Gets the internal LPXLFOPER.
    LPXLFOPER GetLPXLFOPER() const {
        return XlfOperImpl4::instance().GetLPXLFOPER(xlfOperUnion_); }

    //! Set the underlying XLOPER * to lpxloper
    void Set(LPXLFOPER lpxlfoper) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, lpxlfoper); }
    //! Set to a double
    void Set(double value) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value); }
    //! Set to a short
    void Set(short value) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value); }
    //! Set to a boolean
    void Set(bool value) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value); }
    //! Set to a zero-terminated character string
    void Set(const char *value) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value); }
    //! Set to a wstring
    void Set(const std::wstring &value) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value); }
    //! Set to a cell matrix
    void Set(const CellMatrix& cells) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, cells); }
    //! Set to a  matrix
    void Set(const MyMatrix& matrix) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, matrix); }
    //! Set to an array
    void Set(const MyArray& values) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, values); }
    //! Set to a range
    void Set(const XlfRef& range) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, range); }
    //! Set to a short or error, bool for disambiguation
    void Set(short value, bool Error) {
        XlfOperImpl4::instance().Set(xlfOperUnion_, value, Error); }
    //! Set to an error value
    void SetError(WORD error) {
        XlfOperImpl4::instance().SetError(xlfOperUnion_, error); }

    //! Cast to XLOPER *
    operator LPXLOPER() {
        return XlfOperImpl4::instance().operator_LPXLOPER(xlfOperUnion_); }
    //! Cast to XLOPER12 *
    operator LPXLOPER12() {
        return XlfOperImpl4::instance().operator_LPXLOPER12(xlfOperUnion_); }
    //! Cast to LPXLFOPER
    operator LPXLFOPER() {
        return XlfOperImpl4::instance().operator_LPXLFOPER(xlfOperUnion_); }

private:

    //! Internal LPXLOPER.
    XlfOperUnion xlfOperUnion_;

    //! Reserves memory in XLL buffer (garbage collected).
    int Allocate() {
        return XlfOperImpl4::instance().Allocate(xlfOperUnion_); }

    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDoubleVector(
        std::vector<double>& value, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional) const {
            return XlfOperImpl4::instance().ConvertToDoubleVector(xlfOperUnion_, value, policy); }
    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDouble(double& value) const throw() {
        return XlfOperImpl4::instance().ConvertToDouble(xlfOperUnion_, value); }
    //! Attempts conversion to short and returns Excel error code.
    int ConvertToShort(short& value) const throw() {
        return XlfOperImpl4::instance().ConvertToShort(xlfOperUnion_, value); }
    //! Attempts conversion to bool and returns Excel error code.
    int ConvertToBool(bool& value) const throw() {
        return XlfOperImpl4::instance().ConvertToBool(xlfOperUnion_, value); }
    //! Attempts conversion to int and returns Excel error code.
    //int ConvertToInt(int& value) const throw() {
    //    return XlfOperImpl4::instance().ConvertToInt(xlfOperUnion_, value); }
    //! Attempts conversion to string and returns Excel error code.
    int ConvertToString(char *& value) const throw() {
        return XlfOperImpl4::instance().ConvertToString(xlfOperUnion_, value); }
    //! Attempts conversion to CellMatrix and returns Excel error code
    int ConvertToCellMatrix(CellMatrix& output) const {
        return XlfOperImpl4::instance().ConvertToCellMatrix(xlfOperUnion_, output); }
    //! Attempts conversion to Matrix and returns Excel error code
    int ConvertToMatrix(MyMatrix& output) const {
        return XlfOperImpl4::instance().ConvertToMatrix(xlfOperUnion_, output); }

    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToRef(XlfRef& ref) const throw() {
        return XlfOperImpl4::instance().ConvertToRef(xlfOperUnion_, ref); }
    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToErr(WORD& e) const throw() {
        return XlfOperImpl4::instance().ConvertToErr(xlfOperUnion_, e); }

};

#endif
