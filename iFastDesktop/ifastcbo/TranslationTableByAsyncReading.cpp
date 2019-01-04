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
// ^FILE   : TranslationTableByAsyncReading.cpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : MiscInfoExternalInstitutionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "TranslationTable.hpp"
#include "TranslationTableByAsyncReading.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

#include <ifastdataimpl\dse_dstc0254_req.hpp>
#include <ifastdataimpl\dse_dstc0254_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MISC_INFO_TRANSLATION_TABLE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyName;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
   extern CLASS_IMPORT const BFTextFieldId TrackTrOther;
}

namespace
{
   const I_CHAR * const CLASSNAME  = I_("MiscInfoExternalInstitutionList");
}

//******************************************************************************
MiscInfoExternalInstitutionList::MiscInfoExternalInstitutionList(BFAbstractCBO &parent)
:TranslationTable (parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
MiscInfoExternalInstitutionList::~MiscInfoExternalInstitutionList()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY MiscInfoExternalInstitutionList::init()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData *_pRequestData = new BFData (ifds::DSTC0254_REQ);
   DString mgmtCoIdOut;
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   _pRequestData->setElementValue (ifds::Track, I_("N"));
   _pRequestData->setElementValue (ifds::Activity, NULL_STRING);
   _pRequestData->setElementValue( ifds::GroupCode, I_("IL") );

   AsyncReceiveData ( DSTC_REQUEST::MISC_INFO_TRANSLATION_TABLE, *_pRequestData, ifds::DSTC0254_VW, DSTCRequestor (getSecurity(), true));

    return GETCURRENTHIGHESTSEVERITY();
}

 //******************************************************************************
void MiscInfoExternalInstitutionList::getSubstitutionList(DString& dstrSubstitutionList, bool bRequireViewDesc)
{
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

   DString dstrCode, dstrDescription;
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
      iter.getObject()->getField( ifds::MiscDesc, dstrDescription, BF::HOST, false );
      ++iter;
      dstrDescription.strip();
      dstrCode.strip();
      dstrSubstitutionList +=  dstrCode + I_("=") + dstrDescription + I_(";");
   }
}

//******************************************************************************
void MiscInfoExternalInstitutionList::getStrKey( DString &strKey, const BFData *data /* = NULL */)
{
   DString miscCode;
   if(data != NULL)
   {
      data->getElementValue(ifds::MiscCode, miscCode);
      miscCode.strip();
   }
   
   if(I_("") == miscCode)
      BFCBO::getStrKey(miscCode, data);
   
   strKey = miscCode;
}

bool MiscInfoExternalInstitutionList::getDescription(const DString& miscCode, DString& miscDescription, bool& isOther)
{
   bool retVal = false;
   isOther = false;
   DString strOtherCode;
   MgmtCoOptions *pMgmtCoOptions = NULL;
   getMgmtCo().getMgmtCoOptions(pMgmtCoOptions);
   if(pMgmtCoOptions)
      pMgmtCoOptions->getField(ifds::TrackTrOther, strOtherCode, BF::HOST, false);
   strOtherCode.strip().upperCase();
   DString lookupValue(miscCode);

   if (!strOtherCode.empty() && lookupValue.stripAll().upperCase() == strOtherCode)
   {
       miscDescription = lookupValue;
       isOther = true;
       retVal = true;
   }
   else
   {
      BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

      if( iter.positionByKey(miscCode) )
      {
         iter.getObject()->getField( ifds::MiscDesc, miscDescription, BF::HOST); 
         retVal = true;
      }
   }
   return retVal;
}

bool MiscInfoExternalInstitutionList::codeExists(const DString& miscCode)
{
   bool retVal = false;

   DString strOtherCode;
   MgmtCoOptions *pMgmtCoOptions = NULL;
   getMgmtCo().getMgmtCoOptions(pMgmtCoOptions);
   if(pMgmtCoOptions)
      pMgmtCoOptions->getField(ifds::TrackTrOther, strOtherCode, BF::HOST, false);

   strOtherCode.strip().upperCase();
   DString lookupValue(miscCode);

   if (!strOtherCode.empty() && lookupValue.stripAll().upperCase() == strOtherCode)
   {
       retVal = true;
   }
   else
   {
      BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

      if( iter.positionByKey(miscCode) )
      {
         retVal = true;
      }
   }

   return retVal;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TranslationTableByAsyncReading.cpp-arc  $
// 
