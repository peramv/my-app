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
// ^FILE   : HypoRedAcctHoldingsList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedAcctHoldingsList
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

class IFASTCBO_LINKAGE HypoRedAcctHoldingsList : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedAcctHoldingsList( BFAbstractCBO &parent );
   virtual ~HypoRedAcctHoldingsList();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
	bool needsRefresh(const BFDataGroupId& idDataGroup);
	bool isValidForInquiry(const BFDataGroupId& idDataGroup);

protected:

   /**
    * virtual function. It should be overwriten in order to do special processing on object creation
    * ( in lists when we are adding an existing element )
    * @param data    - the data object from which we are taking data from
    * @param pObjOut - here we are returning the new object
 
   */
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:

   void setDefaultAmounts(const BFDataGroupId& idDataGroup);
   BFData *_pRequestData;


};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedAcctHoldingsList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:13:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:37:30   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:34   KOVACSRO
//Initial Revision
// 
 
*/

