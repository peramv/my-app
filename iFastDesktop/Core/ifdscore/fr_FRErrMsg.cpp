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
// ^FILE   : fr_FRErrMsg.cpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 01 Apr 2003
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#undef fr_fr

MsgPair fr_fr[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "Impossible d'ouvrir le fichier contenant les messages d’erreur." ),
      I_( "  Vérifiez: 1) le Registre, ou 2) si le fichier contenant les messages d’erreur existe." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "Le code n'existe pas dans le fichier contenant les messages d’erreur." ),
      I_( "  Obtenez le fichier correcte contenant les messages d’erreur dans lequel le code existe." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Erreur grave pendant la lecture du fichier contenant les messages d’erreur." ),
      I_( "  Contactez le support technique." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "Code pays ISO n'existe pas dans le fichier contenant les messages d’erreur." ),
      I_( "  Contactez le support technique." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "La version du fichier contenant les messages d’erreur n'est pas reconnue." ),
      I_( "  Obtenez un fichier compatible contenant les messages d’erreur." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Mauvais fichier contenant les messages d’erreur." ),
      I_( "Obtenez un nouveau fichier contenant les messages d’erreur." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};




