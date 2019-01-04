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
// ^FILE   : FeeScaleBaseList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : January 08, 2003
//
// ^CLASS    : FeeScaleBaseList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class FeeScaleBase;
class FeeParamBase;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScaleBaseList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FeeScaleBaseList( BFAbstractCBO &parent );
   virtual ~FeeScaleBaseList();
   DString getNextLevel(){ return(DString::asString( ++iLevel ));}
   void setFeeParamBase(FeeParamBase* pFeeParamBase){m_pFeeParamBase = pFeeParamBase;};
   FeeParamBase* getFeeParamBase(){return m_pFeeParamBase;};

protected:
   bool canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	void initLevel(int iLevel)
	{
		this->iLevel = iLevel;
	}

private:
   SEVERITY adjustLevel(DString dstrLevel,const BFDataGroupId& idDataGroup);
   int  iLevel;
   FeeParamBase* m_pFeeParamBase;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleBaseList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:40:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Oct 20 2004 16:24:10   YINGBAOL
//PTS10034800: take care Level
//
//   Rev 1.4   Mar 21 2003 18:10:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 17 2003 17:53:12   linmay
//added getNextLevel()
//
//   Rev 1.2   Jan 15 2003 15:27:10   linmay
//added log comment
*/
