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
// ^FILE   : AcctGrpConfigList.cpp
// ^AUTHOR :
// ^DATE   : 20 July 2015
//
// ^CLASS    : AcctGrpConfigList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AcctGrpConfigList.hpp"

#include "mgmtco.hpp"
#include "translationtable.hpp"

#include <ifastdataimpl\dse_dstc0468_vw.hpp>
#include <ifastdataimpl\dse_dstc0468_req.hpp>
#include <ifastdataimpl\dse_dstc0468_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_GRP_CONFIG_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("AcctGrpConfigList");
   const I_CHAR * const ACCT_GROUP_CONFIG_GROUP_CODE  = I_("AGT");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeModelCopyToGroupHeading;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFNumericFieldId FeeModelRecid;
}

//******************************************************************************
AcctGrpConfigList::AcctGrpConfigList(BFAbstractCBO &parent)
   : MFCanBFCbo( parent )
   , requestData468(nullptr)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}

//******************************************************************************
AcctGrpConfigList::~AcctGrpConfigList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctGrpConfigList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   bool bRetrieveAll = true;
   // receive data from back end
   DString mgmtCoIdOut;
   requestData468 = new BFData(ifds::DSTC0468_REQ);  

   requestData468->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData468->setElementValue( ifds::Track, I_("N") );
   requestData468->setElementValue( ifds::Activity, NULL_STRING );
   requestData468->setElementValue( ifds::NextKey, NULL_STRING );

   BFData* responseData = new BFData(ifds::DSTC0468_VW);
   ReceiveData(DSTC_REQUEST::ACCT_GRP_CONFIG_INQUIRY, 
               *requestData468, 
               *responseData, 
               DSTCRequestor( getSecurity(), 
                              bRetrieveAll, false));

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctGrpConfigList::buildListOfCopyableGroup(DString& copyableList,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildListOfCopyableGroup"));

   TranslationTable* pTranslationTable = nullptr;
   DString dstrSubstitutionList = NULL_STRING, dstrGroupList = NULL_STRING;
   DString strDescription = NULL_STRING;
   copyableList = NULL_STRING;

   BFSubst lBFSubst;
   getMgmtCo ().getTranslationTable (ACCT_GROUP_CONFIG_GROUP_CODE, pTranslationTable);
   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList (dstrSubstitutionList,true);

      BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      iter.begin();

      while(!iter.end())
      {
         DString groupType, configName, configValue;
         iter.getObject()->getField(ifds::AcctGrpType, groupType, idDataGroup, false);
         iter.getObject()->getField(ifds::ConfigName, configName, idDataGroup, false);
         iter.getObject()->getField(ifds::ConfigValue, configValue, idDataGroup, false);
         groupType.strip().upperCase();
         configName.strip().upperCase();
         configValue.strip().upperCase();

         if (configName == I_("ALLOWTOCOPY") && configValue == I_("YES"))
         {
            strDescription = DSTCommonFunctions::getDescription( groupType, dstrSubstitutionList );

            if (!strDescription.empty()){
               lBFSubst.addSubst( groupType, strDescription );
            }
         }
         ++iter;
      }
   }

   lBFSubst.getList( copyableList );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGrpConfigList.cpp-arc  $
// 