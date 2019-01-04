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
// ^FILE   : AwdSource.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 21 Jul 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : AwdSource
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIAWDI_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef AWDSOURCE_HPP
   #include "awdsource.hpp"
#endif


//******************************************************************************
//              Public Methods
//******************************************************************************

AwdSource::AwdSource()
   : m_format( AwdSource::NO_FORMAT )
{
}


AwdSource::~AwdSource()
{
}

const AwdKey *AwdSource::getKey() const
{
   return m_data.getKey();
}

const AwdData &AwdSource::getData() const
{
   return m_data;
}

const DString &AwdSource::getSourceType() const
{
   return m_data.getObjt();
}

const DString &AwdSource::getLobValue( const DString &name ) const
{
   return m_data.getLobValue( name );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************


//******************************************************************************
//              Private Methods
//******************************************************************************


// These two methods are purposely not implemented.
//
// AwdSource::AwdSource( const AwdSource &copy )
// {
//    this->operator =( copy );
// }
//
// const AwdSource &AwdSource::operator=( const AwdSource &copy )
// {
//    if ( this == &copy )
//    {
//       return *this;
//    }
//
//    return *this;
// }


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
// $Log:   Y:/VCS/iFastAWD/diawdi/awdsource.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:18:20   kovacsro
// Initial revision.
// 
//    Rev 1.1   Aug 26 1999 12:58:42   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.0   Aug 04 1999 09:45:02   DMUM
//
//
//

