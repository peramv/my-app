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
// ^FILE   : JAcctMailPrdOverrideProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/03/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : JAcctMailPrdOverrideProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the API
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class MFAccount;
class DecodeAcctID;
class AcctMailingOverrideList;

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

class AcctMailingOverrideList;
class MFAccount;
class DecodeAcctID;
class DSTCWorkSession;

class IFASTBP_LINKAGE JAcctMailPrdOverrideProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   JAcctMailPrdOverrideProcess();
   JAcctMailPrdOverrideProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~JAcctMailPrdOverrideProcess();

protected:
    
   virtual SEVERITY doInit();
  
  
   virtual E_COMMANDRETURN doProcess();

protected:

	
	virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );	

	SEVERITY setFreshList( GenericInterface *rpGI );

	virtual void setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo );


	
private:
  

	SEVERITY setAcctMailOverrideField( const BFFieldId &fieldID,  
		                                const DString &strValue, 
												  const BFDataGroupId& idDataGroup );


   GenericInterface *_rpChildGI;
	DecodeAcctID *_pDecodeAcctID;
	AcctMailingOverrideList *_pAcctMailingOverrideList;
	DSTCWorkSession *pWorkSession;

	DString m_dstrAcctIdentifier;
	DString m_dstrFundGroup;
	DString m_dstrAccountNum;
	DString m_dstrShrNum;
	DString m_dstrStatus;
	DString m_dstrDocumentType;
	DString m_DefOnHold;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctMailPrdOverrideProcess.hpp-arc  $
//
//   Rev 1.1   Dec 05 2005 16:45:36   ZHANGCEL
//PET1332 FN09 -- Add logic to compare with the DefaultMailOption
//
//   Rev 1.0   Oct 24 2005 17:37:32   ZHANGCEL
//Initial revision.
 *
 */
