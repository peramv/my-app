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
// ^FILE   : FundGroupTypeList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : Jan 9, 2003
//
// ^CLASS    : FundGroupTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundGroupTypeList.hpp"
#include <ifastdataimpl\dse_dstc0126_vw.hpp>
#include <ifastdataimpl\dse_dstc0126_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_TYPE_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundGroupTypeList" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO  = I_( "N" );

}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace FUND_GROUP_TYPE
{
    extern CLASS_EXPORT I_CHAR * const SOFT_CAPPED  = I_("SFTCAP");
}

//******************************************************************************
FundGroupTypeList::FundGroupTypeList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
 //setVersionable( false );
}

//******************************************************************************
FundGroupTypeList::~FundGroupTypeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   setObjectAsList();
  
}

//******************************************************************************
SEVERITY FundGroupTypeList::init (
   const DString &fundGroupType, 
   const DString &dstrTrack /*= I_("N")*/,
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ));

   BFData queryData (ifds::DSTC0126_REQ);
   BFData *receivedData = new BFData (ifds::DSTC0126_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   queryData.setElementValue (ifds::FundGroupType, fundGroupType);
   queryData.setElementValue (ifds::AllFundGroupTypes, NO);
   ReceiveData (DSTC_REQUEST::FUND_TYPE_LIST, queryData, 
      *receivedData, DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundGroupTypeList::isFundExist (
   const DString &strFundCode, 
   const DString &strTypeCode, 
   const DString &strGroupCode)
{
   BFObjIter iter (*this, BF::HOST);
   bool bExists = false;

   while (!iter.end())
   {
      DString strFund;
      
      iter.getObject()->getField (ifds::FundCode, strFund, BF::HOST, false);

      if (strFund.strip() == strFundCode)
      {
         DString strFundGroupCode;
         
         iter.getObject()->getField (ifds::FundGroupCode, strFundGroupCode, BF::HOST, false);
         if (strFundGroupCode.strip() == strGroupCode)
         {
            DString strFundTypeCode;

            iter.getObject()->getField(ifds::FundGroupType, strFundTypeCode, BF::HOST, false);
            if (strFundTypeCode.strip() == strTypeCode)
            {
               bExists = true;
               break;
            }
         }
      }
      ++iter;
   }
   return bExists;
}

//******************************************************************************
bool FundGroupTypeList::isFundClassExist (
   const DString &strFundCode, 
   const DString &strClassCode, 
   const DString &strTypeCode, 
   const DString &strGroupCode)
{
   BFObjIter iter (*this, BF::HOST);

   DString strKey = getStrKey (strFundCode, strClassCode, strTypeCode, strGroupCode);
   return iter.positionByKey (strKey);
}

//******************************************************************************
DString FundGroupTypeList::getFundGroupCode(const DString &fundCode, 
                                            const DString &classCode)
{
   DString dstrFundGroupCode, dstrFundCode(fundCode), dstrClassCode(classCode);
   BFObjIter iter(*this, BF::HOST);

   while (!iter.end())
   {
       DString iterFundCode, iterClassCode;

       iter.getObject()->getField(ifds::FundCode, iterFundCode, BF::HOST, false);
       iter.getObject()->getField(ifds::ClassCode, iterClassCode, BF::HOST, false);

       if (iterFundCode.stripAll().upperCase() == dstrFundCode.stripAll().upperCase() &&
           iterClassCode.stripAll().upperCase() == dstrClassCode.stripAll().upperCase())
       {
           iter.getObject()->getField(ifds::FundGroupCode, dstrFundGroupCode, BF::HOST, false);
           break;
       }

       ++iter;
   }

   return dstrFundGroupCode;
}

//******************************************************************************
void FundGroupTypeList::getStrKey( DString &strKey, const BFData *data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   strKey = NULL_STRING;
   if (data)
   {
      DString strFund = data->getElementValue( I_( "FundCode" ) );
      strKey += strFund.strip().upperCase();
      strKey += I_(" ");

      DString strClass = data->getElementValue( I_( "ClassCode" ) );
      strKey += strClass.strip().upperCase();
      strKey += I_(" ");

      DString strFundGroupCode = data->getElementValue( I_( "FundGroupCode" ) );
      strKey += strFundGroupCode.strip().upperCase();
      strKey += I_(" ");

      DString strFundGroupType = data->getElementValue( I_( "FundGroupType" ) );
      strKey += strFundGroupType.strip().upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }
}

//******************************************************************************
DString FundGroupTypeList::getStrKey (
   const DString &strFundCode, 
   const DString &strClassCode, 
   const DString &strTypeCode, 
   const DString &strGroupCode)
{
   DString strRetVal (NULL_STRING);
   BFData data(ifds::DSTC0126_VWRepeat_Record);
   
   data.setElementValue (ifds::FundCode, strFundCode, true, false);
   data.setElementValue (ifds::ClassCode, strClassCode, true, false);
   data.setElementValue (ifds::FundGroupType, strTypeCode, true, false);
   data.setElementValue (ifds::FundGroupCode, strGroupCode, true, false);
   getStrKey (strRetVal, &data);
   return strRetVal;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupTypeList.cpp-arc  $
// 
//    Rev 1.7   Nov 24 2004 10:18:32   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.6   Nov 18 2004 13:28:10   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.5   Nov 14 2004 14:42:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Feb 26 2004 13:43:10   popescu
// PTS 10026434, changed name of parameters for method getFundGroupTypeList to signal a broader use
// 
//    Rev 1.3   Apr 15 2003 10:48:14   linmay
// Sync up with 1.1.1.0
// 
//    Rev 1.2   Mar 21 2003 18:11:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Feb 05 2003 13:01:10   KOVACSRO
// Temporary tuneup - since at this point we only use REBAL type, we'll only ask for these records
// 
//    Rev 1.0   Jan 13 2003 10:15:28   KOVACSRO
// Initial revision.
// 
// 
*/