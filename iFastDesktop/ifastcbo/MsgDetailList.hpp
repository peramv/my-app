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
//    Copyright 2005 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MsgDetailList.hpp
// ^CLASS  : MsgDetailList
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

class IFASTCBO_LINKAGE MsgDetailList : public MFCanBFCbo, private boost::noncopyable
{
public:

   MsgDetailList( BFAbstractCBO &parent );
   virtual ~MsgDetailList( void );
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING,
                          const DString& dstrActivityID = NULL_STRING );

protected:

   SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgDetailList.hpp-arc  $
//
//   Rev 1.0   Feb 21 2005 11:13:40   hernando
//Initial revision.
