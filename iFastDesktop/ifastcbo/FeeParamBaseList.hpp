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
// ^FILE   : FeeParamBaseList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : January 07, 2003
//
// ^CLASS    : FeeParamBaseList
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

class IFASTCBO_LINKAGE FeeParamBaseList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
	FeeParamBaseList( BFAbstractCBO &parent );
	virtual ~FeeParamBaseList();
	virtual void InitNew(const BFDataGroupId& idDataGroup )=0;
   bool canUpdateObject( const DString&  strKey, const BFDataGroupId& idDataGroup);

protected:

   virtual void getStrKey1( DString &strKey, const BFData *data = NULL );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual bool canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup );


};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamBaseList.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:40:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:09:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 17 2003 14:04:32   YINGBAOL
//change init to initNew
//
//   Rev 1.2   Jan 15 2003 15:23:08   linmay
//added log comment
*/

