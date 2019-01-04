#pragma message( "including "__FILE__ )

#ifndef CICSREQUESTFORMATTER_HPP
   #define CICSREQUESTFORMATTER_HPP

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

   #pragma message( "including "__FILE__ )

   #ifndef DIPORT2_H
      #include "diport2.h"
   #endif

extern "C"
{
   #ifndef INCLUDED_VM_H
      #define INCLUDED_VM_H
      #include "vm.h"
   #endif
   #ifndef INCLUDED_VMDLL_H
      #define INCLUDED_VMDLL_H
      #include "vmdll.h"
   #endif
   #ifndef INCLUDED_VMDST_H
      #define INCLUDED_VMDST_H
      #include "vmdst.h"
   #endif
}

   #ifndef CONDITION_HPP
      #include "condition.hpp"
   #endif

   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

/**
 * A simple wrapper around the View Manager application response with methods
 * to extract some TA2000 specific data.
 */
class DIVIEW_LINKAGE CICSRequestFormatter
{
public:
   /**
    * Constructor.
    *
    * @param viewName       Name of the view.
    * @param operatorId     OperatorId.
    * @param system         Name of the system.
    * @param dataLength     Length of the data in bytes.
    * @param data           Pointer to data.
    */
   CICSRequestFormatter( const DStringA & viewName,
                  const DStringA & operatorId,
                  const DStringA & system,
                  unsigned long dataLength,
                  const char * data );

   /**
    * Destory object.
    */
   virtual ~CICSRequestFormatter();

   /**
    * Call this to format a TA2000 host request.  This method should be
    * called before any of the other methods are called (such as getResponse).
    *
    * @return NO_CONDITION if ok, otherwise a higher severity.
    */
   SEVERITY format();

   unsigned long getBufferLength( void ) const;

   const char * getBuffer( void ) const;

private:
   enum CONSTANTS
   {
      LEN_PROJECT_ID    = 4,
      LEN_VIEW_NAME     = 8,
      LEN_OPERATOR_ID   = 8,
      LEN_USER_DATA_LEN = 3,
      LEN_PB00250       = LEN_PROJECT_ID + LEN_VIEW_NAME +
                          LEN_OPERATOR_ID + LEN_USER_DATA_LEN,
      LEN_SYSTEM        = 4
   };

   DStringA _viewName;
   DStringA _operatorId;
   DStringA _system;
   unsigned long _dataLength;
   const char * _data;
   unsigned long _bufferLength;
   char * _buffer;
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
// $Log:   Y:/VCS/iFastAWD/inc/CICSRequestFormatter.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:20   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:42   DT11159
// 
//
//

#endif
