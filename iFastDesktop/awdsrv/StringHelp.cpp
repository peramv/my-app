#include "stdafx.h"
#include "StringHelp.hpp"
#include <string>
#include <iostream>
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : StringHelp.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 09, 2005
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

namespace StringHelp
{

   std::string& stripLeading( std::string& strIn, char stripChar)
{
   int stripLen = 0;
   int strLen = strIn.size();
   if( strLen == 0 )
   {
     
   //   return(strIn);
   }
   while( stripLen < strLen && strIn[ stripLen ] == stripChar )
   {
      stripLen++;
   }
   if( stripLen != std::string::npos )
   {
      strIn.erase( 0, stripLen );
   }
   return(strIn);

}

//*********************************************************************************

std::string& stripTrailing(  std::string& strIn, char stripChar )
{
   
   int stripPos = strIn.size();
   if( stripPos == 0 )
   {
      return(strIn);
   }

   while( --stripPos >= 0 && strIn[ stripPos ] == stripChar )
   {
   }
   strIn.erase( stripPos + 1 );
   return(strIn);
}

//**********************************************************************************
std::string&  strip( std::string &strIn, char stripChar )
{
   return(stripLeading( stripTrailing( strIn, stripChar ), stripChar ));
}

}