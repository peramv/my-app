#ifndef CASEINSENSITIVECOMPARE_HPP
#define CASEINSENSITIVECOMPARE_HPP

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
 *    Copyright 1999 by DST Systems, Inc.
 */


#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif



/**
 * Predicate for DataBroker collections that are case-insensitive.
 * This class is designed for use in DataBroker only. This header is
 * exposed only so that users of Data objects may compile.
 * 
 * @author DST Systems Inc
 */
class DIDBRKR_LINKAGE CaseInsensitiveCompare
{
public:
   CaseInsensitiveCompare();

   bool operator() ( const DString& x, const DString& y ) const;


private:
};


#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/caseinsensitivecompare.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:10   kovacsro
//Initial revision.
//
//   Rev 1.1   Mar 02 2001 14:13:40   dt24433
//Changed to cache case sensitivity flag for performance.
//
//   Rev 1.0   Jun 08 2000 10:27:50   dtwk
// 
// 



