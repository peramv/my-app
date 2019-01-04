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
// ^FILE   : Payment.hpp
// ^AUTHOR : 
// ^DATE   : 17 Nov 2011
//
// ^CLASS    : Payment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE Payment : public MFCanBFCbo, private boost::noncopyable
{
public:
   Payment( BFAbstractCBO &parent );
   virtual ~Payment();
  SEVERITY init(const DString &recordType,
	             const DString &transNum,
				 const DString &transId,
				 const DString &Payment,
				 const BFDataGroupId& idDataGroup );
 
  SEVERITY init(const BFData& data );
   
	


};


//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Payment.hpp-arc  $
//
//   Rev 1.0   Dec 08 2011 00:37:06   wp040032
//Initial revision.
//