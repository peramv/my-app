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
//    Copyright 2003, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : SettleLocationAcctLvlList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettleLocationAcctLvlList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SettleLocationAcctLvlList : public MFCanBFCbo
{

friend class SettleLocationAcctLvl;

public:

   SettleLocationAcctLvlList( BFAbstractCBO &parent );
   virtual ~SettleLocationAcctLvlList();

   SEVERITY init(const DString& dstrAccountNum,
					  const DString& dstrTrack = I_("N"),
					  const DString& dstrPageName = NULL_STRING);
   SEVERITY init();

   SEVERITY reInit();

   bool isDuplicateSettlementLocation( DString &, const BFDataGroupId& idDataGroup );
   bool isDuplicateDefault( DString &, const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;

private:

   DString m_dstrSettleLocationCodeSubstitution;
   DString m_dstrInitialSettleLocationCode;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationAcctLvlList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:53:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 24 2003 18:12:26   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:44   HERNANDO
//Initial revision.
