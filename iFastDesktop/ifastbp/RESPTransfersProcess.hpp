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
//
// ^FILE   : RESPTransfersProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPTransfersProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class RESPTransferList;

class IFASTBP_LINKAGE RESPTransfersProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */

	RESPTransfersProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
	virtual ~RESPTransfersProcess();

 	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
	virtual bool setCommitDataGroupAsHost();
	virtual bool doOk (GenericInterface *rpGICaller);
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

protected:

	virtual SEVERITY doSetField (const GenericInterface *rpGICaller, 
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue, 
                                 bool bFormatted);

	virtual void doGetField (const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;

	virtual const BFProperties *doGetFieldAttributes (const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup,
                                  CONDITIONVECTOR &conditions) const;
   virtual bool doRegisterObserver ( const GenericInterface *rpGICaller,
                                     const BFContainerId &idContainer,
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup,
                                     BFObserver &rpObserver);

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch );

private:
	GenericInterface *_rpChildGI;
	DString m_Caller,
	   m_RESPTransListKey,
	   m_TradeListKey,
	   m_AccountNum,
	   m_DecimalDigits,
	   m_HistoryPending,
	   m_TransType,
	   m_DepositType,
	   m_RedCode,
	   m_AccountTo;

   RESPTransferList* _pRESPTransferList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastbp/RESPTransfersProcess.hpp-arc  $
//
//   Rev 1.5   Jun 28 2011 09:57:26   panatcha
//P0184541_FN01_InvescoQESItrans
//
//   Rev 1.4   Jun 24 2010 07:29:56   dchatcha
//Revision Control entries.
// 