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
// ^FILE   : AccountInquiryList.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 16/03/2001
//
// ^CLASS    : AccountInquiryList
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

class IFASTCBO_LINKAGE AccountInquiryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountInquiryList( BFAbstractCBO &parent );
   virtual ~AccountInquiryList( void );

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode, 
                  const DString& dstrSalesRepCode,
                  const DString& dstrAccountNum, 
                  const DString& dstrSIN, 
                  const DString& dstrShrNum,
                  const DString& dstrAltAccount, 
                  const DString& dstrLastName, 
                  const DString& dstrFirstName,
                  const DString& dstrCorpIndiv, 
                  const DString& dstrInTrustJoint, 
                  const DString& dstrIntermCode, 
                  const DString& dstrIntermAcct, 
                  const DString& dstrNextOrPrevious = I_( "Y" ),
                  const DString& dstrNextKey = NULL_STRING,
                  const DString& dstrTrack = I_( "N" ), 
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init();

private:
};

