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
//    Copyright 2011 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : GIAInvAttribList.hpp
// ^AUTHOR : Panatchakorn Pokawinkoon
// ^DATE   : Oct 26, 2000
//
// ^CLASS    : GIAInvAttribList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#include <ifastdataimpl\dse_dstc0420_req.hpp>
#include <ifastdataimpl\dse_dstc0420_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE GIAInvAttribList : public MFCanBFCbo, private boost::noncopyable
{
public:
   GIAInvAttribList( BFAbstractCBO &parent );
   virtual ~GIAInvAttribList();
                                    
   SEVERITY init( const DString &fundCode,
                  const DString &classCode,
                  const DString &tradeDate,
                  const DString &dstrTrack = I_( "N" ),
                  const DString &dstrPageName = NULL_STRING);
protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/** $Log:   Y:/VCS/BF iFAST/ifastcbo/GIAInvAttribList.hpp-arc  $
//
//   Rev 1.2   Nov 30 2011 00:13:10   dchatcha
//P0186477/FN03 - GIA - Purchase
//
//   Rev 1.1   Nov 27 2011 19:40:38   popescu
//INA Commission Work
// 
// Initial revision.
 **/
