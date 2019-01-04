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
// ^FILE   : Awd23Key.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 24 Apr 97
//
// ----------------------------------------------------------
//
// ^CLASS    : Awd23Key
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
#ifndef AWD23KEY_HPP
   #include "awd23key.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

namespace
{
   const I_CHAR *ec = I_("Awd23Key");

   Environment * ev = NULL;
}
//******************************************************************************
//              Constructors and Destructor
//******************************************************************************

Awd23Key::Awd23Key()
   : m_pObj( NULL ), m_isKey( false )

{
}

Awd23Key::Awd23Key( AWDOBJKEY &key )
   : m_key( key ), m_pObj( NULL ), m_isKey( false )
{
   retrieveObject();
   m_isKey = NULL != m_pObj;
}

Awd23Key::Awd23Key( AWDBase *pObj )
   : m_pObj( NULL ), m_isKey( false )
{
   m_pObj = copyObject( pObj );
   m_isKey = NULL != m_pObj;

   if ( m_isKey )
   {
      try
      {
         m_pObj->getKeyStrct( ev, (AWD_PAWDOBJECTKEYSTRCT)&m_key );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("Awd23Key::Awd23Key()") )
   }
}

Awd23Key::Awd23Key( const Awd23Key *pKey )
   : m_pObj( NULL ), m_isKey( false )
{
   copyKey( pKey );
}

Awd23Key::~Awd23Key()
{
   if ( m_pObj )
   {
      delete m_pObj;
   }
}

//******************************************************************************
//              Public Virtual Methods
//******************************************************************************

bool Awd23Key::isKey() const
{
   return ( m_isKey );
}

AwdKey *Awd23Key::makeCopy() const
{
   Awd23Key *pCopy = new Awd23Key;

   ASSERT_NEW( pCopy, ec, I_("makeCopy()") )

   pCopy->copyKey( this );

   return pCopy;
}

DString Awd23Key::getCreateDateTime() const
{
   return DStringA( m_key.crdattim, CRDATTIM_LEN );
}

DString Awd23Key::getRecordCode() const
{
   return DString( 1, m_key.recordcd );
}

DString Awd23Key::getCreateNode() const
{
   return DStringA( m_key.crnode, CRNODE_LEN );
}

bool Awd23Key::operator ==( const AwdKey &key ) const
{
   const Awd23Key * p23Key = static_cast<const Awd23Key *>( &key );
   return 0 == memcmp( &(this->m_key), &(p23Key->m_key), sizeof( AWDOBJKEY ) );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AWDOBJ Awd23Key::getAwdObjStruct() const
{
   AWDOBJ objStruct;

   try
   {
      m_pObj->getStructure( ev, (AWD_PAWDOBJECTSTRCT)&objStruct );
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("Awd23Key::getStruct()") )

   return objStruct;
}


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Key::copyKey
//
// ^DESCRIPTION : Copies the contents of the Awd23Key passed in
//
// ^PARAMETERS  :
//   ^^ const Awd23Key *pOriginal - Key to be copied
//
// ^RETURNS     : void -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
void Awd23Key::copyKey( const Awd23Key *pOriginal )
{
   if ( this != pOriginal )
   {
      this->m_key   = pOriginal->m_key;
      this->m_isKey = pOriginal->m_isKey;
      this->m_pObj  = NULL;

      if ( pOriginal->m_pObj )
      {
         this->m_pObj = copyObject( pOriginal->m_pObj );
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Key::retrieveObject
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void Awd23Key::retrieveObject()
{
   try
   {
      AWDObjectFactory* pObjFact = new AWDObjectFactory();

      ASSERT_NEW( pObjFact, ec, I_("getFactory()") )

      // Retrieve the object
      m_pObj = pObjFact->makeFromKey( ev, (AWD_PAWDOBJECTKEYSTRCT)&m_key );

      ASSERT_NEW( m_pObj, ec, I_("retrieveObject()") )

      delete pObjFact;
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("retrieveObject()") )
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Key::copyObject
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ AWDBase *pCopy -
//
// ^RETURNS     : AWDBase * -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
AWDBase *Awd23Key::copyObject( AWDBase *pCopy )
{
   AWDBase *pObj = NULL;

   try
   {
      AWDObjectFactory* pObjFact = new AWDObjectFactory();

      ASSERT_NEW( pObjFact, ec, I_("copyObject()") )

      // Retrieve the object
      pObj = pObjFact->makeFromObject( ev, pCopy );

      ASSERT_NEW( pObj, ec, I_("copyObject()") )

      delete pObjFact;
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("copyObject()") )

   return pObj;
}


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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23key.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:16:28   kovacsro
// Initial revision.
// 
//    Rev 1.5   Apr 09 1999 13:50:36   DMUM
// Sync up with 1.6.x
//
//    Rev 1.3.1.0   Mar 31 1999 13:20:52   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.1   Jan 20 1999 16:41:54   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.0   Sep 29 1998 14:37:04   DTWK
//
//
//    Rev 1.1   Sep 09 1998 08:00:22   DMUM
// Added == operator
//
//    Rev 1.0   29 Jul 1998 20:28:12   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.3   Dec 30 1997 12:25:50   dmum
// Cleanup
//
//    Rev 1.2   Dec 16 1997 11:21:16   dmum
// No longer interfaces with AWD32.EXE
//
// Now uses AWD 2.3.0b directly through SOM and APIs
//
//    Rev 1.1   10 Nov 1997 15:20:06   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.0   03 Sep 1997 14:21:22   dmum
//
//
//
//


