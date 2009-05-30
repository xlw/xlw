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
using System.Text;
using Microsoft.Office.Interop.Excel;
using System.Runtime.InteropServices;
using System.Windows.Forms;


namespace TestRTD
{
    [Guid("187F3B31-CB94-48e0-A721-9DEBA62AC969")]
    [ProgId("RTDDemo")]

    public class Class1 : IRtdServer
    {
        private IRTDUpdateEvent theCallback;
        private int theTopic;
        private Timer theTimer= new Timer();
        

        public int ServerStart(IRTDUpdateEvent theCallback_)
        {
            theCallback = theCallback_;
            theTimer.Tick += new EventHandler(TimerEventHandler);
            theTimer.Interval = 2000; // because excel will only check about 2 seconds anyway
            return 1;
        }
        public void ServerTerminate()
        {
        }
        public object ConnectData(int Id,
                                  ref Array strings,
                                  ref bool newValues)
        {
            theTimer.Start();
            theTopic = Id;
            return DateTime.Now.ToOADate();
        }
        public void DisconnectData(int topicId)
        {
            theTimer.Stop();
        }
        private void TimerEventHandler(object sender,
                                  EventArgs args)
        {
            theTimer.Stop();
            theCallback.UpdateNotify();
        }
        public Array RefreshData(ref int topic)
        {
            object[,] data = new object[2, 1];
            data[0, 0] = theTopic;
            data[1, 0] = DateTime.Now.ToOADate();
            topic = 1;

            theTimer.Start();
            return data;
        }

        public int Heartbeat()
        {
            return 1;
        }








    }
}
