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

//
// NMEA parser, adapted by Michael Smith from TinyGPS v9:
//
// TinyGPS - a small GPS library for Arduino providing basic NMEA parsing
// Copyright (C) 2008-9 Mikal Hart
// All rights reserved.
//
//

/// @file	AP_GPS_NMEA.h
/// @brief	NMEA protocol parser
///
/// This is a lightweight NMEA parser, derived originally from the
/// TinyGPS parser by Mikal Hart.  It is frugal in its use of memory
/// and tries to avoid unnecessary arithmetic.
///
/// The parser handles GPGGA, GPRMC and GPVTG messages, and attempts to be
/// robust in the face of occasional corruption in the input stream.  It
/// makes a basic effort to configure GPS' that are likely to be connected in
/// NMEA mode (SiRF, MediaTek and ublox) to emit the correct message
/// stream, but does not validate that the correct stream is being received.
/// In particular, a unit emitting just GPRMC will show as having a fix
/// even though no altitude data is being received.
///
/// GPVTG data is parsed, but as the message may not contain the the
/// qualifier field (this is common with e.g. older SiRF units) it is
/// not considered a source of fix-valid information.
///


/**
 * @file       CansatGPS_NMEA.h
 * @author     Dongwon Lee
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       April 2018
 * @brief     modified vesion of AP_GPS_NMEA.h
 *
*/

#ifndef CansatGPS_NMEA_h
#define CansatGPS_NEMA_h
#include <Arduino.h>




#define FALLTHROUGH [[fallthrough]]
struct Location {

    int32_t alt:24;                                     ///< param 2 - Altitude in centimeters (meters * 100) see LOCATION_ALT_MAX_M
    int32_t lat;                                        ///< param 3 - Latitude * 10**7
    int32_t lng;                                        ///< param 4 - Longitude * 10**7
};

#define GPS_FIX_TYPE_NO_GPS 0
#define GPS_FIX_TYPE_NO_FIX 1
#define GPS_FIX_TYPE_2D_FIX 2
#define GPS_FIX_TYPE_3D_FIX 3
#define GPS_FIX_TYPE_DGPS 4
#define GPS_FIX_TYPE_RTK_FLOAT 5
#define GPS_FIX_TYPE_RTK_FLOAT 6
#define GPS_FIX_TYPE_RTK_FIXED 7
enum GPS_Status {
    NO_GPS = GPS_FIX_TYPE_NO_GPS,                     ///< No GPS connected/detected
    NO_FIX = GPS_FIX_TYPE_NO_FIX,                     ///< Receiving valid GPS messages but no lock
    GPS_OK_FIX_2D = GPS_FIX_TYPE_2D_FIX,              ///< Receiving valid messages and 2D lock
    GPS_OK_FIX_3D = GPS_FIX_TYPE_3D_FIX,              ///< Receiving valid messages and 3D lock
    GPS_OK_FIX_3D_DGPS = GPS_FIX_TYPE_DGPS,           ///< Receiving valid messages and 3D lock with differential improvements
    GPS_OK_FIX_3D_RTK_FLOAT = GPS_FIX_TYPE_RTK_FLOAT, ///< Receiving valid messages and 3D RTK Float
    GPS_OK_FIX_3D_RTK_FIXED = GPS_FIX_TYPE_RTK_FIXED, ///< Receiving valid messages and 3D RTK Fixed
};

struct GPS_State {
    uint8_t instance; // the instance number of this GPS

    // all the following fields must all be filled by the backend driver
    GPS_Status status;                  ///< driver fix status
    int32_t time;
    int32_t date;
    uint32_t time_week_ms;              ///< GPS time (milliseconds from start of GPS week)
    uint16_t time_week;                 ///< GPS week number
    Location location;                  ///< last fix location
    float ground_speed;                 ///< ground speed in m/sec
    float ground_course;                ///< ground course in degrees
    uint16_t hdop;                      ///< horizontal dilution of precision in cm
    uint16_t vdop;                      ///< vertical dilution of precision in cm
    uint8_t num_sats;                   ///< Number of visible satellites
    //Vector3f velocity;                  ///< 3D velocity in m/s, in NED format
    float speed_accuracy;               ///< 3D velocity RMS accuracy estimate in m/s
    float horizontal_accuracy;          ///< horizontal RMS accuracy estimate in m
    float vertical_accuracy;            ///< vertical RMS accuracy estimate in m
    bool have_vertical_velocity:1;      ///< does GPS give vertical velocity? Set to true only once available.
    bool have_speed_accuracy:1;         ///< does GPS give speed accuracy? Set to true only once available.
    bool have_horizontal_accuracy:1;    ///< does GPS give horizontal position accuracy? Set to true only once available.
    bool have_vertical_accuracy:1;      ///< does GPS give vertical position accuracy? Set to true only once available.
    uint32_t last_gps_time_ms;          ///< the system time we got the last GPS timestamp, milliseconds

};

