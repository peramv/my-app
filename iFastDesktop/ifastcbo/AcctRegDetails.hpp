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
//
//******************************************************************************
//
// ^FILE   : AcctRegDetails.hpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : AcctRegDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class MFAccount;
class AcctRegDetailsList;
class FinInstDetlList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctRegDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
	AcctRegDetails (BFAbstractCBO &parent);
	virtual ~AcctRegDetails();
	SEVERITY init (const BFData &data); 
	SEVERITY initNew (const BFDataGroupId &idDataGroup);
	//void getField(const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, bool formattedReturn) const;

protected:
	virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
	virtual SEVERITY doApplyRelatedChanges(const BFFieldId &idField, const BFDataGroupId &idDataGroup);
	virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
	virtual void doReset(const BFDataGroupId &idDataGroup);

private:
	SEVERITY setReportingFFISubstitution(const BFDataGroupId &idDataGroup);
	SEVERITY commonInit(const BFDataGroupId &idDataGroup);
	SEVERITY setDefaultReportingFFI(const BFDataGroupId &idDataGroup);
	//void getSelectedFFIStartStopDate(const BFDataGroupId &idDataGroup, DString &startDate, DString &stopDate);
};