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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : Awd23Source.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 29 Jul 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : Awd23Source
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIAWD23_DLL

#include "stdafx.h"
#include <fstream>

//******************************************************************************
//
// Inlcude this header before ANYTHING that uses the standard C++ library
//
//    This header includes all the SOM headers for AWD.
//
      #include "sominc.h"

//
//******************************************************************************

#ifndef EXCEPTIONHANDLER_HPP
   #include "exceptionhandler.hpp"
#endif
#ifndef AWD23SOURCE_HPP
   #include "awd23source.hpp"
#endif
#ifndef AWD23KEY_HPP
   #include "awd23key.hpp"
#endif

namespace
{
   const I_CHAR *ec = I_("Awd23Source");
   Environment * ev = NULL;

   const DStringA strOBJF = "OBJF";
}

//******************************************************************************
//              Public Methods
//******************************************************************************

Awd23Source::Awd23Source()
{
}

Awd23Source::~Awd23Source()
{
}

void Awd23Source::displayImage()
{
   const AwdKey *pKey = m_data.getKey();

   if ( pKey && pKey->isKey() )
   {
      const Awd23Key *p23Key = static_cast<const Awd23Key *>( pKey );
      AWDBase *pBase = p23Key->getAwdBaseObj();

      if ( pBase->isSourceObject( ev ) )
      {
         AWDSource *pSource = static_cast<AWDSource *>( pBase );

         try
         {
            pSource->displayImage( ev );
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("displayImage()") )
      }
   }
}

void Awd23Source::establishFormat()
{
   const DString& strSourceType = m_data.getLobValue( strOBJF );

   if ( !strSourceType.empty() )
   {
      m_format = (AwdSource::ObjectFormat)strSourceType[0];
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************



//******************************************************************************
//              Private Methods
//******************************************************************************

// This copy constructor is not meant to be used.  By not implementing it
// linker errors will result when someone attempts to use this operator.
//
//Awd23Source::Awd23Source( const Awd23Source &copy )
//{
//   *this = copy;
//}



// This copy operator is not meant to be used.  By not implementing it
// linker errors will result when someone attempts to use this operator.
//
//const Awd23Source &Awd23Source::operator=( const Awd23Source &copy )
//{
//   if ( this == &copy )
//      return *this;
//
//   AwdSource::operator=( copy );
//
//   return *this;
//}



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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23source.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:16:36   kovacsro
// Initial revision.
// 
//    Rev 1.1   Aug 26 1999 12:55:40   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of 
// a service.
//
//    Rev 1.0   Aug 04 1999 09:49:58   DMUM
//
//
//

