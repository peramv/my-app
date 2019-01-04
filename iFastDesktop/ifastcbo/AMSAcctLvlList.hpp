#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2007, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvlList.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 19, 2007
//
// ^CLASS    : AMSAcctLvl
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AMSAcctLvl;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AMSAcctLvlList : public MFCanBFCbo, private boost::noncopyable
{

public:
   AMSAcctLvlList( BFAbstractCBO &parent );
   virtual ~AMSAcctLvlList( void );

   // Initialize function
   SEVERITY init( const DString& dstrShrNum,
                  const DString& dstrAccountNum,
				      const DString& dstrTrack = I_( "N" ),
				      const DString& dstrPageName = NULL_STRING);

   SEVERITY initNew ( const DString& dstrShrNum, 
                      const DString& dstrAccountNum);

protected:
   SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject (BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);

private:
	BFData _requestData;   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSAcctLvlList.hpp-arc  $
//
//   Rev 1.4   14 Sep 2007 10:59:26   popescu
//Incident 1003183 (GAP2360/02) - fixed AMS allocations
//
//   Rev 1.3   Aug 30 2007 11:03:16   smithdav
//Add AccountNum parameter to the initNew of the AMSAcctLvlList.
//
//   Rev 1.2   Jul 11 2007 16:21:36   smithdav
//PET 2360 FN02 - AMS - Interim changes
//
//   Rev 1.1   Jun 22 2007 14:19:02   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.0   Jun 20 2007 11:43:02   porteanm
//Initial revision.
//
*/
