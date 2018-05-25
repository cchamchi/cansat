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
 * @file       location.c
 * @author     Dongwon Lee
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       April 2018
 * @brief
 *
*/


#include <location.h>

#define     PI 3.14159265358979

float degreesToRadians(float degrees) {
  return degrees *(PI/180.);  // () 가 매우 중요
}
float radiansToDegrees(float radians) {
  return radians *(180./PI);  // () 가 매우 중요
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* Vincenty Inverse Solution of Geodesics on the Ellipsoid (c) Chris Veness 2002-2010             */
/*                                                                                                */
/* from: Vincenty inverse formula - T Vincenty, "Direct and Inverse Solutions of Geodesics on the */
/*       Ellipsoid with application of nested equations", Survey Review, vol XXII no 176, 1975    */
/*       http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf                                             */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/**
 * Calculates geodetic distance between two points specified by latitude/longitude using
 * Vincenty inverse formula for ellipsoids
 *
 * @param   {Number} lat1, lon1: first point in decimal degrees
 * @param   {Number} lat2, lon2: second point in decimal degrees
 * @returns (Number} distance in metres between points
 */
bool distVincenty(float point1[],float point2[],float results[]){

  float lat1=point1[0];float lon1=point1[1];
  float lat2=point2[0];float lon2=point2[1];
  float a = 6378137, b = 6356752.314245,  f = 1/298.257223563;  // WGS-84 ellipsoid params
  float L = degreesToRadians((lon2-lon1));
  float U1 = atan((1-f) * tan(degreesToRadians(lat1)));
  float U2 = atan((1-f) * tan(degreesToRadians(lat2)));
  float sinU1 = sin(U1), cosU1 = cos(U1);
  float sinU2 = sin(U2), cosU2 = cos(U2);
  float cosSqAlpha,cos2SigmaM,sinSigma,sinLambda,cosLambda,cosSigma,sigma ;

  float lambda = L, lambdaP, iterLimit = 100;
  do {
    sinLambda = sin(lambda);
    cosLambda = cos(lambda);
    sinSigma = sqrt((cosU2*sinLambda) * (cosU2*sinLambda) +
      (cosU1*sinU2-sinU1*cosU2*cosLambda) * (cosU1*sinU2-sinU1*cosU2*cosLambda));
    if (sinSigma==0) return 0;  // co-incident points

    cosSigma = sinU1*sinU2 + cosU1*cosU2*cosLambda;
    sigma = atan2(sinSigma, cosSigma);
    float sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
    cosSqAlpha = 1 - sinAlpha*sinAlpha;
    cos2SigmaM = cosSigma - 2*sinU1*sinU2/cosSqAlpha;
      if (isnan(cos2SigmaM)) cos2SigmaM = 0;  // equatorial line: cosSqAlpha=0 (§6)
    float C = (f/16)*cosSqAlpha*(4+f*(4-3*cosSqAlpha));
    lambdaP = lambda;
    lambda = L + (1-C) * f * sinAlpha *
      (sigma + C*sinSigma*(cos2SigmaM+C*cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)));
  } while ((fabs(lambda-lambdaP) > 1e-12) && (--iterLimit > 0));

  if (iterLimit==0) return false;  // formula failed to converge

  float uSq = cosSqAlpha * (a*a - b*b) / (b*b);
  float A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
  float B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));
  float deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)-
    B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
  float s = b*A*(sigma-deltaSigma);

  //s = s.toFixed(3); // round to 1mm precision
  results[0]= s;

  // note: to return initial/final bearings in addition to distance, use something like:
  float fwdAz = atan2(cosU2*sinLambda,  cosU1*sinU2-sinU1*cosU2*cosLambda);
  float revAz = atan2(cosU1*sinLambda, -sinU1*cosU2+cosU1*sinU2*cosLambda);
  results[1]=radiansToDegrees(fwdAz);
  if(results[1]<0)results[1]+=360.;
  results[2]=radiansToDegrees(revAz);
  if(results[2]<0)results[2]+=360.;
  //return { distance: s, initialBearing: fwdAz.toDeg(), finalBearing: revAz.toDeg() };
  return true;
}

