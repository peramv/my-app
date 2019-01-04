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
//    Copyright 2005 by IFDS
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


/**
 * Class that manages the Rebook Param process
 *
 * @author Yingbao Li
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 06/26/2005</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE RebookParamProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RebookParamProcess();
   RebookParamProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RebookParamProcess();


protected:
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

/*
   virtual  bool doRefresh(
                          GenericInterface *rpGICaller,
                          const I_CHAR *szOriginalCommand
                          );

   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
*/
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual void doGetField( const GenericInterface *rpGICaller, 
                    const BFContainerId& idContainer, const BFFieldId& idField, 
                    const BFDataGroupId& idDataGroup, 
                    DString &strValueOut, 
                    bool bFormatted ) const;
   virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );	

   virtual void doPostOk( GenericInterface* rpGICaller,
                              bool bSuccessFlag );


private:
   GenericInterface *_rpChildGI;
   DString account_,transNum_,estateAlloc_,commRebate_,rebookExist_, 
			fundCode_, classCode_, useSameAccountTransType_, batch_,rebookCopy_;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RebookParamProcess.hpp-arc  $
//
//   Rev 1.2   May 27 2009 15:15:46   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.1   Feb 07 2006 11:29:34   AGUILAAM
//IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
//
//   Rev 1.0   Jul 06 2005 16:35:48   Yingbaol
//Initial revision.
 * 
 */