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
// ^FILE   : it_ITErrMsg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Aug, 2004
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#undef it_it

MsgPair it_it[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "Non ha potuto aprire l'archivio di circostanza: " ),
      I_( "  Controllo: 1) la registrazione, o 2) vedere se l'archivio di circostanza esiste." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "Non ha trovato il codice nell'archivio di circostanza." ),
      I_( "  Ottenga l'archivio corretta di circostanza che contiene il codice." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "L'errore severo ha incontrato la lettura dell'archivio di circostanza." ),
      I_( "  Mettasi in contatto con lo scrittorio di sostegno." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "Codice di paese di iso non trovato nell'archivio di circostanza." ),
      I_( "  Mettasi in contatto con lo scrittorio di sostegno." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "La versione dell'archivio di circostanza non è riconosciuta. " ),
      I_( "Ottenga l'archivio compatibile di circostanza." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Archivio di circostanza difettoso.  " ),
      I_( "Ottenga una nuova archivio di circostanza." )
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
// $Log:   Y:/VCS/BF Core/ifdscore/it_ITErrMsg.cpp-arc  $
// 
//    Rev 1.2   Aug 30 2004 16:10:18   popescu
// PET 991, FN 02, added support for Dutch and Italian
// 
//    Rev 1.1   Aug 30 2004 16:00:44   popescu
// PET 991, FN 02, added support for Dutch and Italian
// 
//    Rev 1.0   Aug 27 2004 17:41:46   popescu
// Initial revision.
// 
//
//



