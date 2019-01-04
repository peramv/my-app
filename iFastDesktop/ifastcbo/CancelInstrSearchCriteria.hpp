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
// ^FILE   : FileSearchCriteria.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// ^CLASS    : FileSearchCriteria
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

class IFASTCBO_LINKAGE CancelInstrSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

   CancelInstrSearchCriteria( BFAbstractCBO &parent );
   virtual ~CancelInstrSearchCriteria();

   SEVERITY init(const BFDataGroupId& idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

protected:

   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
    
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
											  const BFDataGroupId &idDataGroup);
 
private:

	SEVERITY loadNetworkIDValues (const BFDataGroupId &idDataGroup);
   DString getCurrentBusDate();

	//field validations
   SEVERITY validateDateRange(const BFDataGroupId& idDataGroup);
  
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CancelInstrSearchCriteria.hpp-arc  $
//
//   Rev 1.0   Nov 04 2005 11:48:38   ZHANGCEL
//Initial revision.
//
//   Rev 1.0   Feb 24 2005 17:41:18   ZHANGCEL
//Initial revision.
//
*/

