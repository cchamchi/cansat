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
 * @file       CansatSerial.h
 * @author     Dongwon Lee
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       Feb 2018
 * @brief
 *
 */

#ifndef CansatStream_h
#define CansatStream_h



#define RxMode_CAMERA_PORT 0x00  // 0000 0000 = 0
#define RxMode_GPS_PORT    0x01  // 0010 0001 = 1
#define RxMode_IMU_PORT    0x02  // 0100 0020 = 2

template <class T>
class CansatTransportSerial
{
public:
    CansatTransportSerial(T& stream)
        : stream(stream), conn(0)
    {}

    void begin(uint32_t baud) {
        stream.begin(baud);
    }

    bool connect() {
        CANSAT_LOG("Connecting...");
        return conn = true;
    }
    void disconnect() { conn = false; }

    size_t read(void* buf, size_t len) {
        return stream.readBytes((char*)buf, len);
    }
    size_t write(const void* buf, size_t len) {
        return stream.write((const uint8_t*)buf, len);
    }
    void RxModePortSet( unsigned char iMode)
    {
      unsigned char b = PINC  ;
      b     &= 0xF0  ; // direction is 0
      b     |= iMode ;
      PORTC = b      ;
    }
    bool connected() { return conn; }
    int available() { return stream.available(); }

protected:
    T&     stream;
    bool   conn;
};

template <class T>
class CansatTransportSerialChecked
    : public CansatTransportSerial<T>
{
public:
    CansatTransportSerialChecked(T& stream)
        : CansatTransportSerial<T>(stream)
    {}

    void begin(uint32_t baud) {
        this->stream.begin(baud);
        while (!this->stream) {
            // wait for serial port to connect. Needed for Leonardo only
        }
    }

    int connected() { return this->conn && this->stream; }
};

typedef CansatTransportSerial<HardwareSerial> CansatHwSerial;


#endif
