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
// ^FILE   : RegulatoryStandardList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RegulatoryStandardList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class WhereUsed;

class IFASTCBO_LINKAGE RegulatoryStandardList : public MFCanBFCbo, private boost::noncopyable
{
public:
   RegulatoryStandardList( BFAbstractCBO &parent );

   virtual ~RegulatoryStandardList();

   SEVERITY init( const DString& dstrTypeOfInvestor,
	              const DString& dstrInvsetOnBehalf,
				  const DString& dstrCountry,
                  const DString& dstrAcctEffDate,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const BFData& data );

   void getSubstitionList(DString& regStandardSubList, const BFDataGroupId& idDataGroup);


protected:
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );


private:
   DString	_typeOfInvestor;
   BFData	_requestData;
};

