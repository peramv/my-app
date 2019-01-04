/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
 *******************************************************************************/
#pragma once
#include <xercesc/sax/attributelist.hpp>

namespace xp
{
   enum ProcessAction
   {
      PROC_ACTION_VALIDATE_ONLY = 0,
      PROC_ACTION_SUBMIT,
      // add new action above here
      PROC_ACTION_COUNT
   };

   enum CBOAction
   {
      CBO_ACTION_QUERY = 0,
      CBO_ACTION_ADD,
      CBO_ACTION_UPDATE,
      CBO_ACTION_DELETE,
      CBO_ACTION_REPLACE,
      CBO_ACTION_PROPERTIES,
      // add new action above here
      CBO_ACTION_COUNT
   };

   static DString valueOf( const DString &tagName, xercesc::AttributeList &attributes )
   {
        std::string str = tagName.asA();
        const char* const pStr = str.c_str();

        const I_CHAR *value = (I_CHAR*)(attributes.getValue( pStr ));

      if( value == NULL )
         return(NULL_STRING);

      return(value);
   }
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/xparser/XParserCommon.hpp-arc  $
//
//   Rev 1.3   Jan 27 2005 15:47:42   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.2   Mar 09 2004 11:01:54   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.1   Oct 09 2002 17:43:28   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Sep 19 2002 15:22:12   IVESPAUL
//Initial revision.
//
