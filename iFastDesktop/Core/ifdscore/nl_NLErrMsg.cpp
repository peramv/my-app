//************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//************************************************************************
//
// ^FILE   : nl_NLErrMsg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Aug, 2004
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#undef nl_nl

MsgPair nl_nl[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "Kon het volgende bestand met foutcondities niet openen: " ),
      I_( "  Controleer: 1) het register, of 2) of het bestand met foutcondities bestaat." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "De code is niet gevonden in het bestand met foutcondities." ),
      I_( "  Zorg voor het juiste bestand met foutcondities dat de code bevat." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Ernstige fout opgetreden bij lezen van bestand met foutcondities." ),
      I_( "  Neem contact op met de helpdesk." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "ISO-landcode niet gevonden in het bestand met foutcondities." ),
      I_( "  Neem contact op met de helpdesk." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "Versie van bestand met foutcondities niet herkend.  " ),
      I_( "Zorg voor compatibel bestand met foutcondities." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Beschadigd bestand met foutcondities.  " ),
      I_( "Maak een nieuw bestand met foutcondities." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/nl_NLErrMsg.cpp-arc  $
// 
//    Rev 1.1   Aug 30 2004 16:00:50   popescu
// PET 991, FN 02, added support for Dutch and Italian
// 
//    Rev 1.0   Aug 27 2004 17:41:12   popescu
// Initial revision.
// 
//
//



