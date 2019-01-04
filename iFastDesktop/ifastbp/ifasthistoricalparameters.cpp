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
// ^FILE   : IFastHistoricalParameters.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : IFastHistoricalParameters
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "IFastHistoricalParameters.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "IFastHistoricalParameters" );
}


namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//******************************************************************************
IFastHistoricalParameters::~IFastHistoricalParameters()
{
}

SEVERITY IFastHistoricalParameters::getHistoricalParameters(const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& keys)
{
   return NO_CONDITION;
}

SEVERITY IFastHistoricalParameters::getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical)
{ 
   return NO_CONDITION;
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ifasthistoricalparameters.cpp-arc  $
// 
//    Rev 1.2   Mar 01 2004 09:55:26   HERNANDO
// PET965 FN11 - Added an additional getHistoricalParameters.  Changed from pure abstract class to abstract class.
// 
//    Rev 1.1   Jul 31 2003 21:34:18   popescu
// minor code formatting
// 
//    Rev 1.0   Mar 05 2003 11:13:58   PURDYECH
// Initial revision.
//
