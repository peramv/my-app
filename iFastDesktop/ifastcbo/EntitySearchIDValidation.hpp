#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntitySearchIDValidation.hpp
// ^AUTHOR : 
// ^DATE   : Dec, 2010
//
// ^CLASS    : EntitySearchIDValidation
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

class IFASTCBO_LINKAGE EntitySearchIDValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   EntitySearchIDValidation( BFAbstractCBO &parent );
   virtual ~EntitySearchIDValidation();

   SEVERITY init(const DString& dstrWhereUse,
                 const DString& dstrRelationShip,
                 const DString& dstrSrchIdType,
                 const DString& dstrBicCodeValue,
                 const DString& dstrEntityId,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);

protected:

private:
   BFData* pRequestData_;
   BFData* pResponseData_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EntitySearchIDValidation.hpp-arc  $
//
//   Rev 1.0   Dec 27 2010 02:11:40   dchatcha
//Initial revision.
//
