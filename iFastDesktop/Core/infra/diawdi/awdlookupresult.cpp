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
// ^FILE   : AwdLookupResult.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 6 Jan 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : AwdLookupResult
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

#ifndef AWDLOOKUPRESULT_HPP
   #include "awdlookupresult.hpp"
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

AwdLookupResult::AwdLookupResult()
   : m_unit( I_("") ),
     m_wrkt( I_("") ),
     m_objt( I_("") ),
     m_stat( I_("") ),
     m_queu( I_("") ),
     m_crda( I_("") ),
     m_reco( I_("") ),
     m_crno( I_("") )
{
}

AwdLookupResult::~AwdLookupResult()
{
}

AwdLookupResult::AwdLookupResult( const AwdLookupResult &copy )
{
   this->operator =( copy );
}

DString AwdLookupResult::getBusinessArea() const
{
   return m_unit;
}

DString AwdLookupResult::getWorkType() const
{
   return m_wrkt;
}

DString AwdLookupResult::getSourceType() const
{
   return m_objt;
}

DString AwdLookupResult::getStatus() const
{
   return m_stat;
}

DString AwdLookupResult::getQueue() const
{
   return m_queu;
}

DString AwdLookupResult::getCreateDateTime() const
{
   return m_crda;
}

DString AwdLookupResult::getRecordCode() const
{
   return m_reco;
}

DString AwdLookupResult::getCreateNode() const
{
   return m_crno;
}

AwdLookupResult &AwdLookupResult::operator=( const AwdLookupResult &copy )
{
   if ( this != &copy )
   {
      this->m_unit = copy.m_unit;
      this->m_wrkt = copy.m_wrkt;
      this->m_objt = copy.m_objt;
      this->m_stat = copy.m_stat;
      this->m_queu = copy.m_queu;
      this->m_crda = copy.m_crda;
      this->m_reco = copy.m_reco;
      this->m_crno = copy.m_crno;
   }

   return *this;
}


//******************************************************************************
//              Protected Methods
//******************************************************************************



//******************************************************************************
//              Private Methods
//******************************************************************************

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
// $Log:   Y:/VCS/iFastAWD/diawdi/awdlookupresult.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:18:18   kovacsro
// Initial revision.
// 
//    Rev 1.1   Apr 14 1999 12:30:32   DMUM
//  
// 
//    Rev 1.1   Apr 09 1999 13:49:06   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:19:24   DMUM
//
//
//    Rev 1.0.1.0   Feb 19 1999 07:48:16   DMUM
// Added lookupSource()
//
//    Rev 1.0   Jan 20 1999 09:09:34   DMUM
//
//
//

