/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*!
\file XlfExcel.cpp
\brief Implements the classes XlfExcel and XlfExcelDestroyer.
*/

// $Id$

#include <xlw/XlfExcel.h>
#ifdef PORT_USE_OLD_C_HEADERS
    #include <stdio.h>
#else
    #include <cstdio>
#endif
#include <stdexcept>
#include <xlw/XlfOper.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfExcel.inl>
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

extern "C" {
    //! Main API function to Excel.
    int (__cdecl *Excel4)(int xlfn, LPXLOPER operRes, int count,...);
    //! Main API function to Excel, passing the argument as an array.
    int (__stdcall *Excel4v)(int xlfn, LPXLOPER operRes, int count, LPXLOPER far opers[]);
}

XlfExcel *XlfExcel::this_ = 0;

//! Internal implementation of XlfExcel.
struct XlfExcelImpl
{
  //! Ctor.
  XlfExcelImpl(ofstream * hlogf = 0): hlogf_(hlogf) {}
  //! Handle to the DLL module.
  HINSTANCE handle_;
  //! Pointer to log file, currently not used.
  ofstream * hlogf_;
};

/* Displays a message box */
void XlfExcel::EarlyLog(const char *msg)
{
  MsgBox(msg);
};

bool XlfExcel::IsInitialized()
{
  return this_ != 0;
}

ofstream *XlfExcel::GetLogFileHandle()
{
  return impl_->hlogf_;
}

/*!
\return Occupation of the buffer as a number between 0 and 1.

You might want to increase the size of the buffer with the
method XlfExcel::AllocateBuffer.
*/
double XlfExcel::GetBufferOccupation() const
{
  return offset_/(double)bufsz_;
}

//! Destroys the XlfExcel singleton.
/*!
A static instance of XlfExcelDestroyer
in the dtor of XlfExcel makes sure XlfExcel dtor is called before the
end of the program.

Note that it does not help you if some function tries to access the
XlfExcelDestroyer after its dtor was called. It is howver very unlikely.
If it ever happened a new instance of XlfExcel would be created.
*/
class XlfExcelDestroyer
{
public:
  //! Dtor.
  /*!
  Deletes the pointer returned by XlfExcel::Instance().
  */
  ~XlfExcelDestroyer()
  {
    // delete 0 is safe. It should never happen though.
    delete &XlfExcel::Instance();
  }
};

/*!
You always have the choice with the singleton in returning a pointer or
a reference. By returning a reference and declaring the copy ctor and the
assignment otor private, I limit the risk of a wrong use of XlfExcel
(typically duplication).
*/
XlfExcel& XlfExcel::Instance()
{
//	static XlfExcelDestroyer destroyer;
	if (!this_)
	{
		this_ = new XlfExcel;
		// intialize library first because log displays
		// XLL name in header of log window
		this_->InitLibrary();
		this_->InitLog();
	}
	return *this_;
}

/*!
If not title is specified, the message is assumed to be an error log
*/
void XlfExcel::MsgBox(const char *errmsg, const char *title)
{
	LPVOID lpMsgBuf;
	// retrieve message error from system err code
	if (!title)
	{
		DWORD err = GetLastError();
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);
		// Process any inserts in lpMsgBuf.
		char completeMessage[255];
		sprintf(completeMessage,"%s due to error %d :\n%s", errmsg, err, (LPCSTR)lpMsgBuf);
		MessageBox(NULL, completeMessage,"XLL Error", MB_OK | MB_ICONINFORMATION);
		// Free the buffer.
		LocalFree(lpMsgBuf);
	}
	else
		MessageBox(NULL, errmsg, title, MB_OK | MB_ICONINFORMATION);
	return;
}

/*!
If msg is 0, the status bar is cleared.
*/
void XlfExcel::SendMessage(const char *msg)
{
	if (msg)
		Call(xlcMessage,0,2,XlfOper(true),XlfOper(msg));
	else
		Call(xlcMessage,0,1,XlfOper(false));
	return;
}

bool XlfExcel::IsEscPressed() const
{
	XlfOper ret;
	Call(xlAbort,ret,1,XlfOper(false));
	return ret.AsBool();
}

void XlfExcel::Log(const char *str)
{
  ofstream * log = GetLogFileHandle();
	if (log)
		(*log) << str << endl << flush;
	else
		XlfExcel::EarlyLog(str);
	return;
}

XlfExcel::XlfExcel(): impl_(0), offset_(0), buffer_(0)
{
  impl_ = new XlfExcelImpl();
	AllocateBuffer();
	return;
}

XlfExcel::~XlfExcel()
{
  ofstream * log = GetLogFileHandle();
  if (log)
  {
  	(*log) << endl << endl << "-- Log file ended gracefully --" << endl;
  	log->close();
  	delete log;
  }
	delete[] buffer_;
  delete impl_;
  this_ = 0;
	return;
}

