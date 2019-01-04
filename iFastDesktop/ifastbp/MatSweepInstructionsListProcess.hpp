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
// ^FILE   : MatSweepInstructionsListProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MatSweepInstructionsListProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class MatSweepInstructionsList;

class IFASTBP_LINKAGE MatSweepInstructionsListProcess : public AbstractProcess
{
// Construction
public:
   MatSweepInstructionsListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MatSweepInstructionsListProcess();

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);  
   virtual bool doSend ( GenericInterface *rpGICaller,
                         const I_CHAR  *szMessage);

   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller, 
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue, 
                                 bool bFormatted);

   virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;
   SEVERITY readParameters();

protected:
	virtual bool doOk (GenericInterface* rpGICaller);

private:
   GenericInterface *_rpChildGI;
   DString m_strAcctNum,
           m_strCaller,
		   m_strInstrType,
		   m_strFund,
		   m_strClass,
		   m_strTransNumber,
		   m_strTransId,
		   m_strIntInvestId,
		   m_TradeListKey,
		   m_strPrincipalAmount,
		   m_strAccuredAmount,
		   m_strCalcMethod,
		   m_strInvType,
		   m_strTerm,
		   m_strFrequency,
           m_strInvStatus;
   DString m_Reset;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log::   
 */
