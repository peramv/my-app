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
// ^FILE   : de_DEErrMsg.cpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 01 Apr 2003
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#undef de_de

MsgPair de_de[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "Folgende Bedingungsdatei konnte nicht geöffnet werden: " ),
      I_( "  Überprüfen Sie: 1) die Registrierung oder 2) ob die Bedingungsdatei existiert." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "Code in der Bedingungsdatei nicht gefunden." ),
      I_( "  Suchen Sie die richtige Bedingungsdatei, die den Code enthält." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Schwerer Fehler beim Lesen der Bedingungsdatei." ),
      I_( "  Setzten Sie sich mit dem Kundendienst in Verbindung." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "ISO-Ländercode in der Bedingungsdatei nicht gefunden." ),
      I_( "  Setzten Sie sich mit dem Kundendienst in Verbindung." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "Version der Bedingungsdatei nicht erkannt. " ),
      I_( "  Suchen Sie eine kompatible Bedingungsdatei." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Beschädigte Bedingungsdatei." ),
      I_( "  Suchen Sie eine neue Bedingungsdatei." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};




