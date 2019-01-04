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
// ^FILE   : SysAllocationList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : April 6, 1999
//
// ^CLASS  : HistoricalMarketValueList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
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

class IFASTCBO_LINKAGE HistoricalMarketValueList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HistoricalMarketValueList( BFAbstractCBO &parent );
   virtual ~HistoricalMarketValueList( void );

   // Initialize function
   SEVERITY init( const DString&  strAccountNumber, 
                  const DString&  strAsOfDate,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   //SEVERITY init( const Data& data );

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   virtual void getField( const BFFieldId& idField, DString& strFieldValue, 
                          const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY calculateFundGroupTotal(DString& fundGroup, 
   DString& total, const BFDataGroupId& idDataGroup);
protected:
   void getStrKey ( DString& strKey, const BFData* data );
private:
};

