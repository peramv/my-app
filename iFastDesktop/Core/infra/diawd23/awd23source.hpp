#ifndef AWD23SOURCE_HPP
#define AWD23SOURCE_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef AWDSOURCE_HPP
   #include "awdsource.hpp"
#endif

#undef DIAWD23_LINKAGE
#ifdef DIAWD23_DLL
   #define DIAWD23_LINKAGE CLASS_EXPORT
#else
   #define DIAWD23_LINKAGE CLASS_IMPORT
#endif

class Awd23Source : public AwdSource
{
   public:
      /**
       * Default constructor
       */
      Awd23Source();

      /**
       * Destructor
       */
      virtual ~Awd23Source();


   // Virtual
   public:
      /**
       * wrapper for the AWD api
       */
      virtual void displayImage();

   // For Awd23Interface use only
   public:
      AwdData & exposeData()
      {
         return m_data;
      }

      void setFormat( AwdSource::ObjectFormat format )
      {
         m_format = format;
      }

      /**
       * Copies the LOB format
       */
      void establishFormat();

   private:
      Awd23Source( const Awd23Source &copy );
      const Awd23Source &operator=( const Awd23Source &copy );
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23source.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:16:38   kovacsro
//Initial revision.
// 
//    Rev 1.1   06 Dec 2000 11:32:42   dt14177
// cleanup
// 
//    Rev 1.0   Aug 04 1999 09:50:02   DMUM
//  
//
//

#endif // AWD23SOURCE_HPP

