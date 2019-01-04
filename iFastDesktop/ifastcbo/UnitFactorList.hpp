#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
// ^FILE   : UnitFactorList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : UnitFactorList
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

class IFASTCBO_LINKAGE UnitFactorList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   UnitFactorList( BFAbstractCBO &parent );
   virtual ~UnitFactorList( void );

   // Initialize function
   SEVERITY init( DString& UnitId,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

//   SEVERITY init( const BFData& data );

   SEVERITY getMore();

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );

private:

   BFData m_requestData;
};

