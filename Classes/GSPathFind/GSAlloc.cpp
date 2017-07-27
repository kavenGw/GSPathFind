//
//  GSAlloc.cpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#include "GSAlloc.hpp"

void* gsAlloc(size_t size)
{
    return malloc(size);
}

void gsFree(void* ptr)
{
    if(ptr != NULL){
        free(ptr);
    }
}
