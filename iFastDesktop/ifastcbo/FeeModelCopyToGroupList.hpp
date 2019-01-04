#pragma once


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial 
//    Data Services, Ltd., are proprietary in nature and as such
//    are confidential. Any unauthorized use or disclosure of such
//    information may result in civil liabilities.
//
//    Copyright 2015 by International Financial Data Services, Ltd.
//
//
//******************************************************************************
//
// ^FILE   : FeeModelCopyToGroupList.hpp
// ^AUTHOR : 
// ^DATE   : 9 July 2015
//
// ^CLASS    : FeeModelCopyToGroupList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class MgmtCoOptions;
class MFAccount;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeModelCopyToGroupList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeModelCopyToGroupList( BFAbstractCBO &parent );
   virtual ~FeeModelCopyToGroupList( void );

   SEVERITY init(const DString& dstrTrack = I_("N"), 
                 const DString& dstrPageName = NULL_STRING);
   SEVERITY addChildRecord(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelCopyToGroupList.hpp-arc  $
// 