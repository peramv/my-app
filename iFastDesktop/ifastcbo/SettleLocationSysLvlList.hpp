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
// ^FILE   : SettleLocationSysLvlList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettleLocationSysLvlList
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

class SettleLocationSysLvl;

class IFASTCBO_LINKAGE SettleLocationSysLvlList : public MFCanBFCbo
{
public:

   SettleLocationSysLvlList( BFAbstractCBO &parent );
   virtual ~SettleLocationSysLvlList();

   SEVERITY init(const BFDataGroupId& idDataGroup,
					  const DString& dstrTrack = I_("N"),
					  const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   SEVERITY getMore();

   bool isDuplicateSettlementLocation( DString &, const BFDataGroupId& idDataGroup );

	SEVERITY getSettleLocationSysLvl( const DString &dstrSettlementLocationCode, 
				      				       SettleLocationSysLvl *&pSettleLocationSysLvl, 
												 const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationSysLvlList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:53:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 25 2003 17:19:16   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support - added getSettleLocationSysLvl().
//
//   Rev 1.1   Nov 24 2003 18:13:36   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:48   HERNANDO
//Initial revision.
//
//