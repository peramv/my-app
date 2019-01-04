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
// ^DATE   : 11/03/2001
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



#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class TransactionSummaryList;

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

class IFASTBP_LINKAGE TransactionSummaryProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TransactionSummaryProcess();
   TransactionSummaryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TransactionSummaryProcess();
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
   TransactionSummaryList *_pTransactionSummaryList;
   GenericInterface *_rpChildGI;

   DString AccountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionSummaryProcess.hpp-arc  $
//
//   Rev 1.5   Mar 21 2003 17:49:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:42   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:58   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   19 Mar 2002 13:19:02   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 19 2001 10:10:56   VASILEAD
//Added doGetField
 * 
 *    Rev 1.1   Jul 08 1999 10:04:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

///#endif 
