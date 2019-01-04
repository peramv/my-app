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
// ^FILE   : TransCancellation.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancellation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

// Forward references

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DilutionAllocList;

class IFASTCBO_LINKAGE TransCancellation : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (const DString &TransNum, DString &strKeyOut);
public:
   // X-structors
   TransCancellation( BFAbstractCBO &parent );
   virtual ~TransCancellation();
   // Initialize function
   SEVERITY init ( const DString &transNum,
                   const BFDataGroupId& idDataGroup, 
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING
                 );
   SEVERITY getDilutionAllocList ( const BFDataGroupId& idDataGroup, 
							       DilutionAllocList *&pDilutionAllocList );
   void setReadOnlyFields ( bool readonly, const BFDataGroupId &idDataGroup);
   void CommonInit( bool newCancellation, DString &transNum, const BFDataGroupId &idDataGroup );
   SEVERITY getBatchNum ( const BFDataGroupId &idDataGroup,
                                const DString &track = I_("N"),
                                const DString &pageName = NULL_STRING);   
   SEVERITY ValidateAccountable( const BFDataGroupId& idDataGroup );
   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
   virtual void getField( const BFFieldId& idField, 
                          DString& strFieldValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false );
   void convertFields( const BFDataGroupId& idDataGroup, bool formattedReturn );

protected:
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

private:
	BFData * requestData337;
	bool newCancellation;
};

