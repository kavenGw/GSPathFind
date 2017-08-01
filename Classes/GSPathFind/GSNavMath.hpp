//
//  GSNavMath.hpp
//  GSPathFind
//
//  Created by Can Wu on 2017/7/31.
//
//

#ifndef GSNavMath_hpp
#define GSNavMath_hpp

#include <stdio.h>
#include "GSNavData.hpp"

bool is_point_in_triangle(const GSNavPoint &s, const GSNavPoint &a, const GSNavPoint &b, const GSNavPoint &c);
GSNavPoint get_closest_point_to_segment_2d(const GSNavPoint &p_point, const GSNavPoint &point1,const GSNavPoint&point2);

bool gsMove(GSNavPoint& nowPos,const GSNavPoint &end,const int speed);
#endif /* GSNavMath_hpp */
