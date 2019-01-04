#pragma once
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeDetaiList.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : August 2005
//
// ^CLASS    : GuaranteeDetaiList
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

class IFASTCBO_LINKAGE GuaranteeDetailList : public MFCanBFCbo, private boost::noncopyable
{
public:   
   GuaranteeDetailList( BFAbstractCBO &parent );
   virtual ~GuaranteeDetailList( void );

   SEVERITY getMore();

   SEVERITY init( const BFDataGroupId &idDataGroup,
                  const DString& dstrGuarSummRecId,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
private:

   BFData _requestData;

};

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeDetailList.hpp-arc  $
//
//   Rev 1.1   Jun 29 2006 17:21:32   popescu
//Incident# 655992 - restricted the call to view 351 - GuaranteeInfoDetail to only certain trans types.
//
//   Rev 1.0   Aug 17 2005 16:17:36   porteanm
//Initial revision.
 *  
 */