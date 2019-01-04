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

class IFASTBP_LINKAGE AccountCommitmentProcess : public AbstractProcess
{
public:
   AccountCommitmentProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountCommitmentProcess();
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

protected:
 	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
	virtual bool doOk (GenericInterface *rpGICaller);
    virtual bool doSend ( GenericInterface *rpGICaller,
                         const I_CHAR  *szMessage);
    SEVERITY doSetField( const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted );
	virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
	
private:
	GenericInterface *_rpChildGI;
	DString m_Caller,
	   m_TradeListKey,
      m_accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountCommitmentProcess.hpp-arc  $
//
//   Rev 1.3   Apr 30 2012 15:30:52   popescu
//2902002 - P0186480FN02 - Diploma DSK Validation
//
//   Rev 1.2   Mar 23 2012 10:44:28   if991250
//IN  2885402 - PAC-EFT Systematic readonly for active commitments, Added Insured and Policy number
//
//   Rev 1.1   Feb 17 2012 10:34:04   if991250
//Account Commitment
//
//   Rev 1.0   Jan 20 2012 16:21:00   if991250
//Initial revision.
//
*/
