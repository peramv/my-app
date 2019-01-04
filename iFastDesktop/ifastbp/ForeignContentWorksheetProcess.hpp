#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ForeignContentWorksheetProcess.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ForeignContentWorksheetProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : 

//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class Trade;
class IFASTBP_LINKAGE ForeignContentWorksheetProcess : public AbstractProcess
{
// Construction
public:
   ForeignContentWorksheetProcess( GenericInterfaceContainer* pGIC, 
                                   GenericInterface* pGIParent, 
										     const Command& rCommand );

   virtual ~ForeignContentWorksheetProcess();
	SEVERITY performSearch( GenericInterface *rpGI, 
                         const BFContainerId& idSearch, 
								 E_SEARCHACTION eSearchAction );

protected:
   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();

   virtual bool doModelessChildComplete( const Command &cmd );   	

   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return true;
   }
   
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,
                                   const BFDataGroupId &idDataGroup );
   	
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

	virtual SEVERITY doSetField( const GenericInterface *rpGICaller, 
								const BFContainerId& idContainer, 
								const BFFieldId& idField, 
								const BFDataGroupId& idDataGroup, 
								const DString& strValue, 
								bool bFormatted );

	virtual const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                             const BFContainerId& idContainer, 
															const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup );

	virtual void doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const;

	virtual bool doSend(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szMessage
                               );
   virtual SEVERITY doGetErrors( const GenericInterface* rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& fieldID,
                                 const BFDataGroupId& idDataGroup,
                                 CONDITIONVECTOR& conditions ) const;



private:
   GenericInterface *_rpChildGI;
   
   SEVERITY processParameters();		

	DString _dstrAccount;
	DString _dstrShareholder;
	Trade*  m_pTrade;
	DString m_dstrHypoTransType;
	BFProperties* m_pTransTypeProperty;
	bool m_bFirstTime;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ForeignContentWorksheetProcess.hpp-arc  $
//
//   Rev 1.4   May 26 2004 09:51:52   YINGBAOL
//PET985Limplement doGetError
//
//   Rev 1.3   May 25 2004 10:07:42   YINGBAOL
//PET985: implement FundName
//
//   Rev 1.2   May 19 2004 17:41:54   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.1   Apr 26 2004 13:35:18   VADEANUM
//PET985 FN01 - Foreign Content - work in progress.
//
//   Rev 1.0   Apr 21 2004 15:38:04   VADEANUM
//Initial revision.
//
