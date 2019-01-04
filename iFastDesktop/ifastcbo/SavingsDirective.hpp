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
//
//******************************************************************************
//
// ^FILE   : SavingsDirective.hpp
// ^AUTHOR : 
// ^DATE   : 15 Nov 2005
//
// ^CLASS    : SavingsDirective
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SavingsDirective : public MFCanBFCbo, private boost::noncopyable
{
public:
   SavingsDirective( BFAbstractCBO &parent );
   virtual ~SavingsDirective();
   SEVERITY init (const DString &dstrTransid,
						const DString &dstrAccountNum,
						const DString &dstrFund,
						const DString &dstrClass,
						const DString &dstrTradeDate,
						const DString &dstrTISType,
						const DString &dstrTIS,
						const DString &dstrCostType,
						const DString &dstrCost,
						const DString &dstrVersion,
						const BFDataGroupId &idDataGroup,
						const DString &dstrTrack = I_("N"),
						const DString &dstrPageName = NULL_STRING) ;

	SEVERITY doValidateField(	const BFFieldId &idField, 
                              const DString &strValue, 
                              const BFDataGroupId &idDataGroup);	
	virtual void doReset(const BFDataGroupId &idDataGroup);
   void clearUpdateFlags(const BFDataGroupId& idDataGroup);

protected:
	SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	SEVERITY doApplyRelatedChanges(const BFFieldId &idField, const BFDataGroupId &idDataGroup);


private:
   SEVERITY setSavingsDirectiveFields(const BFDataGroupId &idDataGroup);
	SEVERITY validateEUSD(const BFDataGroupId &idDataGroup); 

	DString	_transId,
				_tisType,
				_tis,
				_costType,
				_cost,
				_eusdOverrideVer,
				_accountNum,
				_fundCode,
				_classCode,
				_tradeDate;
	SavingsDirective* _pSavingsDirective;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SavingsDirective.hpp-arc  $
//
//   Rev 1.1   Jan 20 2006 11:10:12   AGUILAAM
//IN 512857 - fixed reset functionality
//
//   Rev 1.0   Nov 29 2005 16:59:46   AGUILAAM
//Initial revision.
//
*/