struct GPS_timing {
    // the time we got our last fix in system milliseconds
    uint32_t last_fix_time_ms;

    // the time we got our last message in system milliseconds
    uint32_t last_message_time_ms;

    // delta time between the last pair of GPS updates in system milliseconds
    uint16_t delta_time_ms;
};

/// NMEA parser
///
class Cansat_GPS_NMEA
{


public:
	Cansat_GPS_NMEA(GPS_State &_state);

    /// Checks the serial receive buffer for characters,
    /// attempts to parse NMEA data and updates internal state
    /// accordingly.
    //bool        read();

	//static bool _detect(struct NMEA_detect_state &state, uint8_t data);

    //const char *name() const override { return "NMEA"; }
    /// Update the decode state machine with a new character
    ///
    /// @param	c		The next character in the NMEA input stream
    /// @returns		True if processing the character has resulted in
    ///					an update to the GPS state
    ///
    bool                        decode(char c);
private:
    /// Coding for the GPS sentences that the parser handles
    enum _sentence_types {      //there are some more than 10 fields in some sentences , thus we have to increase these value.
        _GPS_SENTENCE_RMC = 32,
        _GPS_SENTENCE_GGA = 64,
        _GPS_SENTENCE_VTG = 96,
        _GPS_SENTENCE_OTHER = 0
    };



    /// Return the numeric value of an ascii hex character
    ///
    /// @param	a		The character to be converted
    /// @returns		The value of the character as a hex digit
    ///
    int16_t                     _from_hex(char a);

    /// Parses the @p as a NMEA-style decimal number with
    /// up to 3 decimal digits.
    ///
    /// @returns		The value expressed by the string in @p,
    ///					multiplied by 100.
    ///
    static int32_t _parse_decimal_100(const char *p);

    /// Parses the current term as a NMEA-style degrees + minutes
    /// value with up to four decimal digits.
    ///
    /// This gives a theoretical resolution limit of around 1cm.
    ///
    /// @returns		The value expressed by the string in _term,
    ///					multiplied by 1e7.
    ///
    uint32_t    _parse_degrees();

    /// Processes the current term when it has been deemed to be
    /// complete.
    ///
    /// Each GPS message is broken up into terms separated by commas.
    /// Each term is then processed by this function as it is received.
    ///
    /// @returns		True if completing the term has resulted in
    ///					an update to the GPS state.
    bool                        _term_complete();

    /// return true if we have a new set of NMEA messages
    bool _have_new_message(void);

    uint8_t _parity;                                                    ///< NMEA message checksum accumulator
    bool _is_checksum_term;                                     ///< current term is the checksum
    char _term[15];                                                     ///< buffer for the current term within the current sentence
    uint8_t _sentence_type;                                     ///< the sentence type currently being processed
    uint8_t _term_number;                                       ///< term index within the current sentence
    uint8_t _term_offset;                                       ///< character offset with the term being received
    bool _gps_data_good;                                        ///< set when the sentence indicates data is good

    // The result of parsing terms within a message is stored temporarily until
    // the message is completely processed and the checksum validated.
    // This avoids the need to buffer the entire message.
    int32_t _new_time;                                                  ///< time parsed from a term
    int32_t _new_date;                                                  ///< date parsed from a term
    int32_t _new_latitude;                                      ///< latitude parsed from a term
    int32_t _new_longitude;                                     ///< longitude parsed from a term
    int32_t _new_altitude;                                      ///< altitude parsed from a term
    int32_t _new_speed;                                                 ///< speed parsed from a term
    int32_t _new_course;                                        ///< course parsed from a term
    uint16_t _new_hdop;                                                 ///< HDOP parsed from a term
    uint8_t _new_satellite_count;                       ///< satellite count parsed from a term
    uint8_t _new_quality_indicator;                                     ///< GPS quality indicator parsed from a term

    uint32_t _last_RMC_ms = 0;
    uint32_t _last_GGA_ms = 0;
    uint32_t _last_VTG_ms = 0;
    GPS_State &state;

    /// @name	Init strings
    ///			In ::init, an attempt is made to configure the GPS
    ///			unit to send just the messages that we are interested
    ///			in using these strings
    //@{
    //static const char _SiRF_init_string[];         ///< init string for SiRF units
    //static const char _MTK_init_string[];                  ///< init string for MediaTek units
    //static const char _ublox_init_string[];        ///< init string for ublox units
    //@}

    //static const char _initialisation_blob[];
};

#endif
