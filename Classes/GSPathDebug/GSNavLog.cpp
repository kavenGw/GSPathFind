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
    
}

void GSNavLog::addWarningLog(const char *format, ...)
{
    
}

void GSNavLog::addErrorLog(const char *format, ...)
{
    
}

void GSNavLog::addLog(gsNavLogCategory category, const char *format, ...)
{

}

void GSNavLog::changeLogState(gsNavLogState state)
{
    this->m_state = state;
}
