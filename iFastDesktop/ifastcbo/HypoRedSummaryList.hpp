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
// ^FILE   : HypoRedSummaryList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedSummaryList
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

class IFASTCBO_LINKAGE HypoRedSummaryList : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedSummaryList( BFAbstractCBO &parent );
   virtual ~HypoRedSummaryList();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	bool needsRefresh(const BFDataGroupId& idDataGroup);

protected:

   /**
    * virtual function. It should be overwriten in order to do special processing on object creation
    * ( in lists when we are adding an existing element )
    * @param data    - the data object from which we are taking data from
    * @param pObjOut - here we are returning the new object
 
   */
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	/**
    * gets the string part of the key for an object
    * @param strKey       - a reference to a string in which we will return the string key. 
    * @param data         - pointer to a data object from which we can take data in oreder to compute the key 
   */
   void getStrKey( DString &strKey, const BFData *data = NULL ); 
	
private:

	void refreshCurrencyList(const BFDataGroupId& idDataGroup);
	SEVERITY	prepareRequest(const BFDataGroupId& idDataGroup);
	bool isFixedPartChanged(const BFDataGroupId& idDataGroup);
	bool isReqFieldChanged(const BFFieldId& fieldId, const BFDataGroupId& idDataGroup);
	bool isRepeatReqFieldChanged(BFData& repeat, const BFFieldId& repeatFieldId, 
		BFAbstractCBO* pHolding, const BFFieldId& holdingFieldId, const BFDataGroupId& idDataGroup);
   void viewFailureCleanup(const BFDataGroupId& idDataGroup);

	BFData* _pView227;
	BFData* _pView398;
	BFData* _pRequest398;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedSummaryList.hpp-arc  $
//
//   Rev 1.4   Sep 11 2009 16:40:32   yingz
//using view 398
//
//   Rev 1.3   Nov 14 2004 14:44:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:14:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:42:40   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:40   KOVACSRO
//Initial Revision
// 
 
*/

