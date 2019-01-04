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
//    Copyright 2009 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ChequeDetailsList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/07/09
//
// ^CLASS    : ChequeDetailsList
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

class ChequeDetails;

class IFASTCBO_LINKAGE ChequeDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ChequeDetailsList( BFAbstractCBO &parent );
   virtual ~ChequeDetailsList( void );

   // Initialize function
   SEVERITY init( const DString& dstrTrack = NULL_STRING,
                  const DString& dstrPageName = NULL_STRING );      

   SEVERITY init( const BFData& data );

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   SEVERITY addRecord( ChequeDetails *pDetails );

private:
  

};


