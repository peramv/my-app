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
//******************************************************************************
//
// ^FILE   : FreeUnitList.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : July 26, 1999
//
// ^CLASS  : FreeUnitList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE FreeUnitList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FreeUnitList( BFAbstractCBO &parent );
   virtual ~FreeUnitList( void );

   // Initialize function
   SEVERITY init( const DString& AccountNum,
                  const DString& AcctLvlDSCFund = I_("Y"),
                  const DString& AllFundMode = I_("Y"),
                  const DString& AllFundGroupMode = I_("N"),
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init( const BFData& data );

   void setParameter( const DString& elementName, const DString& value );
   SEVERITY search( bool bClearPreviousSearch = false );
   void getStrKey( DString &strKey, const BFData *data );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY init2( const DString& AccountNum,
				  const DString& FundCode,
				  const DString& ClassCode,
                  const DString& FundGroup = NULL_STRING,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );
private:
   BFData*  requestData;
   DString _accountNum;
};

