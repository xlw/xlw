// $Id$
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "xlw/TempMemory.h"
#include "xlw/CriticalSection.h"
#include "xlw/ThreadLocalStorage.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <xlw/XlfWindows.h>

typedef xlw_tr1::shared_ptr<xlw::TempMemory> TempMemoryPtr;


namespace 
{
     xlw::ThreadLocalStorage<xlw::TempMemory> tls;
     xlw::CriticalSection threadInfoVector;
     std::vector<TempMemoryPtr> tempMemoryInstances;
}
namespace
{
    bool threadIsDead(const TempMemoryPtr& tempMemory)
    {
        return tempMemory->isThreadDead();
    }

}

namespace xlw {

    char* TempMemory::GetBytes(size_t bytes)
    {
        TempMemory* threadStorage = tls.GetValue();
        if(!threadStorage)
        {
            threadStorage = CreateTempMemory();
        }
        return threadStorage->InternalGetMemory(bytes);
    }

    void TempMemory::EnterExportedFunction() {
        TempMemory* threadStorage = tls.GetValue();
        if(!threadStorage)
        {
            threadStorage = CreateTempMemory();
        }
        threadStorage->InternalEnterExportedFunction();
    }


    void TempMemory::LeaveExportedFunction() {
        TempMemory* threadStorage = tls.GetValue();
        if(threadStorage)
        {
            threadStorage->InternalLeaveExportedFunction();
        }
    }

    TempMemory::TempMemory() :
        offset_(0),
        threadId_(GetCurrentThreadId()),
        depth_(0){
    }

    TempMemory::~TempMemory() {
        InternalFreeMemory(true);
    }

    void TempMemory::InternalFreeMemory(bool finished) {
        size_t nbBuffersToKeep = 1;
        if (finished)
            nbBuffersToKeep = 0;
        while (freeList_.size() > nbBuffersToKeep) {
           // delete[] freeList_.back().start; shouldn't need this anymore
            freeList_.pop_back();
        }
        offset_ = 0;
    }

    void TempMemory::InternalEnterExportedFunction() {
        if(depth_ == 0)
        {
            InternalFreeMemory(false);
        }
        ++depth_;
    }

    void TempMemory::InternalLeaveExportedFunction() {
        --depth_;
    }

    TempMemory* TempMemory::CreateTempMemory() {
        // we want to keep function entry
        // as fast as possible, so to avoid
        // needing a critical section around each call
        // we use a double lock
        ProtectInScope protecting(threadInfoVector);
        TempMemory* threadStorage = tls.GetValue();
        if(!threadStorage)
        {
            // see if any of the existing threads have died
            // since we where last called
            tempMemoryInstances.erase(std::remove_if(tempMemoryInstances.begin(), tempMemoryInstances.end(), threadIsDead), tempMemoryInstances.end());

            // create the new memory object
            TempMemoryPtr smartThreadStorage(new TempMemory);
            threadStorage = smartThreadStorage.get();
            tls.SetValue(threadStorage);
            tempMemoryInstances.push_back(smartThreadStorage);
        }
        return threadStorage;
    }


    void TempMemory::PushNewBuffer(size_t size) {
        XlfBuffer newBuffer;
        newBuffer.size = size;
        newBuffer.start = shared_char_ptr(new char[size],CustomArrayDeleter<char>());;
        freeList_.push_front(newBuffer);
        offset_=0;
    #if !defined(NDEBUG)
        std::cerr << "xlw is allocating a new buffer of " << static_cast<unsigned int>(size) << " bytes" << std::endl;
    #endif
        return;
    }

    char* TempMemory::InternalGetMemory(size_t bytes) {
        if (freeList_.empty())
            PushNewBuffer(8192);
        XlfBuffer& buffer = freeList_.front();
        if (offset_ + bytes > buffer.size) {
            // if we need more space allocate either 50% more than last time
            // or enough to hold all the of data used on previous buffer and this data and a bit of spare
            // space, whichever is greater
            PushNewBuffer(std::max((buffer.size * 3) / 2, (offset_ + bytes) + 4096));
            // buffer no longer valid
            memset(freeList_.front().start.get(), 0, bytes);
            offset_ = bytes;
            return freeList_.front().start.get();
        }
        else
        {
            size_t temp = offset_;
            memset(buffer.start.get() + temp, 0, bytes);
            offset_ += bytes;
            return buffer.start.get() + temp;
        }
    }

    void TempMemory::InitializeProcess() {
        // turns out we don't need to do anything now
        // left in case we do in the future
    }

    void TempMemory::TerminateProcess() {
        ProtectInScope protecting(threadInfoVector);
        for(size_t i(0); i < tempMemoryInstances.size(); ++i) {
            tempMemoryInstances[i]->InternalFreeMemory(true);
        }
        // NOTE:
        // we deliberately don't call tempMemoryInstances.clear()
        // here as we can't remove the TLS info from other threads
        // and it's possible for our addin to be reloaded and to reuse 
        // calculation threads
    }
    
    bool TempMemory::isThreadDead() const
    {
        HANDLE threadHandle(OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId_));
        if(threadHandle) {
            DWORD exitCode(0);
            BOOL result = GetExitCodeThread(threadHandle, &exitCode);
            CloseHandle(threadHandle);
            if(result != 0) {
                if(exitCode == STILL_ACTIVE) {
                    // still running
                    return false;
                }
                else {
                    // it's gone
                    return true;
                }
            }
            else {
                // fail safe and don't delete in this case
                return false;
            }
        }
        else {
            // fail safe and don't delete in this case
            return false;
        }
    }
}
