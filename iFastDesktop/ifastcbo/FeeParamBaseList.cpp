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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeParamBaseList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Jan. 07, 2002
//
// ^CLASS    : FeeParamBaseList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeparamBaselist.hpp"
#include "feeparamBase.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "feeparamconfig.hpp"
#include "feeparamconfiglist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_LIST;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeParamBaseList" );  
   const I_CHAR * const IDI_CODE    = I_("CODE");  
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_CODE_OVERLAPED;  
   extern const long ERR_DELETE_FEE_PARAMETER;
   extern const long ERR_COMM_GROUP_CODE_OVERLAPED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId ShGroup;
   extern CLASS_IMPORT const BFTextFieldId FundFromCode;
   extern CLASS_IMPORT const BFTextFieldId ClassFromCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId UpdateRule;
   extern CLASS_IMPORT const BFDateFieldId FMLastProcDate;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FeeParamBaseList::FeeParamBaseList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FeeParamBaseList::~FeeParamBaseList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//*********************************************************************************
//duplicate check for newly added records.
SEVERITY FeeParamBaseList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   DString dstrFeeCode1, dstrFundCode1, dstrClassCode1, dstrCommGroupCode1, dstrEffectiveDate1,dstrStopDate1;
   DString dstrBrokerCode1, dstrFundFromCode1, dstrClassFromCode1, dstrShGroup1, dstrBranchCode1, dstrSalesRepCode1;
   DString dstrFeeCode2, dstrFundCode2, dstrClassCode2, dstrCommGroupCode2, dstrEffectiveDate2,dstrStopDate2;
   DString dstrBrokerCode2, dstrFundFromCode2, dstrClassFromCode2, dstrShGroup2, dstrBranchCode2, dstrSalesRepCode2;


   while( !iter.end() )
   {
    	BFAbstractCBO* cbo1 = iter.getObject();
		if (cbo1->isNew() && !iter.isDummy() )
        {
			cbo1->getField(ifds::FeeCode,dstrFeeCode1,idDataGroup,false);
			cbo1->getField(ifds::FundCode,dstrFundCode1,idDataGroup,false);
			cbo1->getField(ifds::ClassCode,dstrClassCode1,idDataGroup,false);
			cbo1->getField(ifds::CommGroup,dstrCommGroupCode1,idDataGroup,false);
			cbo1->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false);

			cbo1->getField(ifds::FundFromCode,dstrFundFromCode1,idDataGroup,false);
			cbo1->getField(ifds::ClassFromCode,dstrClassFromCode1,idDataGroup,false);
			cbo1->getField(ifds::StopDate,dstrStopDate1,idDataGroup,false);
			cbo1->getField(ifds::BrokerCode,dstrBrokerCode1,idDataGroup,false);
			cbo1->getField(ifds::ShGroup,dstrShGroup1,idDataGroup,false);
			cbo1->getField(ifds::BranchCode,dstrBranchCode1,idDataGroup,false);
			cbo1->getField(ifds::SlsrepCode,dstrSalesRepCode1,idDataGroup,false);


			dstrFeeCode1.strip().upperCase();
			dstrFundCode1.strip().upperCase();
			dstrClassCode1.strip().upperCase();
			dstrEffectiveDate1.strip(); 
			dstrStopDate1.strip();
			dstrBrokerCode1.strip();
			dstrCommGroupCode1.strip().upperCase();
			dstrFundFromCode1.strip().upperCase();
			dstrClassFromCode1.strip().upperCase();
			dstrShGroup1.strip();
			dstrBranchCode1.strip();
			dstrSalesRepCode1.strip();

			iter1.positionByKey( iter.getStringKey() );
			++iter1;
			for( iter1; !iter1.end(); ++iter1 )
			{
				BFAbstractCBO* cbo2 = iter1.getObject();
				if ( cbo2->isNew() && !iter1.isDummy() )
				{
					cbo2->getField(ifds::FeeCode,dstrFeeCode2,idDataGroup,false);
					cbo2->getField(ifds::FundCode,dstrFundCode2,idDataGroup,false);
					cbo2->getField(ifds::ClassCode,dstrClassCode2,idDataGroup,false);
					cbo2->getField(ifds::CommGroup,dstrCommGroupCode2,idDataGroup,false);
					cbo2->getField(ifds::EffectiveDate,dstrEffectiveDate2,idDataGroup,false);

					cbo2->getField(ifds::FundFromCode,dstrFundFromCode2,idDataGroup,false);
					cbo2->getField(ifds::ClassFromCode,dstrClassFromCode2,idDataGroup,false);
					cbo2->getField(ifds::StopDate,dstrStopDate2,idDataGroup,false);
					cbo2->getField(ifds::BrokerCode,dstrBrokerCode2,idDataGroup,false);
					cbo2->getField(ifds::ShGroup,dstrShGroup2,idDataGroup,false);
					cbo2->getField(ifds::BranchCode,dstrBranchCode2,idDataGroup,false);
					cbo2->getField(ifds::SlsrepCode,dstrSalesRepCode2,idDataGroup,false);

					dstrFeeCode2.strip().upperCase();
					dstrFundCode2.strip().upperCase();
					dstrClassCode2.strip().upperCase();
					dstrEffectiveDate2.strip(); 
					dstrStopDate2.strip();
					dstrBrokerCode2.strip();
					dstrCommGroupCode2.strip().upperCase();
					dstrFundFromCode2.strip().upperCase();
					dstrClassFromCode2.strip().upperCase();
					dstrShGroup2.strip();
					dstrBranchCode2.strip();
					dstrSalesRepCode2.strip();

					if(dstrCommGroupCode1 == NULL_STRING && dstrCommGroupCode2 == NULL_STRING )
					{
						if( dstrFeeCode1 == dstrFeeCode2 && dstrFundCode1 == dstrFundCode2 && 
							dstrClassCode1 == dstrClassCode2 && dstrBrokerCode1 == dstrBrokerCode2 &&
							dstrShGroup1 == dstrShGroup2 && dstrFundFromCode1 == dstrFundFromCode2 &&
							dstrClassFromCode1 == dstrClassFromCode2 && dstrBranchCode1 == dstrBranchCode2 &&
							dstrSalesRepCode1 == dstrSalesRepCode2 )
						{
							if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																	   dstrEffectiveDate2, dstrStopDate2 ) )
							{
								DString strTemp;                 
								addIDITagValue( strTemp, IDI_CODE, dstrFeeCode1 +I_(" ") + dstrFundCode1 + I_(" ") + dstrClassCode2);         
								ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, strTemp);
								return(GETCURRENTHIGHESTSEVERITY());
							}
						}
					}
					else
					{
						 if (dstrCommGroupCode1 == dstrCommGroupCode2 && dstrFeeCode1 == dstrFeeCode2 &&
							  dstrBrokerCode1 == dstrBrokerCode2 && dstrShGroup1 == dstrShGroup2 && 
							  dstrFundFromCode1 == dstrFundFromCode2 && dstrClassFromCode1 == dstrClassFromCode2 &&
							  dstrBranchCode1 == dstrBranchCode2 && dstrSalesRepCode1 == dstrSalesRepCode2)					 
						 {
							
							 if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																		dstrEffectiveDate2, dstrStopDate2 ) )
							{
								DString strTemp;                 
								addIDITagValue( strTemp, IDI_CODE, dstrFeeCode1 +I_(" ") + dstrCommGroupCode1 + I_(" ") + dstrCommGroupCode2);         
								ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, strTemp);
								return(GETCURRENTHIGHESTSEVERITY());
							}
						 }
					}
				}
			}
		}
        dynamic_cast<FeeParamBase*>(iter.getObject() )->validateFeeScaleList( idDataGroup );

        ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
