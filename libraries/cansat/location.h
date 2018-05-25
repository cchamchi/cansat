/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file       location.h
 * @author     Dongwon Lee
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       April 2018
 * @brief
 *
*/

#ifndef CansatLocation_h
#define CansatLocation_h

#include <Arduino.h>
/*
    point[lat,lng] @dd,ddddddd
    result[0]=distance in meters
    result[1]=inital bearing (deg)
    result[2]=final bearing (deg)
    return 0 : fail to converge

*/

bool get_ditance_bearing(float point1[],float point2[],float results[]);

/*
    input point[lat,lng] @dd,ddddddd
          bearing (deg)
          dist (meter)
    output dest[]

*/

void get_destination(float point1[],float dest[],float bearing, float dist);


#endif
