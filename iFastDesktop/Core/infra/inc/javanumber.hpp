#ifndef JAVANUMBER_HPP
#define JAVANUMBER_HPP
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

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE JavaNumber
{

// Implementation
public:
   enum
   {
      JAVANUMBER_CONFIG_ERROR = 1
   };

   /**
    * constructor
    */
   JavaNumber()
   {
      m_double = 0.0;
      m_longInt = 0;
   }

   /**
    * constructor
    * 
    * @param parm
    */
   JavaNumber( double parm )
   {
      m_double = parm;
      m_longInt = (long long)parm;
   }

   /**
    * constructor
    * 
    * @param parm
    */
   JavaNumber( __int64 parm )
   {
      m_double = (double)parm;
      m_longInt = parm;
   }

   /**
    * destructor
    */
   virtual ~JavaNumber()
   {
   }

   /**
    * truncates a long to a byte
    * 
    * @return 
    */
   DIJAVABYTE byteValue()
   {
      return (DIJAVABYTE)m_longInt;
   }

   /**
    * returns the value as a double
    * 
    * @return 
    */
   double doubleValue()
   {
      return m_double;
   }

   /**
    * returns the value as a float
    * 
    * @return 
    */
   float floatValue()
   {
      return (float)m_double;
   }

   /**
    * returns the value as an int
    * 
    * @return 
    */
   DIJAVAINT intValue()
   {
      return (long)m_longInt;
   }

   /**
    * returns the value as a long
    * 
    * @return 
    */
   DIINT64 longValue()
   {
      return m_longInt;
   }

   /**
    * returns the value as a short
    * 
    * @return 
    */
   short shortValue()
   {
      return (short)m_longInt;
   }


private:

// Attributes
private:

   double  m_double;
   __int64 m_longInt;
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
// $Log:   Y:/VCS/iFastAWD/inc/javanumber.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:04   kovacsro
//Initial revision.
// 
//    Rev 1.4   Jun 01 2000 14:51:00   DT14177
// added javadoc comments
// 
//    Rev 1.3   Apr 10 2000 16:38:54   DT14177
// ICU syncup
// 
//    Rev 1.2   Jun 06 1999 13:24:02   DTWK
// Minor tweaks
// 
//    Rev 1.1   Jun 01 1999 17:22:36   DTWK
//  
// 
//    Rev 1.0   May 24 1999 10:26:32   DTWK
//  
//
//

#endif