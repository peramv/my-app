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
//    Copyright 2002 by International financial data service.
//
//
//******************************************************************************
//
// ^FILE   : EntityAddressMailingList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : September, 2002
//
// ^CLASS    : EntityAddressMailingList
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

class IFASTCBO_LINKAGE EntityAddressMailingList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   EntityAddressMailingList( BFAbstractCBO &parent );
   virtual ~EntityAddressMailingList();
   // Initialize function
   SEVERITY init( const DString& dstrAccountNum, 
                  const DString& dstrEntityType,
                  const DString& dstrEntityTypeSeq,
                  const BFDataGroupId& idDataGroup,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void initNew( const DString& accountNum,
                 const DString& entityType,
                 const DString& seqNumber,
                 const BFDataGroupId& idDataGroup);



protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );

private:
   DString _strAccountNum;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//