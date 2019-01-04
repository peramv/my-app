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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : LSIFCodesList.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : May 2004
//
// ^CLASS    : LSIFCodesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "lsifcodeslist.hpp"

#include <ifastdataimpl\dse_dstc0295_req.hpp>
#include <ifastdataimpl\dse_dstc0295_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest LSIF_CODES;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("LSIFCodesList");
}

namespace CND
{
}

//******************************************************************************
LSIFCodesList::LSIFCodesList  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setObjectAsList ();
   setVersionable( false );

}

//******************************************************************************
LSIFCodesList::~LSIFCodesList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY LSIFCodesList::init (
   const DString &dstrTrack, 
   const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData queryData (ifds::DSTC0295_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   AsyncReceiveData (DSTC_REQUEST::LSIF_CODES, queryData, 
      ifds::DSTC0295_VW, DSTCRequestor (getSecurity (), true));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void LSIFCodesList::buildKey (const DString &lsifCode, DString &strKey)
{
   strKey = lsifCode;
   strKey.strip ();
   strKey.upperCase ();
}

//******************************************************************************
void LSIFCodesList::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey (data->getElementValue (ifds::LSIFCode), strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
DString LSIFCodesList::getLSIFCodesSubstitutionList ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getLSIFCodesSubstitutionList"));
   
   DString retLSIFSubstList,
      lsifSubstList,
      code,
      description;
   BFProperties *pPropsLSIFCode = 
      getFieldProperties (ifds::LSIFCode, BF::HOST);
   
   pPropsLSIFCode->getAllSubstituteValues (lsifSubstList);

   I_CHAR *temp = const_cast<I_CHAR*> (lsifSubstList.c_str ());
   BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

   do
   {
      temp = parseIdiString (temp, code, description);
      if (iter.positionByKey (code))
      {
         DString available;

         iter.getObject ()->getField (ifds::AvailOnInput, 
            available, BF::HOST, false); 
         available.strip ();
         if (available == I_("1"))
         {
            retLSIFSubstList += code + I_("=") + description + I_(";");
         }
      }
   } 
   while (temp && temp != NULL_STRING && *temp);
   return retLSIFSubstList;
}

//******************************************************************************
DString LSIFCodesList::getDSCOverrideFlag (const DString &lsifCode)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDSCOverrideFlag"));

   DString dscOverrideFlag = I_("0");
   BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

   if (iter.positionByKey (lsifCode))
   {
      iter.getObject ()->getField (ifds::LSIFDSCOverrideCode, 
         dscOverrideFlag, BF::HOST, false); 
      dscOverrideFlag.strip ();
   }
   return dscOverrideFlag;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/LSIFCodesList.cpp-arc  $
// 
//    Rev 1.5   Dec 10 2004 14:52:44   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.4   Nov 24 2004 10:18:38   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.3   Nov 18 2004 13:28:16   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.2   Nov 14 2004 14:49:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   May 12 2004 09:10:08   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.0   May 09 2004 20:17:22   popescu
// Initial revision.
// 
//    Rev 1.0   May 06 2004 18:43:38   popescu
// Initial revision.
*/