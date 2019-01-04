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
// ^FILE   : DirectTradingList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DirectTradingList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class MgmtCoOptions;
class DirectTrading;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DirectTradingList : public MFCanBFCbo, private boost::noncopyable
{
public:
   DirectTradingList( BFAbstractCBO &parent );
   virtual ~DirectTradingList( void );

   // Initialize function
   SEVERITY init( DString& AccountNum, 
                  bool ignoreDataNotFound = true, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );    


   SEVERITY init2(const BFData& recData ); 
   SEVERITY  initNew( const DString& dstrAccountNum );

protected:
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   virtual SEVERITY doCreateNewObject( BFCBO*& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual void getStrKey( DString &strKey, const BFData *data ); 
   bool IsCurrentObjectEffective(const DString& strKey,const BFDataGroupId& idDataGroup);


private:
   DString _AccountNum;
   DString _dstrKey;

};


