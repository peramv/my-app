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
// ^FILE   : JAcctMailProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/03/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : JAcctMailProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the API
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class JEntityList;

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

class AccountMailingList;
class Shareholder;
class DecodeAcctID;
class DSTCWorkSession;

class IFASTBP_LINKAGE JAcctMailProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   JAcctMailProcess();
   JAcctMailProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~JAcctMailProcess();

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

protected:
	
	virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );	

	 virtual void setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo );

	 //const DString& getKeyForNewListItem( const GenericInterface *rpGICaller,
                                         //const BFContainerId& idList );


	SEVERITY setFreshList( GenericInterface *rpGI );

private:
  
   GenericInterface *_rpChildGI;
	DecodeAcctID *_pDecodeAcctID;
	AccountMailingList *_pAccountMailingList;
	DSTCWorkSession *pWorkSession;

	DString m_dstrAcctIdentifier;
	DString m_dstrAccountNum;
	DString m_dstrShrNum;
	DString m_dstrStatus;
	DString defHoldAnnlRpts, defHoldSemiAnnual, defHoldAnnlMRFP, defHoldSmAnnlMRFP;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctMailProcess.hpp-arc  $
//
//   Rev 1.1   Dec 05 2005 16:46:18   ZHANGCEL
//PET1332 FN09 -- Add logic to compare with the DefaultMailOption
//
//   Rev 1.0   Oct 24 2005 17:37:42   ZHANGCEL
//Initial revision.
 */
