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
// ^FILE   : FeeScaleList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeScaleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class FeeScale;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScaleList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FeeScaleList( BFAbstractCBO &parent );
   virtual ~FeeScaleList();
   // Initialize function
   SEVERITY init(const BFData& viewData, const DString& AcctFeeParamId);
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   DString getNextLevel(){
      return(DString::asString( ++iLevel ));

   }
protected:
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   bool canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup );

private:
   SEVERITY adjustLevel(DString dstrLevel,const BFDataGroupId& idDataGroup);
   int  iLevel;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//