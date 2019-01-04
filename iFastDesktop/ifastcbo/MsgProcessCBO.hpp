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
//    Copyright 2005, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : MsgProcessCBO.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MsgProcessCBO
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class MsgActivityList;

class IFASTCBO_LINKAGE MsgProcessCBO : public MFCanBFCbo
{
public:

   MsgProcessCBO( BFAbstractCBO &parent );
   virtual ~MsgProcessCBO();

   SEVERITY init(const BFData& data );
	SEVERITY getMsgActivityList( MsgActivityList *&pMsgActivityList,
						const BFDataGroupId& idDataGroup,bool bCreate = true );
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgProcessCBO.hpp-arc  $
//
//   Rev 1.0   Feb 21 2005 11:14:18   hernando
//Initial revision.