// sort by FeeCode and EffectiveDate
void  FeeParamBaseList::getStrKey1( DString &strKey, const BFData *data  )
{
   DString dstrFeeID, dstrFeeCode, dstrEffectiveDate, 
	   dstrFundCode, dstrClassCode, dstrSortDate, dstrCommGroup;

   DString dstrBroker, dstrFundFrom, dstrClassFrom, 
	   dstrBranchCode, dstrSalesRepCode, dstrShGroup, dstrDistributionChannel;   	

   dstrFeeCode = data->getElementValue( I_( "FeeCode" ) );
   dstrFeeCode.strip().stripLeading('0');
   dstrFeeCode.padLeft( 2, '0' );

   dstrEffectiveDate = data->getElementValue( I_( "EffectiveDate" ) );
   
   dstrBroker = data->getElementValue( I_( "BrokerCode" ) );
   dstrFundFrom = data->getElementValue( I_( "FundFromCode" ) );
   dstrClassFrom = data->getElementValue( I_( "ClassFromCode" ) );

   dstrBroker.strip().upperCase();
   dstrFundFrom.strip().upperCase();
   dstrClassFrom.strip().upperCase();

   DSTCommonFunctions::convertToSortableDateInDec ( dstrEffectiveDate, dstrSortDate );
   
   dstrFundCode = data->getElementValue( I_( "FundCode" ) );
   dstrClassCode = data->getElementValue( I_( "ClassCode" ) );
   dstrFundCode.strip().upperCase(); dstrClassCode.strip().upperCase();
   
   dstrCommGroup = data->getElementValue( I_( "CommGroup" ) );
   dstrCommGroup.strip();
   
   dstrBranchCode = data->getElementValue( I_( "BranchCode" ) );
   dstrBranchCode.strip();
   
   dstrSalesRepCode = data->getElementValue( I_( "SlsrepCode" ) );
   dstrSalesRepCode.strip();
   
   dstrShGroup = data->getElementValue( I_( "ShGroup" ) );
   dstrShGroup.strip();
   
   dstrDistributionChannel = data->getElementValue( I_( "DistributionChannel" ) );
   dstrDistributionChannel.strip();

   dstrFeeID = data->getElementValue( I_("FeeID") );
   dstrFeeID.stripAll();

   strKey = dstrFeeCode.strip().upperCase() + dstrSortDate + dstrFundCode + dstrClassCode + dstrCommGroup;
   strKey += dstrBroker + dstrFundFrom + dstrClassFrom + dstrBranchCode +dstrSalesRepCode + dstrShGroup;
   strKey += dstrDistributionChannel;
   strKey += dstrFeeID;
}
//************************************************************************************
bool FeeParamBaseList::canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

   bool retVal = canUpdateObject(strKey, idDataGroup);
   if(!retVal)
   {
      ADDCONDITIONFROMFILE( CND::ERR_DELETE_FEE_PARAMETER );
   }
   return retVal;
}

