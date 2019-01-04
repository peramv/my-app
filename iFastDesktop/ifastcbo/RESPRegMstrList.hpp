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
// ^FILE   : FATCAMasterList.hpp
// ^AUTHOR : 
// ^DATE   : 14 January 2014
//
// ^CLASS    : FATCAMasterList
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

class IFASTCBO_LINKAGE RESPRegMstrList : public MFCanBFCbo, private boost::noncopyable
{
public:
	RESPRegMstrList( BFAbstractCBO &parent );
	virtual ~RESPRegMstrList( void );
	SEVERITY init(const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
	bool isGrantTypeActive( const DString &dstrTradeDate, const DString& respNotlType, const BFDataGroupId& idDataGroup );

protected:
	virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
	virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);
	SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);

};