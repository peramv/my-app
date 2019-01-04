#ifndef AWDRESPONSEFORMATTER_HPP
#define AWDRESPONSEFORMATTER_HPP

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
#define INCL_DOSQUEUES
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

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif

/**
 * A simple wrapper around the View Manager application response with methods
 * to extract some AWD specific data.
 */
class DIVIEW_LINKAGE AwdResponseFormatter
{
public:
   /**
    * Constructor.
    *
    * @param response  - Pointer to a View Manager application response.
    * @param message   - Error message if View Manager returned an error.
    */
   AwdResponseFormatter::AwdResponseFormatter( const void * response,
                                               const DString & message );

   /**
    * Destory object and shutdown AWD View connection.
    */
   virtual ~AwdResponseFormatter();

   /**
    * Call this to parse the raw AWD host response.  This method should be
    * called before any of the other methods are called (such as
    * getRepeatRecSize).
    *
    * @return NO_CONDITION if ok, otherwise a higher severity.
    * @exception ConditionException if AWD / View had an error.
    */
   SEVERITY parse();

   /**
    * Get the raw response buffer from the Host.
    *
    * @param pBuf   - a pointer to the buffer that will receive the data
    * @param ulBufSize the size of the buffer in bytes
    * @return true if successful, false otherwise.
    */
   bool getBuffer( char * pBuf, unsigned long ulBufSize ) const;

   /**
    * Get the length of the raw response buffer from the host.
    *
    * @return the length in bytes.
    */
   unsigned long getBufferLength() const;

   /**
    * Copy the view's fixed data into a buffer.
    *
    * @param pBuf - the buffer to copy the data into.
    * @param ulBufSize - the size of the buffer
    * @return true if some or all of the data was copied, false otherwise.
    */
   bool getFixedData( unsigned char * pBuf,
                      unsigned long ulBufSize ) const;

   /**
    * Returns the length of the fixed area of the last view.
    *
    * @return the size in bytes.
    */
   unsigned long getFixedLenBufSize( void ) const;

   /**
    * Get the number of repeat record in the last view.
    *
    * @return the number.
    */
   unsigned long getNumRepeatRec( void ) const;

   /**
    * Gets the primary return code from AWD View. See AWD View docs.
    *
    * @return the return code.
    */
   unsigned short getRcPrimary( void ) const;

   /**
    * Gets the Secondary return code from AWD View. See AWD View
    * docs.
    *
    * @return the return code.
    */
   unsigned short getRcSecondary( void ) const;

   /**
    * Get the error message from the most recent View Manager call.
    *
    * @return error message.
    */
   const DString & getErrorText( ) const
   {
      return( _message );
   }

   /**
    * Copy one specific repeat record into a buffer.
    *
    * @param ulRecordNumber - 1-based index.
    * @param pBuf - the buffer to receive the data
    * @param ulBufSize - the size of the buffer
    * @return true if some of the data was copied, false otherwise.
    */
   bool getRepeatRecord( unsigned long ulRecordNumber,
                         char * pBuf,
                         unsigned long ulBufSize ) const;

   /**
    * Get the size of a single repeat record from the last view.
    *
    * @return the number of bytes.
    */
   unsigned long getRepeatRecSize( void ) const;

   /**
    * Copy the view's repeat data into a buffer.
    *
    * @param  pBuf the buffer to copy the data into.
    * @param ulBufSize the size of the buffer
    * @return true if some or all of the data was copied. False otherwise.
    */
   bool getVarData( unsigned char * pBuf,
                    unsigned long ulBufSize ) const;

   /**
    * Returns the size of the all of the repeats combined
    * from the last view.
    *
    * @return the size in bytes.
    */
   unsigned long getVarLenBufSize( void ) const;

   /**
    * Get the return code sent from the host.  These are AWD return codes
    * like "OK", "DATA-NOT-FOUND", "SEVERE-ERROR".
    *
    * @return the return code
    */
   unsigned short getViewReturnCode( void ) const;

private:
   PVMAPPRESP     _response;
   VMDSTRESP      _vmResp;
   const DString  _message;
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
// $Log:   Y:/VCS/iFastAWD/inc/awdresponseFormatter.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:52   kovacsro
//Initial revision.
//
//   Rev 1.2   Jun 26 2001 12:57:16   DT11159
//Deleted method getFormattedErrorMessage( ).
//
//   Rev 1.1   Jun 08 2001 19:14:14   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 15:53:40   DT11159
//
//
//

#endif
