//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1996 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DataBroker.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/24/96
//
// ----------------------------------------------------------
//
// ^CLASS : DataBroker
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DATABROKER_HPP
   #include "databroker.hpp"
#endif

extern CLASS_EXPORT const I_CHAR *DIDBRKR_COMPONENT_NAME = I_("DIDBRKR");



//******************************************************************************
//              Public Methods
//******************************************************************************

DataBroker::DataBroker()
{
}



DataBroker::~DataBroker()
{
}



bool DataBroker::receive( const Data &queryData, Data &receivedData,
                          bool doBuffer )
{
/*   if ( doBuffer )
   {
      DString key = queryData.getKey();
      DString dataType = receivedData.getProperties()->getId();
      DataMap::iterator mapIter;

      key += dataType;

      mapIter = _buffers.find( key );
      if ( mapIter == _buffers.end() )
      {
         // match dataType with external table of ids & types & algorithm DLL
         // load DLL & call algorithm OR call algorithm already assoc through
         // earlier constructor of Data class (associated with Properties)
         // view algorithm( receivedData ):
         BYTES buffer;
         // Call VM...
         receivedData.setFields( buffer );

         _buffers.insert( receivedData );  // is this a copy???
      }
      else
      {
         receivedData = *mapIter;
      }
   }
*/
   return true;
}



bool update( const Data &updateData )
{
   return true;
}



//******************************************************************************
//              Protected Methods
//******************************************************************************



//******************************************************************************
//              Private Methods
//******************************************************************************

//DataBroker::DataBroker( const DataBroker &copy )
//{
//   ;   // Copy constructor not meant to be used.  Cause linker error.
//}



//DataBroker &DataBroker::operator=( const DataBroker &copy )
//{
//   return *this;   // Copy operator not meant to be used.  Cause linker error.
//}



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
// $Log:   Y:/VCS/iFastAWD/didbrkr/databroker.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:18   kovacsro
// Initial revision.
// 
//    Rev 1.4   Jul 22 1999 11:26:42   DMUM
// Condition re-work
// 
//    Rev 1.3   Mar 05 1999 10:25:20   DCYK
// Changes for I18N.
// 
// 
//    Rev 1.2   Jan 28 1999 14:03:44   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 15:42:50   DMUM
//
//
//    Rev 1.1   Nov 10 1997 14:46:58   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.0   Jun 13 1997 16:31:24   DTWK
//
//
//    Rev 1.3   Feb 11 1997 14:11:00   dcyk
// Added #include "srcprag.h" to suppress
// compiler warnings.
//
//
//    Rev 1.2   Dec 31 1996 13:25:32   DRUS
// Fixed PVCS comment error (again).
//
//    Rev 1.1   Nov 21 1996 14:38:08   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:08   DRUS
//
//
//

