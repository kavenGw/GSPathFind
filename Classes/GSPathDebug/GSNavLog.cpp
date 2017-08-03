//
//  GSNavLog.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/28.
//
//

#include "GSNavLog.hpp"

GSNavLog::GSNavLog()
{
    this->m_state = gsNavLogState::eOpenAll;
}

void GSNavLog::addInfoLog(const char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    
    printf(format,argp);
    
    va_end(argp);
}

void GSNavLog::addWarningLog(const char *format, ...)
{
    
    va_list argp;
    va_start(argp, format);
    
    printf(format,argp);
    
    va_end(argp);
}

void GSNavLog::addErrorLog(const char *format, ...)
{
    
    va_list argp;
    va_start(argp, format);
    
    printf(format,argp);
    
    va_end(argp);
}

void GSNavLog::addLog(gsNavLogCategory category, const char *format, ...)
{
    
    va_list argp;
    va_start(argp, format);
    
    printf(format,argp);
    
    va_end(argp);
}

void GSNavLog::changeLogState(gsNavLogState state)
{
    this->m_state = state;
}
