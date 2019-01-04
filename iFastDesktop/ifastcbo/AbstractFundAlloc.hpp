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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AbstractFundAlloc.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 13, 02
//
// ^CLASS    : AbstractFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Ams fund allocation 
//
//******************************************************************************

#ifndef FUNDALLOC_HPP
   #include <ifastcbo\FundAlloc.hpp>
#endif 


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FundDetail;
class IFASTCBO_LINKAGE AbstractFundAlloc:public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AbstractFundAlloc( BFAbstractCBO &parent );
   virtual ~AbstractFundAlloc( void );
	virtual SEVERITY initExisting(const BFData &data);


   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);

protected:

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   //validation
   virtual SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   virtual SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   virtual SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   virtual SEVERITY validatePercentage(const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateFundNumber( const DString& strValue, const BFDataGroupId& idDataGroup ); 
	SEVERITY setFundNumber(const BFDataGroupId& idDataGroup);
	SEVERITY setFundClassCode(const BFDataGroupId& idDataGroup);

	SEVERITY getFundDetail( const DString& strFundCode, 
                                           const DString& strClassCode, 
                                           FundDetail *&pFundDetail );



private:



};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractFundAlloc.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:24:04   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 17:53:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 22 2002 14:35:12   YINGBAOL
//change getfunddetail
//
//   Rev 1.0   Nov 13 2002 10:01:16   YINGBAOL
//Initial Revision



*/