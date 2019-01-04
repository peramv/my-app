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
// ^FILE		: RESPRegRule.hpp
// ^AUTHOR		: 
// ^DATE		: 
//
// ^CLASS		: RESPRegRule
// ^SUBCLASS	:
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class RESPRegRuleList;


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RESPRegRule : public MFCanBFCbo, private boost::noncopyable
{
public:
	RESPRegRule (BFAbstractCBO &parent);
	virtual ~RESPRegRule();
	SEVERITY init (const BFData &data); 
	SEVERITY initNew (const BFDataGroupId &idDataGroup);

protected:
	virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);	

private:
	SEVERITY commonInit(const BFDataGroupId &idDataGroup);
};