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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : JFundInDiv.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 25/02/00
//
// ^CLASS    : JFundInDiv
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE JFundInDiv : public MFCanBFCbo, private boost::noncopyable
{
public:
   JFundInDiv( BFAbstractCBO &parent );
   virtual ~JFundInDiv( void );

   SEVERITY init( DString& dstFundCode, 
                  DString& dstClassCode, 
                  DString& dstFromDate, 
                  DString& dstToDate,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );


   SEVERITY search( bool bClearPreviousSearch = false );

private:
   BFData _requestData;

};

///#endif

