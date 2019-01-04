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
      I_( "No se pudo abrir el archivo de condici�n: " ),
      I_( "  Verifique: 1) el registro, o 2) si existe el archivo de condici�n." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "No se encontr� el c�digo en el archivo de condici�n." ),
      I_( "  Busque el archivo de condici�n correcto que contiene el c�digo." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Se encontr� un error grave al leer el archivo de condici�n." ),
      I_( "  P�ngase en contacto con el soporte t�cnico." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "No se encontr� el c�digo de pa�s ISO en el archivo de condici�n." ),
      I_( "  P�ngase en contacto con el soporte t�cnico." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "No se reconoce la versi�n del archivo de condici�n." ),
      I_( "Busque el archivo de condici�n compatible." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Archivo de condici�n no v�lido." ),
      I_( "Busque otro archivo de condici�n." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};




