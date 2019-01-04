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
// ^FILE   : ConfirmationList.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Nov 23, 1999
//
// ^CLASS  : ConfirmationList
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

class IFASTCBO_LINKAGE ConfirmationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ConfirmationList( BFAbstractCBO &parent );
   virtual ~ConfirmationList();

   // Initialize function
   SEVERITY init();
protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
};

