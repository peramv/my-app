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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorizationList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : TaxExemptAuthorizationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class MgmtCoOptions;
class MFAccount;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TaxExemptAuthorizationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TaxExemptAuthorizationList( BFAbstractCBO &parent );
   virtual ~TaxExemptAuthorizationList( void );

	SEVERITY initNew( const DString& strAccountNumber );
   // Initialize function
   SEVERITY init( const BFDataGroupId& idDataGroup,
                  const DString& AccountNumber, 
                  bool bViewCall = true, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	//DString &DofBirth );

	// Following functions will be used in TaxExemptAuthorization.cpp
	MgmtCoOptions*	getMgmtCoOptions()      { return(pMgmtCoOptions);}
	MFAccount*      getMFAccount()          { return(pMFAccount);}
	DString			getDeregAmtYrToDate()	{ return(m_dstrDeregAmtYrToDate);}
	DString         getAcctNum()            { return(dstrAcctNum);}
	SEVERITY		getMore();
	bool hasFullExemptScope(const DString &taxExType, 
							const DString &taxJurisCode,
							const DString &entityId,
							const DString &fundCode,
							const DString &classCode,
							const DString &startDate,
							const DString &endDate,
							const BFDataGroupId& idDataGroup);	

protected:
   SEVERITY doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   bool validateExemptionScope(const DString &fundCode, 
							   const DString &fundCode1, 
							   const DString &classCode, 
							   const DString &classCode1, 
							   const DString &exemptionScope, 
							   const DString &exemptionScope1);

private:
	// Private function member
	void getInfoForVldandDft( const BFDataGroupId& idDataGroup );
	SEVERITY validateDateRanges( const BFDataGroupId& idDataGroup );
	bool getTaxExemptLevel (const BFDataGroupId &idDataGroup);

	// Private data members
	MgmtCoOptions	*pMgmtCoOptions;
	MFAccount       *pMFAccount;
	DString         dstrAcctNum;
	DString			m_dstrDeregAmtYrToDate;
	BFData			queryData;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxExemptAuthorizationList.hpp-arc  $
//
//   Rev 1.3   Nov 28 2005 09:42:28   jankovii
//PET1228_FN02_ EU Savings Directive Phase Two
//
//   Rev 1.2   Apr 21 2005 10:17:24   ZHANGCEL
//Incident #292340 -- Added initNew for a new account creation.
//
//   Rev 1.1   Nov 14 2004 14:56:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Aug 06 2004 17:46:22   ZHANGCEL
//Initial revision.
 * 
 */