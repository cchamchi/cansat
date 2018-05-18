/**
 * @file       location.h
 * @author     Dongwon Lee
 * @license    This project is released under the MIT License (MIT)
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
