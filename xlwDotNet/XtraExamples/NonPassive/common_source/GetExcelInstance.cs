/*
 Copyright (C) 2008 2009  Narinder S Claire

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/



using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using xlwDotNet;
using xlwDotNet.xlwTypes;
//using System.Windows.Forms;
using Microsoft.Office.Core;
using XL = Microsoft.Office.Interop.Excel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;


namespace Example
{
    public class ExcelInstance
    {
        static XL._Application theInstance;
        
        [DllImport("ole32.dll")]
        public static extern int GetRunningObjectTable(int reserved,
                                  out IRunningObjectTable prot);

        [DllImport("ole32.dll")]
        public static extern int CreateBindCtx(int reserved, out IBindCtx ppbc);

        [DllImport("user32.dll")]
        public static extern IntPtr GetWindowThreadProcessId(int hwnd, out int processid);

        static ExcelInstance()
 
        {
            Hashtable result = new Hashtable();

            IntPtr numFetched = IntPtr.Zero;
            IRunningObjectTable runningObjectTable;
            IEnumMoniker monikerEnumerator;
            IMoniker[] monikers = new IMoniker[1];

            GetRunningObjectTable(0, out runningObjectTable);
            runningObjectTable.EnumRunning(out monikerEnumerator);
            monikerEnumerator.Reset();

            while (monikerEnumerator.Next(1, monikers, numFetched) == 0)
            {
                System.Runtime.InteropServices.ComTypes.IBindCtx ctx;
                CreateBindCtx(0, out ctx);

                string runningObjectName;
                monikers[0].GetDisplayName(ctx, null, out runningObjectName);

                object runningObjectVal;
                runningObjectTable.GetObject(monikers[0], out runningObjectVal);

                if (runningObjectVal is XL._Workbook)
                {
                    XL._Workbook theExcel = (XL._Workbook)runningObjectVal;
                    int theHandle = theExcel.Application.Hwnd;
                    int ProcessId;
                    GetWindowThreadProcessId(theHandle, out ProcessId);
                    if (ProcessId == Process.GetCurrentProcess().Id)
                    {
                        theInstance=theExcel.Application;
                        return;
                    }
                   
                }
                if (runningObjectVal is XL._Application)
                {
                    XL._Application theExcel = (XL._Application)runningObjectVal;
                    int theHandle = theExcel.Hwnd;
                    int ProcessId;
                    GetWindowThreadProcessId(theHandle, out ProcessId);
                    if (ProcessId == Process.GetCurrentProcess().Id)
                    {
                        theInstance = (XL._Application)runningObjectVal;
                        return;
                    }

                }
            }
            throw new Exception("Didn't get a Handle");
        }

        public static XL._Application Instance()
        {
            return theInstance;
        }

  
        
        
    }
}

