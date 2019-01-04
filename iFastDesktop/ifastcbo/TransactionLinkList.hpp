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
//    Copyright 2005 By IFDS.
//
//
//******************************************************************************
//
// ^FILE   : TransactionLinkList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : 06/26/2005
//
// ^CLASS    : TransactionLinkList
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

class IFASTCBO_LINKAGE TransactionLinkList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransactionLinkList( BFAbstractCBO &parent );
   virtual ~TransactionLinkList();
   // Initialize function
	SEVERITY init( const DString& TransNum,
					   const DString& dstrTrack = I_("N"),
					   const DString& dstrPageName = NULL_STRING
                );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionLinkList.hpp-arc  $
//
//   Rev 1.0   Jul 06 2005 15:56:12   Yingbaol
//Initial revision.
//
//

**/