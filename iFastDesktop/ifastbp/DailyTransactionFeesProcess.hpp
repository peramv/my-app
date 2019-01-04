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
//    AUTHOR : Monica Vadeanu
//    DATE   : Jan 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class DailyTransactionsFeeList;

class IFASTBP_LINKAGE DailyTransactionFeesProcess : public AbstractProcess ,
                                                    public IFastHistoricalParameters
{
// Construction
public:
   DailyTransactionFeesProcess( GenericInterfaceContainer* pGIC, 
                                GenericInterface* pGIParent, 
										  const Command& rCommand );

   virtual ~DailyTransactionFeesProcess();
protected:
   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();

   virtual bool doModelessChildComplete( const Command &cmd );
   
	virtual SEVERITY performSearch( GenericInterface *rpGI, 
                                   const BFContainerId& idSearch, 
											  E_SEARCHACTION eSearchAction );
   
	virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idSearch );

   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return true;
   }
   
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,
                                   const BFDataGroupId &idDataGroup );
   
	void *getPtrForContainer( const BFContainerId &idContainer,
                             const BFDataGroupId &idDataGroup );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

   virtual SEVERITY getHistoricalParameters ( const BFContainerId& idContainer, 
                                              BFFieldId &recordIdField,
                                              DString& tableId, 
                                              DString& dstrKeys); 
   virtual SEVERITY getHistoricalParameters (const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput);


private:
   GenericInterface *_rpChildGI;
   
   SEVERITY processParameters();

	DString _dstrDailyTransFeeRecordType;
	DString _dstrFeeCode;
	DString _dstrFundCode;
	DString _dstrClassCode;
	DString _dstrEffectiveDate;

	DailyTransactionsFeeList *_pDailyTransactionsFeeList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DailyTransactionFeesProcess.hpp-arc  $
//
//   Rev 1.2   Jul 14 2010 13:32:24   jankovii
//PET0170770_FN01_Anti Dilution Levy
//
//   Rev 1.1   Feb 10 2004 16:28:18   VADEANUM
//PET 859 FN23 - ADL - first working version
//
//   Rev 1.0   Feb 03 2004 16:38:40   VADEANUM
//Initial revision.
//
*/
