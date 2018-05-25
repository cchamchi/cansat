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
 * @file       CansatIMU.h
 * @author     Dongwon Lee
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       Feb 2018
 * @brief
 *
 */

 #ifndef CansatIMU_h
 #define CansatIMU_h

#include <CansatSerial.h>

 #define RxMode_IMU_PORT    0x02  // 0100 0020 = 2

 #define IMU_DATA_SIZE 60
 template <class T>
 class CansatIMU
     : public CansatTransportSerial<T>
 {
 public:
     CansatIMU(T& stream)
         : CansatTransportSerial<T>(stream)
     {}

     void begin(uint32_t baud) {
         this->stream.begin(baud);
     }
     void begin() {
         this->stream.begin(115200);
     }
     bool read(float *buf){
         this->stream.RxModePortSet(RxMode_IMU_PORT);
         if(this->stream.available()){
             this->stream.read(_imu_data,IMU_DATA_SIZE);
             parsingAccelgyro(buf);
             return true;
         }else{
           return false;
         }
     }

     int connected() { return this->conn && this->stream; }
     int available() { return this->stream.available(); }
   private:

     void parsingAccelgyro(float *buf){
       char *tokenFrame = NULL;
       char *token =NULL;


       tokenFrame = strtok(_imu_data, "*");
       tokenFrame = strtok(NULL, "*"); //skip first frame data
       int i=0;
       for (token = strtok(tokenFrame, ","); token != NULL; token = strtok(NULL, ",")){

         char *unconverted;
          buf[i]= strtod(token, &unconverted);
          i++;
       }
     }

     char	_imu_data[IMU_DATA_SIZE];;
     size_t	_buff_size=IMU_DATA_SIZE;
 };



 typedef CansatTransportSerial<HardwareSerial> CansatHwSerial;

 static CansatHwSerial _IMUport(Serial1);

 CansatIMU<CansatHwSerial> cansatIMU(_IMUport);



 #endif
