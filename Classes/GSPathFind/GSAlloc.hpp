//
//  GSAlloc.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/27.
//
//

#ifndef GSAlloc_hpp
#define GSAlloc_hpp

#include <stdio.h>
#include <stdlib.h>

void* gsAlloc(size_t size);
void gsFree(void* ptr);

#endif /* GSAlloc_hpp */
