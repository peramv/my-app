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
// ^FILE   : FeeModelCopyToGroup.hpp
// ^AUTHOR : 
// ^DATE   : 9 July 2015
//
// ^CLASS    : FeeModelCopyToGroup
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class FeeModelCopyToGroupList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeModelCopyToGroup : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeModelCopyToGroup (BFAbstractCBO &parent);
   virtual ~FeeModelCopyToGroup();

   SEVERITY init (const BFData &data); 
   SEVERITY initNew (const BFDataGroupId &idDataGroup);

protected:

private:

   void initFieldSubstitutionList(const BFDataGroupId &idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelCopyToGroup.hpp-arc  $
// 