#pragma once
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
// ^FILE   : AWDCommon.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 12 Jul 1999
//
// ^CLASS  : 
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#include <bfdata\bfdata.hpp>
#include <bfproc\genericinterface.hpp>

class AWDCommon
{
public:

   static void getExportAwdConvertedData(BFData &data, GenericInterface &rpGIUserSession);
   static void getDataForAWD(BFData &data, GenericInterface &rpGIUserSession);
   static bool IsSessionTableValid(DString &dstrTable);
   static bool IsMappingTableValid( void );
};

