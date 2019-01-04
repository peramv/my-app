#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//
//******************************************************************************
//
// ^FILE   : ExternalInstitution.hpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : ExternalInstitution
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

class IFASTCBO_LINKAGE ExternalInstitution : public MFCanBFCbo, private boost::noncopyable
{
public:

   ExternalInstitution( BFAbstractCBO &parent );
   virtual ~ExternalInstitution();
   
   SEVERITY init( const BFData& data );

private:

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ExternalInstitution.hpp-arc  $
// 