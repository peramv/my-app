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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFAccountList.cpp
// ^AUTHOR : Serban Popescu && Adrian Vasile
// ^DATE   : 02/16/99
//
// ^CLASS    : MFAccountList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mfaccountlist.hpp"
#include "Shareholder.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0004_req.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MFAccountList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MFACCOUNT;
}

namespace CND
{  // Conditions used
   extern const long ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER;

}



//******************************************************************************
MFAccountList::MFAccountList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
MFAccountList::~MFAccountList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY MFAccountList::initNew(const DString& shrNum, const BFDataGroupId& idDataGroup /*== BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccountList::init(const DString& shrNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   return init(NULL_STRING, NULL_STRING, shrNum);
}

//******************************************************************************
SEVERITY MFAccountList::init(const DString& EntityId, const DString& InputAcctNum, 
   const DString& InputShrNum, const DString& NumEntry /*= NULL_STRING*/,
   const DString& dstrTrack /*=I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   assert((EntityId != NULL_STRING && InputAcctNum == NULL_STRING && InputShrNum == NULL_STRING)
           || (EntityId == NULL_STRING && InputAcctNum != NULL_STRING && InputShrNum == NULL_STRING)
           || (EntityId == NULL_STRING && InputAcctNum == NULL_STRING && InputShrNum != NULL_STRING));

   BFData requestData(ifds::DSTC0004_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   requestData.setElementValue(ifds::EntityId, EntityId);
   requestData.setElementValue(ifds::InputAcctNum, InputAcctNum);
   requestData.setElementValue(ifds::InputShrNum, InputShrNum);
   requestData.setElementValue(ifds::Track, dstrTrack);
   requestData.setElementValue(ifds::Activity, dstrPageName);
   //call the back-end
   ReceiveData(DSTC_REQUEST::MFACCOUNT, requestData, ifds::DSTC0004_VW, DSTCRequestor(getSecurity()));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccountList::init( BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   return(populateList( InstData ));
}

//******************************************************************************
SEVERITY MFAccountList::populateList(BFData& InstData)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "populateList" ) );

   BFData* pViewData = new BFData(InstData);
   createObjectForEachRepeat( *pViewData );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccountList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   MFAccount *pMFAccount;

   getWorkSession().PopulateMFAccount(BF::HOST, data, pMFAccount);
   pObjOut = pMFAccount;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MFAccountList::setObjectFlags(const BFObjectKey& objKey, long& lStateFlags, long& lGroupFlags)
{
   lStateFlags = BFCBO::NO_BASE_DELETE;
   lGroupFlags = 0;
}

//******************************************************************************
SEVERITY MFAccountList::getAccountNumSubstList( DString & dstrAccountNumSubstList,
															  const BFDataGroupId& idDataGroup															  
															   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getAccountNumSubstList" ) );
   
	dstrAccountNumSubstList = I_( "" );

   MFAccount *pMFAccount = NULL;
	BFObjIter iter( *this, 
		             idDataGroup, 
						 true, 
						 BFObjIter::ITERTYPE::NON_DELETED );

	while( !iter.end() )
   {
		BFAbstractCBO *pMFAccount = dynamic_cast<BFAbstractCBO*>( iter.getObject() );
      if ( NULL != pMFAccount )
		{
			DString dstrAccountNum;			
			pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
			dstrAccountNumSubstList += dstrAccountNum + I_("=") + dstrAccountNum + I_(";");
		}

		++iter;
	}

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY MFAccountList::validateEffectivDateAgainstAllShereholder( DString & inEffectiveDate,
															  const BFDataGroupId& idDataGroup	)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateEffectivDateAgainstAllShereholder" ) );
   MFAccount *pMFAccount = NULL;
	BFObjIter iter( *this, 
		             idDataGroup, 
						 true, 
						 BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter.end() )
   {
		BFAbstractCBO *pMFAccount = dynamic_cast<BFAbstractCBO*>( iter.getObject() );
      if ( NULL != pMFAccount )
		{
         DString shrNum;
         pMFAccount->getField(ifds::ShrNum, shrNum,idDataGroup,false);
         shrNum.strip().stripLeading(I_('0') );
         if( shrNum != NULL_STRING )
         {
             Shareholder* pShareholder = NULL;
              if( getWorkSession().getShareholder( idDataGroup, shrNum, pShareholder ) <= WARNING )
              {
                 if( pShareholder )
                 {
                     DString effectiveDate,formdate;
                     if( pShareholder->isNew() )
                     {
                        pShareholder->getField(ifds::EffectiveDate,effectiveDate,idDataGroup,false);
                        pShareholder->getField(ifds::EffectiveDate,formdate,idDataGroup,true);
                     }
                     else
                     {
                        pShareholder->getField(ifds::FirstEffective,effectiveDate,idDataGroup,false);
                        pShareholder->getField(ifds::FirstEffective,formdate,idDataGroup,true);
                     }  
                     if( DSTCommonFunctions::CompareDates( inEffectiveDate, effectiveDate ) == DSTCommonFunctions::FIRST_EARLIER) 
                     {
                        DString dstrDate;
                        addIDITagValue( dstrDate, I_("DATE"), formdate );
                        ADDCONDITIONFROMFILEIDI( CND::ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER, dstrDate.c_str() );
                     }                 
                 }
              }
         }
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccountList.cpp-arc  $
 * 
 *    Rev 1.18   Apr 08 2005 11:41:42   yingbaol
 * incident 284670, effectivedate issue in NASU flow
 * 
 *    Rev 1.17   Mar 11 2005 15:27:52   yingbaol
 * PET1171,FN01, EU Saving: compare first effective date at share holder level.
 * 
 *    Rev 1.16   Mar 09 2005 16:05:10   yingbaol
 * PET 1171,FN01: EU saving entity update
 * 
 *    Rev 1.15   Nov 14 2004 14:50:06   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Sep 21 2004 11:07:36   YINGBAOL
 * PET1117:FN05  Iterate list take data group id
 * 
 *    Rev 1.13   Sep 20 2004 11:08:56   YINGBAOL
 * PET1117:FN5 Fee Model is part of Nasu flow.
 * 
 *    Rev 1.12   Aug 11 2004 18:37:44   FENGYONG
 * Temp check in  PET 117 FN5  for other enhancement compiling
 * 
 *    Rev 1.11   May 22 2003 14:12:58   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.10   Mar 21 2003 18:18:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:54:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:56:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:29:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:06:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 18 2001 16:05:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:24:04   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 13:56:36   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   26 Oct 2000 17:28:10   SMITHDAV
 * Now uses new data broker.
 * 
 *    Rev 1.1   Mar 30 2000 09:48:08   BUZILA
 * changes due to introduction of objKey parameter in BFBase:: ::setObjectFlags
 * 
 *    Rev 1.0   Feb 15 2000 11:00:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.13   Jan 05 2000 20:11:00   BUZILA
 * adding list flag
 * 
 *    Rev 1.12   Dec 12 1999 16:25:48   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/