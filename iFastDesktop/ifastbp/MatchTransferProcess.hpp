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
// ^FILE   : MatchTransferProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : August 9, 2001
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Matching Transfer Record screen
//
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class MatchTransferList;
class FundMasterList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the remarks process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE MatchTransferProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   MatchTransferProcess();
   MatchTransferProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MatchTransferProcess();

protected:
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();

   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();

   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   bool doModelessChildComplete( const Command &cmd );
private:

   DString _AccountNum;
   DString _TransId;
   DString _ShareholderNum;
   DString _EntityId;
   DString _InquiryOnly;
//	FundMasterList       *_pFundMasterList;
   MatchTransferList *_pMatchTransferList;
   GenericInterface     *_rpChildGI;
}; 



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MatchTransferProcess.hpp-arc  $
//
//   Rev 1.8   May 11 2004 14:26:28   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.7   Mar 21 2003 17:44:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Mar 03 2003 14:08:28   KOVACSRO
//Added InquiryOnly.
//
//   Rev 1.5   Oct 09 2002 23:53:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:53:00   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:20:22   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:56   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Sep 10 2001 16:53:30   ZHANGCEL
//Added a new member data
//
//   Rev 1.0   Aug 16 2001 13:32:34   ZHANGCEL
//Initial revision.
 * 
 */

