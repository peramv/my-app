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
// ^FILE   : MsgEvent.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MsgEvent
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

class IFASTCBO_LINKAGE MsgEvent : public MFCanBFCbo
{
public:

   MsgEvent( BFAbstractCBO &parent );
   virtual ~MsgEvent();

   SEVERITY init(const BFData& data );
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgEvent.hpp-arc  $
//
//   Rev 1.0   Feb 21 2005 11:13:56   hernando
//Initial revision.
