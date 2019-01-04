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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MessageEnvelopeList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 17, 2005
//
// ^CLASS    : MessageEnvelopeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

class IFASTCBO_LINKAGE MessageEnvelopeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   MessageEnvelopeList( BFAbstractCBO &parent );
   virtual ~MessageEnvelopeList();

   SEVERITY init( const DString& dstrNetWorkId, 
						const DString& dstrFileName,
						const DString& dstrStartDate,
						const DString& dstrEndDate,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
	SEVERITY init( const BFData& data );

   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
	SEVERITY getMore( );

private:

	BFData queryData; 
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MessageEnvelopeList.hpp-arc  $
//
//   Rev 1.1   Mar 30 2005 17:20:04   ZHANGCEL
//Incident #276685 -- Fix <more> functionality issue
//
//   Rev 1.0   Feb 24 2005 17:43:18   ZHANGCEL
//Initial revision.
 *
 */