//************************************************************************************
bool FeeParamBaseList::canUpdateObject( const DString&  strKey,   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canUpdateObject" ) );
   bool retVal = false;

   FeeParamBase* pFeeParamBase = dynamic_cast<FeeParamBase*>(getObject(strKey, idDataGroup));
   if(pFeeParamBase)
   {
      retVal = pFeeParamBase->canUpdateObject(idDataGroup);
   }

   return retVal;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamBaseList.cpp-arc  $
// 
//    Rev 1.14   Feb 28 2012 06:11:14   wutipong
// IN2773982 - another revised
// 
//    Rev 1.13   Feb 23 2012 10:17:38   wutipong
// IN2773982 - revised.
// 
//    Rev 1.11   Oct 31 2011 10:18:42   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.10   Nov 14 2004 14:40:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   May 02 2003 14:52:58   linmay
// modified doValidateAll() and getStrKey()
// 
//    Rev 1.8   Mar 21 2003 18:09:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Mar 10 2003 14:44:18   linmay
// modified doValidateAll
// 
//    Rev 1.6   Feb 05 2003 13:51:56   YINGBAOL
// change to uppercase and change getStrKey
// 
//    Rev 1.5   Feb 05 2003 13:35:34   YINGBAOL
// change validateall include check ShGroup, Broker, FundFromCode and ClassFromCode.
// 
//    Rev 1.4   Jan 27 2003 15:21:44   linmay
// modified doValidateAll()
// 
//    Rev 1.3   Jan 22 2003 09:57:30   YINGBAOL
// change validateall
// 
//    Rev 1.2   Jan 15 2003 15:22:08   linmay
// added log comment
*/