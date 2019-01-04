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

class IFASTBP_LINKAGE EstateAllocationProcess : public AbstractProcess
{
public:
   EstateAllocationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~EstateAllocationProcess();
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
	DString m_Caller;
   DString m_TradeListKey;
   DString m_accountNum;
   DString m_TransId;
   bool _readOnly;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EstateAllocationProcess.hpp-arc  $
//
//   Rev 1.0   25 Jul 2012 15:27:32   if991250
//Initial revision.
//
*/
