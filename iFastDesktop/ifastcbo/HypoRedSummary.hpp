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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : HypoRedSummary.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedSummary
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

class HypoRedDetailList;

class IFASTCBO_LINKAGE HypoRedSummary : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedSummary( BFAbstractCBO &parent );
   virtual ~HypoRedSummary();

   SEVERITY init( const BFData& summaryData, const BFData& allDetailsData,
		const DString& dstrTrack = I_("N"),
      const DString& dstrPageName = NULL_STRING );
	SEVERITY getHypoRedDetailList( HypoRedDetailList *&pHypoRedDetailList, const BFDataGroupId& idDataGroup);


protected:

   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;


private:

	void formatUnits(DString& strValue, const BFDataGroupId& idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedSummary.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:14:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:41:56   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:40   KOVACSRO
//Initial Revision
// 
 
*/

