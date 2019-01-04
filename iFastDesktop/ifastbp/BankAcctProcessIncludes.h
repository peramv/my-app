#ifndef BANKINSTRUCTIONSPROCESSINCLUDES_H
#define BANKINSTRUCTIONSPROCESSINCLUDES_H

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankAcctProcessIncludes.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/2001
//
//******************************************************************************

#include <DSTC0055_VW.hpp>
#include <DSTC0052_VWRepeat_Record.hpp>
#include <DSTC0004_VWRepeat_Record.hpp>
#include <DSTC0006_VWRepeat_Record.hpp>
#include <DSTC0016_VWRepeat_Record.hpp>
#include <DSTC0100_VWRepeat_Record.hpp>
#include <DSTC0050_VW.hpp>

#ifndef DSTC0049_VW_HPP
   #include <DSTC0049_VW.hpp>
#endif

#include <ListViewHeading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//name of the substitute list fields
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId BANK_ACCT_LIST;
}
namespace DBR
{
   extern CLASS_IMPORT const long ShrBankInstrAcctUseCode;
   extern CLASS_IMPORT const long SystematicTransType;
   extern CLASS_IMPORT const long BankOptionsFieldsHeadingSet;
   extern CLASS_IMPORT const long BankOptionsHeadingSet;
   extern CLASS_IMPORT const long BankAcctHeadingSet;
}

namespace BANKACCTLIT
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR* const INSTRUCTION;
   extern IFASTBP_LINKAGE const I_CHAR* const DEFAULT;
}

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace BANK_ACCT_DEF
{
//CP20030319   const int BANK_ACCT_LIST                    = 1;
}

#endif // BANKINSTRUCTIONSPROCESSINCLUDES_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BankAcctProcessIncludes.h-arc  $
//
//   Rev 1.4   Mar 21 2003 17:36:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Feb 21 2001 10:42:40   BUZILAMI
//BankAcct changes
//
//   Rev 1.1   Feb 16 2001 17:21:16   BUZILAMI
//New Bank dlg/Process/CBO changes
//
//   Rev 1.0   Feb 12 2001 12:39:32   BUZILAMI
//Initial revision.
 * 
 *
 */
