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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class AsPensionPlan;
class MFAccount;

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

class IFASTBP_LINKAGE AsPensionPlanProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AsPensionPlanProcess();
   AsPensionPlanProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AsPensionPlanProcess();


protected:

   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(const Command &);

   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   SEVERITY doSetField(
                      const GenericInterface *rpGICaller, 
                      const BFContainerId& idContainer, 
                      const BFFieldId& idField, 
                      const BFDataGroupId& idDataGroup, 
                      const DString& strValue, 
                      bool bFormatted
                      );
   void doGetField(
                  const GenericInterface *rpGICaller,  
                  const BFContainerId& idContainer, 
                  const BFFieldId& idField, 
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormtted
                  ) const;
private:
   AsPensionPlan *_pAsPensionPlan;
   GenericInterface *_rpChildGI;
   MFAccount* _pMFAccount;

   DString _accountNum;
   DString _shrNum;

};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AsPensionPlanProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:36:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:51:48   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:46   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:15:08   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   04 Jan 2002 17:23:10   KOVACSRO
//Added doGetField and doSetField
//
//   Rev 1.0   Aug 23 2001 13:07:32   JANKAREN
//Initial revision.
 * 
 */
