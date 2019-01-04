#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//
//******************************************************************************
//
// ^FILE   : ExternalInstitutionList.hpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : ExternalInstitutionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE ExternalInstitutionList : public MFCanBFCbo, private boost::noncopyable
{
public:

   ExternalInstitutionList( BFAbstractCBO &parent );
   virtual ~ExternalInstitutionList();
   
   SEVERITY init(const BFDataGroupId &idDataGroup);
   bool doesCodeExist(const DString key, const BFDataGroupId &idDataGroup);
   void getExternalInstitutionSubstitutionList(DString& listOut, const BFDataGroupId &idDataGroup);

   SEVERITY doSearch(bool bNext, const DString& searchBy, const DString searchKey, const BFDataGroupId &idDataGroup);

protected:
   SEVERITY doCreateObject (const BFData& data, BFCBO*& pObjOut);

private:

   void removedExistingItems(const BFDataGroupId &idDataGroup);
   SEVERITY appendOtherToSearchList(const BFDataGroupId &idDataGroup);

   std::map<DString,DString> _mapSubstitutionList;
   unsigned int _maxNumRecord;
   std::set<DString> _setCurrItemInList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ExternalInstitutionList.hpp-arc  $
// 