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
// ^FILE   : MessageEnvelope.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// ^CLASS    : MessageEnvelope
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

class MsgEventList;
class IFASTCBO_LINKAGE MessageEnvelope : public MFCanBFCbo, private boost::noncopyable
{
public:

   MessageEnvelope( BFAbstractCBO &parent );
   virtual ~MessageEnvelope();

   SEVERITY init( const BFData& Data );

	SEVERITY getMsgEventList( MsgEventList *&pMsgEventList,
						const BFDataGroupId& idDataGroup,bool bCreate = true );


	
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MessageEnvelope.hpp-arc  $
//
//   Rev 1.0   Feb 24 2005 17:43:28   ZHANGCEL
//Initial revision.
//
*/