/**************************************************************************
 * Module: vincenty (direct).
 *
 * Calculate WGS 84 destination given starting lat/long (degrees),
 * bearing (degrees) & distance (Meters).
 *
 * from: Vincenty direct formula - T Vincenty, "Direct and Inverse
 * Solutions of Geodesics on the Ellipsoid with application of
 * nested equations", Survey Review, vol XXII no 176, 1975
 *       http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
 *
 * Ported from web java script implementation.  Code standard is a bit
 * odd, but it's efficient and closely parallels the alg equations.
 *
 * Doug Summers    Nov 2010
 *
 ************************************************************/
void destVincenty(float point1[],float dest[],float bearing, float dist){
//double lat1, double lon1, double bearing, double dist,
//                  double *lat2out, double *lon2out)
  // WGS-84 ellipsiod
  float a=6378137.0, b=6356752.3142, f=1/298.257223563;
  float alpha1,sinAlpha, sinAlpha1, cosAlpha1, cosSqAlpha;
  float sigma, sigma1, cos2SigmaM, sinSigma, cosSigma, deltaSigma, sigmaP;
  float tanU1, cosU1, sinU1, uSq;
  float A, B, C, L, lambda;
  float tmp, lat2;
  float revAz;   /* unused but retained for alg completeness */
  float lat1=point1[0],lon1=point1[1];

  /* code body */

  alpha1 = degreesToRadians(bearing);
  sinAlpha1 = sin(alpha1);
  cosAlpha1 = cos(alpha1);

  tanU1 = (1-f) * tan(degreesToRadians(lat1));
  cosU1 = 1 / sqrt((1 + tanU1*tanU1));
  sinU1 = tanU1*cosU1;
  sigma1 = atan2(tanU1, cosAlpha1);
  sinAlpha = cosU1 * sinAlpha1;
  cosSqAlpha = 1 - sinAlpha*sinAlpha;
  uSq = cosSqAlpha * (a*a - b*b) / (b*b);
  A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
  B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));

  sigma = dist / (b*A);
  sigmaP = 2*PI;
  while (fabs(sigma-sigmaP) > 1e-12) {
    cos2SigmaM = cos(2*sigma1 + sigma);
    sinSigma = sin(sigma);
    cosSigma = cos(sigma);
    deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)-
                 B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
    sigmaP = sigma;
    sigma = dist / (b*A) + deltaSigma;
  }

  tmp = sinU1*sinSigma - cosU1*cosSigma*cosAlpha1;
  lat2 = atan2(sinU1*cosSigma + cosU1*sinSigma*cosAlpha1,
      (1-f)*sqrt(sinAlpha*sinAlpha + tmp*tmp));
  lambda = atan2(sinSigma*sinAlpha1,
                 cosU1*cosSigma - sinU1*sinSigma*cosAlpha1);
  C = f/16*cosSqAlpha*(4+f*(4-3*cosSqAlpha));
  L = lambda - (1-C)*f*sinAlpha*(sigma+C*sinSigma*(cos2SigmaM+C*cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)));

  // final bearing
   dest[2] = atan2(sinAlpha, -tmp);

  // algorithm convention uses Deg outputs
  dest[0] = radiansToDegrees(lat2);
  dest[1] = lon1+(radiansToDegrees(L));
}

/*
    point[lat,lng] @dd,ddddddd
    result[0]=distance in meters
    result[1]=inital bearing (deg)
    result[2]=final bearing (deg)

*/



bool get_ditance_bearing(float point1[],float point2[],float results[]){
  return distVincenty(point1,point2,results);
}

/*
    input point[lat,lng] @dd,ddddddd
          bearing (deg)
          dist (meter)
    output dest[]

*/

void get_destination(float point1[],float dest[],float bearing, float dist){
  destVincenty(point1,dest,bearing, dist);

}
