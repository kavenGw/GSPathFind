//
//  GSNavLog.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/28.
//
//

#ifndef GSNavLog_hpp
#define GSNavLog_hpp

#include <stdio.h>

enum gsNavLogCategory
{
    GS_LOG_INFO = 1,	///< A progress log entry.
    GS_LOG_WARNING,			///< A warning log entry.
    GS_LOG_ERROR,			///< An error log entry.
};

enum gsNavLogState
{
    eOpenAll = 1,
    eOpenWarningAndError,
    eOpenError,
    eClose,
};

class GSNavLog
{
public:
    static GSNavLog& getInstance()
    {
        static GSNavLog singleTon;
        return singleTon;
    }
    
    void addInfoLog(const char* format,...);
    void addWarningLog(const char* format,...);
    void addErrorLog(const char* format,...);
    void addLog(gsNavLogCategory category,const char* format,...);
    
    void changeLogState(gsNavLogState state);
private:
    GSNavLog();
    gsNavLogState m_state;
};

#endif /* GSNavLog_hpp */
