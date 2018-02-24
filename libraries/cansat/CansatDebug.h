/**
 * @file       CansatDebug.h
 * @author     dongwon Lee
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       Feb 2018
 * @brief      Debug utilities
 *
 */

#ifndef CansatDebug_h
#define CansatDebug_h


#include <stddef.h>
#include <inttypes.h>
#include <assert.h>

typedef uint32_t millis_time_t;



#define CansatMillis() millis()


#include <Arduino.h>

#include <avr/pgmspace.h>




// Diagnostic defines

//#define CANSAT_FATAL(msg)     { CANSAT_LOG1(msg); CansatFatal(); }
//#define CANSAT_LOG_RAM()      { CANSAT_LOG2(CANSAT_F("Free RAM: "), CansatFreeRam()); }
//#define CANSAT_LOG_FN()       CANSAT_LOG3(CANSAT_F(__FUNCTION__), '@', __LINE__);
//#define CANSAT_LOG_TROUBLE(t) CANSAT_LOG2(CANSAT_F("Trouble detected: email to cchamchi@naver.com-"), t)

#ifndef CANSAT_PRINT
#undef CANSAT_DEBUG
#endif

#ifdef CANSAT_DEBUG_ALL
#define CANSAT_DEBUG
#endif

#ifdef CANSAT_PRINT

    #define CANSAT_LOG(msg)  {CANSAT_PRINT.print('[');CANSAT_PRINT.print(millis());CANSAT_PRINT.print(F("] ")); CANSAT_PRINT.println(F(msg));   }

    #define CANSAT_ASSERT(expr) { if(!(expr)) { CANSAT_LOG("Assertion failed."); CANSAT_DBG_BREAK()} }


#ifdef CANSAT_DEBUG
        #define CANSAT_DBG_DUMP(msg, addr, len) if (len) { CANSAT_PRINT.print(F(msg)); CANSAT_PRINT.write((uint8_t*)addr, len); CANSAT_PRINT.println(); }
        #define CANSAT_DBG_BREAK()    { for(;;); }
#endif


#endif //#ifdef CANSAT_PRINT

#ifndef CANSAT_LOG
    #define CANSAT_LOG(...)


#endif

#ifndef CANSAT_DBG_BREAK
    #define CANSAT_DBG_BREAK()
    #define CANSAT_ASSERT(expr)
    #define CANSAT_DBG_DUMP(msg, addr, len)
#endif

#endif
