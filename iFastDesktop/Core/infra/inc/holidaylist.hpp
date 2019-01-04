#ifndef HOLIDAYLIST_HPP
#define HOLIDAYLIST_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DITABUSCORE */ 

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef LISTBASE_HPP
   #include "listbase.hpp"
#endif



/**@#-*/  // forward declarations
class HolidayListImpl;
/**@#+*/

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE HolidayList: public ListBase
{
        public:

                bool isHoliday( const DString & strDate ) const;
                bool isHoliday( long lDateOffset ) const;
                static const HolidayList * getInstance( void );
                static void killInstance( void );

        private://methods
                 // Constructors
       HolidayList();  // Default Constructor
       HolidayList( const HolidayList & copy ); // Copy Constructor
       HolidayList& operator=( const HolidayList & copy ); //equals operator overload
       
       ~HolidayList(); // Destructor

   private://data
        
       static HolidayList * _pInstance;


};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/holidaylist.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:34   kovacsro
//Initial revision.
// 
//    Rev 1.2   01 Feb 2001 16:20:08   dt14177
// cleanup

#endif // HOLIDAYLIST_HPP

