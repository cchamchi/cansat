/**
 * @file       CansatIMU.h
 * @author     Dongwon Lee
 * @license    This project is released under the MIT License (MIT)
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
     void read(float *buf){
         this->stream.RxModePortSet(RxMode_IMU_PORT);
         if(this->stream.available()){
             this->stream.read(_imu_data,IMU_DATA_SIZE);
             parsingAccelgyro(buf);
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
