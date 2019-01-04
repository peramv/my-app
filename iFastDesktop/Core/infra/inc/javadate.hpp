#ifndef JAVADATE_HPP
#define JAVADATE_HPP
#  pragma message( "including "__FILE__ )

/** 
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

/**@pkg DICORE */    


#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif


#ifndef UTYPES_H
   #include <utypes.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif



class DICORE_LINKAGE JavaDate
{

// Implementation
public:
   /**
    * constructor
    */
   JavaDate();
   
   /**
    * constructor
    * 
    * @param jlTime - the offset in milliseconds from 1-1-1970
    */
   JavaDate( DIINT64 jlTime );
   
   /**
    * copy constructor
    * 
    * @param JavaDate
    */
   JavaDate( const JavaDate & copy );
   
   /**
    * destructor
    */
   virtual ~JavaDate();

   // Start with 1 (0 reserved)
   enum {
            JAVADATE_JNI_EXCEPTION_LOCATE = 1,
            JAVADATE_JNI_EXCEPTION_EXECUTE = 2
        } ElementalCondition;

    // Member functions
    // bool after(JavaDate *srcDate);

   /**
    *   compares whether the date of this object is 
    *   before the date of the parameter
    * 
    * @param srcDate
    * @return true, if "this" date is less than srcDate
    *         false, otherwise
    */
   bool before( JavaDate * srcDate );
   
   /**
    *   compares whether the date of this object is 
    *   equal to the date of the parameter
    * 
    * @param srcDate
    * @return true, if "this" date is equal to srcDate
    *         false, otherwise
    */
   bool equals( JavaDate * srcDate );
   
   /**
    * 
    * @return time as an offset in milliseconds from 1-1-1970
    */
   DIINT64 getTime( void );
   
   /**
    * set time
    * 
    * @param srcTime - an offset in milliseconds from 1-1-1970
    */
   virtual void setTime( DIINT64 srcTime );
   
   /**
    * 
    * @return a date string in full format
    */
   const DString toString(void);

   /**
    * subtraction operator
    * 
    * minuend (this) - subtrahend
    * 
    * @param subtrahend
    *
    * @return the offset in days
    */
   DIINT64 operator-( JavaDate & subtrahend );

   /**
    * subtraction
    * 
    * minuend (this) - subtrahend
    * 
    * @param subtrahend
    *
    * @return the offset in days
    */
   DIINT64 minus( JavaDate & subtrahend );

   /**
    * add the offset to this date and store the result
    * in the result parameter
    * 
    * @param offset - in days
    * @param result - where to store the result
    *
    * @return - the result
    */
   JavaDate & plus( DIINT64 offset,
                    JavaDate & result );

   /**
    * 
    * @return - this date as an offset in milliseconds from 
    *           1-1-1970
    */
   UDate getUDate() const { return cDate; };

protected:
   virtual void setUDate( void );
   virtual void setUDate( UDate argDate )
   {
      cDate = argDate;
   }
   

private:
   UDate cDate;

// Attributes
private:
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
// $Log:   Y:/VCS/iFastAWD/inc/javadate.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:00   kovacsro
//Initial revision.
// 
//    Rev 1.17   20 Mar 2001 16:39:12   DT14177
// fixed DDate == compare problem when
// an empty string is used to initialize a DDate
// 
//    Rev 1.16   11 Dec 2000 12:09:44   dt14177
// made the ddate comparison operators
// const and JavaDate::getUDate() const
// 
//    Rev 1.15   Jun 27 2000 17:02:06   DT14177
// moved some date member variables from JavaDate to DDate
// 
//    Rev 1.14   Jun 13 2000 13:15:40   DT14177
// fixed: addDays(), subtractDays(), getDayOfYearFromDate().
// added conditional operators
// 
//    Rev 1.13   Jun 01 2000 10:56:48   DT14177
// added javadoc comments
// 
//    Rev 1.12   May 11 2000 08:26:08   DT14177
// lots of fixes to DDate
// 
//    Rev 1.11   Apr 10 2000 16:57:30   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.10   10 Apr 2000 10:30:50   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.9   06 Apr 2000 14:15:32   dt20842
// Changed to ICU
// 
//    Rev 1.8   Sep 16 1999 16:28:16   DT14177
// memory leak cleanup
// 
//    Rev 1.7   Jul 16 1999 11:26:40   DT14177
// Added getOffset() to dDate and minus() to JavaDate
// 
//    Rev 1.6   Jun 18 1999 17:33:52   DT14177
// removed the after() method from the header
// 
//    Rev 1.5   Jun 01 1999 17:22:06   DTWK
// General cleanup
// 
//    Rev 1.4   May 12 1999 09:21:58   DT20842
// Added elemental conditions
// 
//    Rev 1.3   Apr 08 1999 13:02:14   DMUM
// Added import/export macros
//
//    Rev 1.2   Apr 02 1999 11:26:22   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.1   Mar 23 1999 09:43:26   DT20842
// Changed from long to DIINT64
//
//    Rev 1.0   Mar 04 1999 14:40:12   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif