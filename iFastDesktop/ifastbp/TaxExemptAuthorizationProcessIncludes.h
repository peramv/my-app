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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorizationProcessIncludes.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 07/15/2004
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0301_vw.hpp>
#include <ifastdataimpl\dse_dstc0301_vwrepeat_record.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TAX_EXEMPT_AUTHORIZATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
namespace TAXEXEMPT
{
   const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
}

namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TaxExemptAuthorizationHeadingSet;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	extern CLASS_IMPORT const BFDecimalFieldId ExemptAmtRemain;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxExemptAuthorizationProcessIncludes.h-arc  $
//
//   Rev 1.0   Aug 06 2004 17:38:20   ZHANGCEL
//Initial revision.
 * 
 */
