
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

#ifndef INC_XlfOper_H
#define INC_XlfOper_H

/*!
\file XlfOper.h
\brief Declares class XlfOper.
*/

// $Id$

#include <xlw/XlfOperImpl.h>

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
class EXCEL32_API XlfOper
{
    friend class XlfOperImpl4;
    friend class XlfOperImpl12;
    friend class XlfExcel;

public:

    //! Default ctor.
    XlfOper() { XlfOperImpl::instance().Init(xlfOperUnion_); }
    //! Copy ctor.
    XlfOper(const XlfOper& oper) { *this = oper; }
    //! XLOPER * ctor.
    XlfOper(LPXLFOPER lpxloper) { xlfOperUnion_.lpxloper4 = reinterpret_cast<LPXLOPER>(lpxloper); }
    //! double ctor.
    XlfOper(double value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! short ctor.
    XlfOper(short value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! short or error ctor.
    XlfOper(short value, bool Error) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! boolean ctor.
    XlfOper(bool value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! 0 terminated character string ctor.
    XlfOper(const char *value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //!  string ctor.
    XlfOper(const std::string& value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //!  wstring ctor.
    XlfOper(const std::wstring& value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! CellMatrix ctor
    XlfOper(const CellMatrix& value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! MyMatrix ctor
    XlfOper(const MyMatrix& value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! MyArray ctor
    XlfOper(const MyArray& value) { XlfOperImpl::instance().Init(xlfOperUnion_, value); }
    //! XlfRef ctor.
    XlfOper(const XlfRef& range) { XlfOperImpl::instance().Init(xlfOperUnion_, range); }

    //! Dtor
    ~XlfOper() { XlfOperImpl::instance().destroy(xlfOperUnion_); }
    //! Free auxiliary memory associated with the XLOPER
    void FreeAuxiliaryMemory() const {
        return XlfOperImpl::instance().FreeAuxiliaryMemory(xlfOperUnion_); }
    //! Assignment operator
    XlfOper& operator=(const XlfOper& xloper)  {
        return XlfOperImpl::instance().assignment_operator(*this, xloper); }

    //! Is the data missing ?
    bool IsMissing() const {
        return XlfOperImpl::instance().IsMissing(xlfOperUnion_); }
    //! Is the data an error ?
    bool IsError() const {
        return XlfOperImpl::instance().IsError(xlfOperUnion_); }

    //! Converts to a double.
    double AsDouble(int *pxlret = 0) const {
        return XlfOperImpl::instance().AsDouble(xlfOperUnion_, pxlret); }
    //! Converts to a double with error identifer.
    double AsDouble(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsDouble(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a std::vector<double>.
    std::vector<double> AsDoubleVector(
        XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsDoubleVector(xlfOperUnion_, policy, pxlret); }
    std::vector<double> AsDoubleVector(
        const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsDoubleVector(xlfOperUnion_, ErrorId, policy, pxlret); }
 
    //! Converts to an array.
    MyArray AsArray(XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsArray(xlfOperUnion_, policy, pxlret); }
    MyArray AsArray(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsArray(xlfOperUnion_, ErrorId, policy, pxlret); }

    //! Converts to a short.
    short AsShort(int *pxlret = 0) const {
        return XlfOperImpl::instance().AsShort(xlfOperUnion_, pxlret); }
    //! Converts to a short with error identifer.
    short AsShort(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsShort(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a bool.
    bool AsBool(int *pxlret = 0) const {
        return XlfOperImpl::instance().AsBool(xlfOperUnion_, pxlret); }
    //! Converts to a bool with error identifer.
    bool AsBool(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsBool(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to an int.
    int AsInt(int *pxlret = 0) {
        return XlfOperImpl::instance().AsInt(xlfOperUnion_, pxlret); }
    //! Converts to an int with error identifer.
    int AsInt(const std::string& ErrorId, int *pxlret = 0) {
        return XlfOperImpl::instance().AsInt(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a char *.
    char *AsString(int *pxlret = 0) const {
        return XlfOperImpl::instance().AsString(xlfOperUnion_, pxlret); }
    //! Converts to a char * with error identifer.
    char *AsString(const std::string& ErrorId, int *pxlret = 0) const {
        return XlfOperImpl::instance().AsString(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a cell Matrix
    CellMatrix AsCellMatrix(int *pxlret=0) const {
        return XlfOperImpl::instance().AsCellMatrix(xlfOperUnion_, pxlret); }
    //! Converts to a cell Matrix with error identifer.
    CellMatrix AsCellMatrix(const std::string& ErrorId, int *pxlret=0) const {
        return XlfOperImpl::instance().AsCellMatrix(xlfOperUnion_, ErrorId, pxlret); }
 
    //! Converts to a matrix
    MyMatrix AsMatrix(int *pxlret=0) const {
        return XlfOperImpl::instance().AsMatrix(xlfOperUnion_, pxlret); }
    //! Converts to a matrix with error identifer.
    MyMatrix AsMatrix(const std::string& ErrorId, int *pxlret=0) const {
        return XlfOperImpl::instance().AsMatrix(xlfOperUnion_, ErrorId, pxlret); }

    //! Converts to a XlfRef.
    XlfRef AsRef(int *pxlret = 0) const {
        return XlfOperImpl::instance().AsRef(xlfOperUnion_, pxlret); }

    //! Gets the internal LPXLFOPER.
    LPXLFOPER GetLPXLFOPER() const {
        return XlfOperImpl::instance().GetLPXLFOPER(xlfOperUnion_); }

    //! Set the underlying XLOPER * to lpxloper
    void Set(LPXLFOPER lpxlfoper) {
        XlfOperImpl::instance().Set(xlfOperUnion_, lpxlfoper); }
    //! Set to a double
    void Set(double value) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value); }
    //! Set to a short
    void Set(short value) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value); }
    //! Set to a boolean
    void Set(bool value) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value); }
    //! Set to a zero-terminated character string
    void Set(const char *value) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value); }
    //! Set to a wstring
    void Set(const std::wstring &value) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value); }
    //! Set to a cell matrix
    void Set(const CellMatrix& cells) {
        XlfOperImpl::instance().Set(xlfOperUnion_, cells); }
    //! Set to a  matrix
    void Set(const MyMatrix& matrix) {
        XlfOperImpl::instance().Set(xlfOperUnion_, matrix); }
    //! Set to an array
    void Set(const MyArray& values) {
        XlfOperImpl::instance().Set(xlfOperUnion_, values); }
    //! Set to a range
    void Set(const XlfRef& range) {
        XlfOperImpl::instance().Set(xlfOperUnion_, range); }
    //! Set to a short or error, bool for disambiguation
    void Set(short value, bool Error) {
        XlfOperImpl::instance().Set(xlfOperUnion_, value, Error); }
    //! Set to an error value
    void SetError(WORD error) {
        XlfOperImpl::instance().SetError(xlfOperUnion_, error); }

    //! Cast to XLOPER *
    operator LPXLOPER() {
        return XlfOperImpl::instance().operator_LPXLOPER(xlfOperUnion_); }
    //! Cast to XLOPER12 *
    operator LPXLOPER12() {
        return XlfOperImpl::instance().operator_LPXLOPER12(xlfOperUnion_); }
    //! Cast to LPXLFOPER
    operator LPXLFOPER() {
        return XlfOperImpl::instance().operator_LPXLFOPER(xlfOperUnion_); }

private:

    //! Internal LPXLOPER.
    XlfOperUnion xlfOperUnion_;

    //! Reserves memory in XLL buffer (garbage collected).
    int Allocate() {
        return XlfOperImpl::instance().Allocate(xlfOperUnion_); }

    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDoubleVector(
        std::vector<double>& value, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional) const {
            return XlfOperImpl::instance().ConvertToDoubleVector(xlfOperUnion_, value, policy); }
    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDouble(double& value) const throw() {
        return XlfOperImpl::instance().ConvertToDouble(xlfOperUnion_, value); }
    //! Attempts conversion to short and returns Excel error code.
    int ConvertToShort(short& value) const throw() {
        return XlfOperImpl::instance().ConvertToShort(xlfOperUnion_, value); }
    //! Attempts conversion to bool and returns Excel error code.
    int ConvertToBool(bool& value) const throw() {
        return XlfOperImpl::instance().ConvertToBool(xlfOperUnion_, value); }
    //! Attempts conversion to int and returns Excel error code.
    //int ConvertToInt(int& value) const throw() {
    //    return XlfOperImpl::instance().ConvertToInt(xlfOperUnion_, value); }
    //! Attempts conversion to string and returns Excel error code.
    int ConvertToString(char *& value) const throw() {
        return XlfOperImpl::instance().ConvertToString(xlfOperUnion_, value); }
    //! Attempts conversion to CellMatrix and returns Excel error code
    int ConvertToCellMatrix(CellMatrix& output) const {
        return XlfOperImpl::instance().ConvertToCellMatrix(xlfOperUnion_, output); }
    //! Attempts conversion to Matrix and returns Excel error code
    int ConvertToMatrix(MyMatrix& output) const {
        return XlfOperImpl::instance().ConvertToMatrix(xlfOperUnion_, output); }

    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToRef(XlfRef& ref) const throw() {
        return XlfOperImpl::instance().ConvertToRef(xlfOperUnion_, ref); }
    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToErr(WORD& e) const throw() {
        return XlfOperImpl::instance().ConvertToErr(xlfOperUnion_, e); }

};

#endif
