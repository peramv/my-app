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
// ^FILE   : FundList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 25/03/99
//
// ^CLASS    : FundList
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

class IFASTCBO_LINKAGE FundList : public MFCanBFCbo, private boost::noncopyable
{
public:

   FundList( BFAbstractCBO &parent );
   virtual ~FundList( void );

   // Initialize function
   SEVERITY init( DString& dstFundCode,  
                  DString& dstClassCode, 
                  DString& dstFromDate, 
                  DString& dstToDate, 
                  DString& dstPrevDatePressed, 
                  DString& dstNextDatePressed,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING,
				  const DString& dstGetLastIDRate= I_("N"),
                  const DString& dstrGetTransType = I_(""),
                  const DString& dstrGetNextAvailRate = I_("N"));

   void setParameter( const DString& elementName, const DString& value );
   SEVERITY search( bool bClearPreviousSearch = false );
protected:
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
private :
   BFData* requestData;

};


