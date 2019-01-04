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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFAccountList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 042/16/99
//
// ^CLASS    : MFAccountList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <bfdata\bfdata.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE MFAccountList : public MFCanBFCbo, private boost::noncopyable
{
public:
   MFAccountList( BFAbstractCBO &parent );
   virtual ~MFAccountList();

   //used to initialize from the shareholder object, when shareholder is new,
   //the param here is passed for convenience
   SEVERITY initNew(const DString& shrNum, const BFDataGroupId& idDataGroup = BF::HOST);
   //used to initialize when we only know the shareholder number
   SEVERITY init(const DString& InputShrNum);
   SEVERITY init(const DString& EntityId, const DString& InputAcctNum, 
      const DString& InputShrNum, const DString& NumEntry = NULL_STRING, //num entry is useless, should be removed
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   SEVERITY init(BFData& InstData);
   SEVERITY populateList(BFData& InstData);
   SEVERITY getAccountNumSubstList(DString & _AccountNumSubList,
		const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectivDateAgainstAllShereholder( DString & inEffectiveDate,
															  const BFDataGroupId& idDataGroup	);

protected:
   SEVERITY doCreateObject(const BFData& data, BFCBO*& pObjOut);
   void setObjectFlags(const BFObjectKey & objKey, long& lStateFlags, long& lGroupFlags);
private:
};

///#endif

