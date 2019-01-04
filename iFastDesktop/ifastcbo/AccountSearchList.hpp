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
// ^FILE   : AccountSearchList.hpp
// ^AUTHOR : 
// ^DATE   : 03/11/99
//
// ^CLASS    : AccountSearchList
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

class IFASTCBO_LINKAGE AccountSearchList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountSearchList( BFAbstractCBO &parent );
   virtual ~AccountSearchList( void );
   // Initialize function
   SEVERITY init( DString& _srchAltAcct, 
                  DString& _SrchBrokerCode,                  
                  DString& _OneAcctOnly = DString(I_("N")), 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING, 
                  const DString& dstrOverrideRepeats = I_( "0" ), 
                  const DString& dstrNextOrPrevious = I_( "Y" ) ); 

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
private:
//methods
   bool containOnlyAllowedChars( const DString& AllowedChars, const DString& str );
   bool isStringEmptyOrJustContainSpace( const DString& str );


   BFData*  _requestData;
};

