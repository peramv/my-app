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
// ^FILE   : es_esErrMsg.cpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 07Aug2003
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#undef es_es

MsgPair es_es[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "No se pudo abrir el archivo de condición: " ),
      I_( "  Verifique: 1) el registro, o 2) si existe el archivo de condición." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "No se encontró el código en el archivo de condición." ),
      I_( "  Busque el archivo de condición correcto que contiene el código." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Se encontró un error grave al leer el archivo de condición." ),
      I_( "  Póngase en contacto con el soporte técnico." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "No se encontró el código de país ISO en el archivo de condición." ),
      I_( "  Póngase en contacto con el soporte técnico." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "No se reconoce la versión del archivo de condición." ),
      I_( "Busque el archivo de condición compatible." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Archivo de condición no válido." ),
      I_( "Busque otro archivo de condición." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};




