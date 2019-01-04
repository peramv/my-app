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
// ^FILE   : EntityRegJurisDetails.hpp
// ^AUTHOR : 
// ^DATE   : 14 January 2014
//
// ^CLASS    : EntityRegJurisDetails
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
class EntityRegJurisDetailsList;
class FinInstDetlList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE EntityRegJurisDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
	EntityRegJurisDetails (BFAbstractCBO &parent);
	virtual ~EntityRegJurisDetails();
	SEVERITY init (const BFData &data); 
	SEVERITY initNew (const BFDataGroupId &idDataGroup);
	void setDefaultEntityId(DString &dstrEntityId,
	 				   const BFDataGroupId &idDataGroup);

protected:
	virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
	virtual SEVERITY doApplyRelatedChanges(const BFFieldId &idField, const BFDataGroupId &idDataGroup);
	virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
	virtual void doReset(const BFDataGroupId &idDataGroup);
   void    initializeSubstitutionListFromMiscInfo ( const BFFieldId& idField, 
                                                    const DString &dstrGroupCode, 
                                                    const BFDataGroupId& idDataGroup,
                                                    const bool bUseViewDesc = false );

private:
	void setFATCACodeRelatedChanges(const BFDataGroupId &idDataGroup);
	SEVERITY commonInit(const BFDataGroupId &idDataGroup);
	void initConsent(const BFDataGroupId &idDataGroup);
	//void getSelectedFFIStartStopDate(const BFDataGroupId &idDataGroup, DString &startDate, DString &stopDate);
};