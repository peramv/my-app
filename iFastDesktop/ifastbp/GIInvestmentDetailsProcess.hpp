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
//    Copyright 2011 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>

// Forward references

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE GIInvestmentDetailsProcess : public AbstractProcess
{
public:
   GIInvestmentDetailsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~GIInvestmentDetailsProcess();
   bool isReadOnly() {return _readOnly;};
protected:
 	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
	virtual bool doOk (GenericInterface *rpGICaller);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, 
                                    const BFDataGroupId& idDataGroup);
   virtual bool doSend ( GenericInterface *rpGICaller,
                         const I_CHAR  *szMessage);

   virtual void doGetField ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup, 
                                        DString &strValueOut,
                                        bool bFormatted) const;
   virtual SEVERITY doSetField( const GenericInterface *rpGICaller, 
                                         const BFContainerId &idContainer, 
                                         const BFFieldId &idField, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString &strValue, 
                                         bool bFormatted);
   virtual const BFProperties* doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                          const BFContainerId &idContainer, 
                                          const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup );
   virtual void setCurrentListItem(const GenericInterface *rpGICaller,
               const BFContainerId& idList, const DString& strListItemKey);
   SEVERITY calculateTotals();
private:
	GenericInterface *_rpChildGI;
	DString m_Caller,
	   m_TradeListKey,
      m_accountNum;
   bool _readOnly;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GIInvestmentDetailsProcess.hpp-arc  $
//
//   Rev 1.6   Mar 20 2012 16:40:42   if991250
//IN 2885623 - GI Money Oout
//
//   Rev 1.5   Mar 12 2012 18:10:44   if991250
//GI Money Out
//
//   Rev 1.4   Mar 09 2012 17:44:58   if991250
//GIInvestmentDetails
//
//   Rev 1.3   Mar 08 2012 09:56:54   if991250
//GI Money Out
//
//   Rev 1.2   Feb 17 2012 10:34:36   if991250
//GI Investment
//
//   Rev 1.1   Jan 16 2012 15:41:48   if991250
//GI Investment Details
//
//   Rev 1.0   Jan 12 2012 10:19:50   jankovii
//Initial revision.
//
*/
