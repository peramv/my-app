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
// ^FILE   : RESPBeneficiaryList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPBeneficiaryList
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

class IFASTCBO_LINKAGE RESPBeneficiaryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   RESPBeneficiaryList( BFAbstractCBO &parent );

   virtual ~RESPBeneficiaryList();

   SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const BFData& data );

   void getSubstitionList(DString& beneficiarySubList, const BFDataGroupId& idDataGroup);


protected:
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );


private:
 
   BFData	_requestData;
};

