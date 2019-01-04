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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeScaleBase.hpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2002
//
// ^CLASS    : FeeScaleBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
class BFData;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScaleBase : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeScaleBase( BFAbstractCBO &parent );
   virtual ~FeeScaleBase();
   SEVERITY ChangeLevel(  const int idLevel,const BFDataGroupId& idDataGroup );
   void setValidFlagDerive( const BFFieldId& idField,const BFDataGroupId& idDataGroup,bool bValid ) 
   {
      BFCBO::setValidFlag( idField,idDataGroup,bValid );
   }

protected: 
    virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

	SEVERITY validateLUBound(const BFDataGroupId& idDataGroup );
    virtual SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup ); 
	SEVERITY validateMinMax(const BFDataGroupId& idDataGroup );
    SEVERITY validateMaxFee(const BFDataGroupId& idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleBase.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:40:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Aug 10 2004 11:24:22   FENGYONG
//PET 1117 FN 5 - Client condition Fee
//
//   Rev 1.5   Jul 21 2003 15:03:22   linmay
//PTS Ticket #10014935
//
//   Rev 1.4   Mar 21 2003 18:09:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 24 2003 16:15:56   linmay
//added validateMinMax(const BFDataGroupId& idDataGroup );
//
//   Rev 1.2   Jan 17 2003 17:53:58   linmay
//added changelevel()
//
//   Rev 1.1   Jan 15 2003 11:59:06   linmay
//added Log Comment
// 
*/
