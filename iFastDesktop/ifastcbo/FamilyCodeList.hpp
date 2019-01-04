#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FamilyCodeList.hpp
// ^AUTHOR : 
// ^DATE   : Oct, 2011
//
// ^CLASS    : FamilyCodeList
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

class IFASTCBO_LINKAGE FamilyCodeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FamilyCodeList( BFAbstractCBO &parent );
   virtual ~FamilyCodeList(void);

// Initialize function
   SEVERITY init(const DString& dstrFamilyCode,
                 const DString& dstrFamilyName,
                 const DString& dstrExactMatch,
                 const BFDataGroupId& idDataGroup);

   SEVERITY getMore();
   
   void refreshMe (bool bRefresh)
   {
      _bRefresh = bRefresh;
   }

   bool needsRefresh (const BFDataGroupId& idDataGroup) const
   {
      return _bRefresh;
   }
   
   bool isFamilyCodeExisted(const DString& dstrLookForCode, const BFDataGroupId& idDataGroup);   

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData* requestData235;
   bool   _bRefresh;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FamilyCodeList.hpp-arc  $
//
//   Rev 1.1   Nov 17 2011 19:11:50   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.0   Nov 08 2011 11:47:24   dchatcha
//Initial revision.
//
