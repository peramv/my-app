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
// ^FILE   : AcctGrpConfigList.hpp
// ^AUTHOR : 
// ^DATE   : 20 July 2015
//
// ^CLASS    : AcctGrpConfigList
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

class IFASTCBO_LINKAGE AcctGrpConfigList : public MFCanBFCbo, private boost::noncopyable
{
public:
   AcctGrpConfigList( BFAbstractCBO &parent );
   virtual ~AcctGrpConfigList( void );

   SEVERITY init();

   SEVERITY buildListOfCopyableGroup(DString& copyableList,const BFDataGroupId& idDataGroup);

protected:

private:
    BFData *requestData468;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGrpConfigList.hpp-arc  $
// 