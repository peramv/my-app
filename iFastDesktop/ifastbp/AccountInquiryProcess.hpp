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
// ^FILE   : TransactionHistoryProcess.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 16/03/2001
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionHistoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>

// Forward references
class AccountInquiryList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccountInquiryProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountInquiryProcess();
   AccountInquiryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountInquiryProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   void doGetField(
                  const GenericInterface *rpGICaller,
                  const BFContainerId& idContainer,
                  const BFFieldId& idField,
                  const BFDataGroupId& idDataGroup,
                  DString &strValueOut,
                  bool bFormatted
                  ) const;

private:
   AccountInquiryList *_pAccountInquiryList;
   GenericInterface *_rpChildGI;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountInquiryProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:34:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:51:30   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:22:06   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:48   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 18 2001 18:17:54   VASILEAD
//Fixes for UAT release
 * 
 *    Rev 1.1   Jul 08 1999 10:04:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

