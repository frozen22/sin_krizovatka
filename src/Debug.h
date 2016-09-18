/*
 * Soubor: Debug.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 * Datum:  2014-02-02
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <iostream>
#include <iomanip> // setprecision

#define OUT(message) std::cout << message << std::endl;

// -----------------------------------------------------------------------------

#define DBG_MSG
#ifdef DBG_MSG
    #define DBG(message) std::cerr << message << std::endl;
    #define DBG_NO_ENDL(message) std::cerr << message;
#else
    #define DBG(message)
    #define DBG_NO_ENDL(message)
#endif

//#define DBG_FUZZY_MSG
#ifdef DBG_FUZZY_MSG
    #define DBG_FUZZY(message) std::cerr << message << std::endl;
    #define DBG_FUZZY_NO_ENDL(message) std::cerr << message;
#else
    #define DBG_FUZZY(message)
    #define DBG_FUZZY_NO_ENDL(message)
#endif
            
// -----------------------------------------------------------------------------

#define DBG_ALERT_MSG
#ifdef DBG_ALERT_MSG
    #define DBG_ALERT(message) std::cerr << "!ALERT! " << message << " !ALERT!" << std::endl;
    #define DBG_ALERT_NO_ENDL(message) std::cerr << "!ALERT! " << message;
#else
    #define DBG_ALERT(message)
    #define DBG_ALERT_NO_ENDL(message)
#endif
// -----------------------------------------------------------------------------

#define ASSERT_NON_EXIT_MSG
#ifdef ASSERT_NON_EXIT_MSG
    #define ASSERT_NON_EXIT(condition, message)                                \
        if (condition)                                                         \
            std::cerr << "Soubor: " << __FILE__ << ":" << __LINE__             \
                      << " | condition: " << #condition                        \
                      << " | message: " << message << std::endl;
#else
    #define ASSERT_NON_EXIT(condition, message)
#endif

// -----------------------------------------------------------------------------

#define DBG_ASSERT_MSG
#ifdef DBG_ASSERT_MSG
    #define DBG_ASSERT(condition, message) \
        if (condition) std::cerr << message << std::endl;
#else
    #define DBG_ASSERT(condition, message)
#endif

// -----------------------------------------------------------------------------

#endif	/* DEBUG_H */

