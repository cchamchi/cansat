/**
 * @file       CansatGPS.h
 * @author     Dongwon Lee
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       Feb 2018
 * @brief
 *
*/

#ifndef CansatGPS_h
#define CansatGPS_h

#include <CansatSerial.h>
#include <CansatGPS_NMEA.h>




template <class T>
class CansatGPS
     : public CansatTransportSerial<T>,Cansat_GPS_NMEA
{
 public:
     CansatGPS(T& stream)
         : CansatTransportSerial<T>(stream),Cansat_GPS_NMEA(this->state)
     {}

     void begin(uint32_t baud) {
         this->stream.begin(baud);
     }
     void begin() {
         this->stream.begin(9600);
     }
     bool read(){

         int16_t numc;
         bool parsed = false;
         char c;
         this->stream.RxModePortSet(RxMode_GPS_PORT);
         numc = this->stream.available();
         while (numc--) {
             this->stream.read(&c,1); //read 1 Byte
             if (decode(c)) {
                 parsed = true;
             }
         }
         return parsed;

     }

     int connected() { return this->conn && this->stream; }
     int available() { return this->stream.available(); }
     // ground speed in m/s
     float ground_speed_ms() const {
         return state.ground_speed;
     }
     float ground_speed_km() const {
         return (state.ground_speed*3600.)/1000.;
     }
     // ground course in degrees
     float ground_course() const {
         return state.ground_course;
     }
     // number of locked satellites
     uint8_t num_sats() const {
         return state.num_sats;
     }
     // the time we last processed a message in milliseconds. This is
     // used to indicate that we have new GPS data to process
     uint32_t last_message_time_ms() const {
         return timing.last_message_time_ms;
     }
     // system time delta between the last two reported positions
     uint16_t last_message_delta_time_ms() const {
         return timing.delta_time_ms;
     }
     /// Query GPS status
     GPS_Status status() const {
         return state.status;
     }

     // location of last fix
     const Location &location() const {
         return state.location;
     }
     uint32_t time() const {
         return state.time;
     }
     uint32_t date() const {
         return state.date;
     }
   private:


     GPS_State state;
     // Note allowance for an additional instance to contain blended data
     GPS_timing timing;


 };



 typedef CansatTransportSerial<HardwareSerial> CansatHwSerial;

 static CansatHwSerial _GPSport(Serial1);

 CansatGPS<CansatHwSerial> cansatGPS(_GPSport);



 #endif