void XlfExcel::AllocateBuffer(size_t buffersize)
{
	FreeMemory();
	bufsz_ = buffersize;
	if (buffer_)
		delete[] buffer_;
	buffer_ = new char[bufsz_];
	ERR_CHECKX(buffer_ != 0, std::runtime_error,"Could not allocate buffer");
	return;
}

/*!
The name of the log file is the same than the xll with a \c .log
extension instead of the \c .xll.
The file is located in the directory refered by the TEMP environment
variable if it exists else TMP environment variable if it exists else
in the xll directory.
*/
void XlfExcel::InitLog()
{
	std::string name = GetName();
	std::string root;
	if (getenv("TEMP"))
		root = getenv("TEMP");
	if (root.empty() && getenv("TMP"))
		root = getenv("TMP");
	if (root.empty())
		root = name.substr(0, name.rfind('\\'));

	std::string base = name.substr(name.rfind('\\') + 1);
	base = base.substr(0, base.rfind('.'));
	if (root[root.length()-1]!='\\')
		root+="\\";
	impl_->hlogf_ = new ofstream((root + base+".log").c_str());
	return;
}

/*!
Load \c XlfCALL32.DLL to interface excel (this library is shipped with Excel)
and link it to the XLL.
*/
void XlfExcel::InitLibrary()
{
  HINSTANCE handle = LoadLibrary("XLCALL32.DLL");
	ERR_CHECKX(handle != 0, std::runtime_error,"Could not load library XLCALL32.DLL");
	Excel4 = (int (__cdecl *)(int, struct xloper *, int, ...))GetProcAddress(handle,"Excel4");
	ERR_CHECKX(Excel4 != 0, std::runtime_error,"Could not get address of Excel4 callback");
	Excel4v = (int (__stdcall *)(int, struct xloper *, int, struct xloper *[]))GetProcAddress(handle,"Excel4v");
	ERR_CHECKX(Excel4v != 0, std::runtime_error,"Could not get address of Excel4v callback");
  impl_->handle_ = handle;
	return;
}

std::string XlfExcel::GetName() const
{
	XlfOper xName;
  int err = Call(xlGetName, (LPXLOPER)xName, 0);
	ERR_CHECKX(err == xlretSuccess, std::runtime_error,"Could not get DLL name");
	return xName.AsString();
}

#ifdef __MINGW32__
int __cdecl XlfExcel::Call(int xlfn, LPXLOPER pxResult, int count, ...) const
#else
int cdecl XlfExcel::Call(int xlfn, LPXLOPER pxResult, int count, ...) const
#endif
{
#ifdef _ALPHA_
/*
* On the Alpha, arguments may be passed in via registers instead of
* being located in a contiguous block of memory, so we must use the
* va_arg functions to retrieve them instead of simply walking through
* memory.
	*/
	va_list argList;
	LPXLOPER *plpx = alloca(count*sizeof(LPXLOPER));
#endif

#ifdef _ALPHA_
	/* Fetch all of the LPXLOPERS and copy them into plpx.
	* plpx is alloca'ed and will automatically be freed when the function
	* exits.
	*/
	va_start(argList, count);
	for (i = 0; i<count; i++)
		plpx[i] = va_arg(argList, LPXLOPER);
	va_end(argList);
#endif

#ifdef _ALPHA_
	return Callv(xlfn, pxResult, count, plpx);
#else
	return Callv(xlfn, pxResult, count, (LPXLOPER *)(&count + 1));
#endif
}

/*!
If one (or more) cells refered as argument is(are) uncalculated, the framework
throw an exception and return immediately to Excel.
*/
int XlfExcel::Callv(int xlfn, LPXLOPER pxResult, int count, LPXLOPER pxdata[]) const
{
#ifndef NDEBUG
	for (size_t i = 0; i<size_t(count);++i)
		if (!pxdata[i])
		{
			if (xlfn & xlCommand)
				ERR_LOG("xlCommand | " << (xlfn & 0x0FFF));
			if (xlfn & xlSpecial)
				ERR_LOG("xlSpecial | " << (xlfn & 0x0FFF));
			if (xlfn & xlIntl)
				ERR_LOG("xlIntl | " << (xlfn & 0x0FFF));
			if (xlfn & xlPrompt)
				ERR_LOG("xlPrompt | " << (xlfn & 0x0FFF));
			ERR_THROW_MSG(XlfException,"0 pointer for argument " << i);
		}
#endif
		int err = Excel4v(xlfn, pxResult, count, pxdata);
		if (err & xlretUncalced)
			ERR_THROW(XlfExceptionUncalculated);
		if (err & xlretAbort)
			ERR_THROW(XlfExceptionAbort)
		if (err & xlretStackOvfl)
			ERR_THROW_MSG(std::runtime_error,"Stack Overflow");
		return err;
}

