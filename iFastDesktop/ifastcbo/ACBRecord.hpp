#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ACBRecord.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2012
//
// ^CLASS    : ACBRecord
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ACBRecord : public MFCanBFCbo, private boost::noncopyable
{
public:

   ACBRecord( BFAbstractCBO &parent );
   virtual ~ACBRecord();

   SEVERITY init (const BFData& data );
   
   void getField( const BFFieldId& idField, 
                  DString& strFieldValue, 
                  const BFDataGroupId& idDataGroup, 
                  bool formattedReturn = false ) const;

protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ACBRecord.hpp-arc  $
//
