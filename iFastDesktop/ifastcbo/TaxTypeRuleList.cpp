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
// ^FILE   : TaxTypeRuleList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 12/10/1999
//
// ^CLASS    : TaxTypeRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "taxtyperulelist.hpp"
#include "taxtyperule.hpp"
#include "redcodebytaxtypelist.hpp"
#include <ifastdataimpl\dse_dstc0087_req.hpp>
#include <ifastdataimpl\dse_dstc0087_vw.hpp>

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TAXTYPE_RULE;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "TaxTypeRuleList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TFSAProvCode;
   extern CLASS_IMPORT const BFTextFieldId TFSAAgeOfMajor;
}

//******************************************************************************

TaxTypeRuleList::TaxTypeRuleList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}

//******************************************************************************

TaxTypeRuleList::~TaxTypeRuleList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY TaxTypeRuleList::init( const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0087_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData( DSTC_REQUEST::TAXTYPE_RULE, queryData, ifds::DSTC0087_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());

}


//******************************************************************************
void TaxTypeRuleList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstTaxType = data->getElementValue( I_( "TaxType" ));
	  DString dstTaxTypeSchedule = data->getElementValue( I_( "TaxTypeSchedule" ));
      getStrKey ( strKey, dstTaxType, dstTaxTypeSchedule );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}


//******************************************************************************
void TaxTypeRuleList::getStrKey ( DString& strKey, const DString& dstTaxType, const DString& dstTaxTypeSchedule )
{
   strKey = dstTaxType;
   strKey.strip();   
   strKey += I_("_");
   strKey += dstTaxTypeSchedule;   
   strKey.strip().upperCase();
}

//******************************************************************************
SEVERITY TaxTypeRuleList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   TaxTypeRule *pTaxTypeRule = new TaxTypeRule( *this );
   pTaxTypeRule->init( data );

   // preload these values.  This TaxTypeRule object
   // may cause a lock in BPServer if these methods are 
   // loaded on-the-fly - CP20050916
   RedCodeByTaxTypeList* p1;
   pTaxTypeRule->getDepTypeList( p1, BF::HOST);
   pTaxTypeRule->getRedCodeList( p1, BF::HOST );
   pTaxTypeRule->doesTaxJurisdictionLimitationListExist( BF::HOST );


   pObjOut = pTaxTypeRule;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TaxTypeRuleList::createTaxTypesList (DString &strCodesList)
{
   strCodesList = NULL_STRING;
   TaxTypeRule *pTaxTypeRule = NULL;

   DString dstrTaxType;
   BFObjIter iterTaxType( *this, BF::HOST, true );
   iterTaxType.begin();

   while( !iterTaxType.end() )
   {
      iterTaxType.getObject()->getField( ifds::TaxType, dstrTaxType, BF::HOST );
      dstrTaxType.strip().upperCase();
      strCodesList += dstrTaxType ;
      strCodesList += I_(",");
      ++iterTaxType;
   }

   //delete the last ","
   if( !strCodesList.empty() )
      strCodesList.erase( strCodesList.length() - 1, 1 );
}

//******************************************************************************
bool TaxTypeRuleList::checkEligibleAge(const DString &taxType)
{
    bool checkAge = false;
    DString dstrTaxType(taxType);
    BFObjIter iterTaxType(*this, BF::HOST);

    dstrTaxType.upperCase().stripAll();

    while (!iterTaxType.end())
    {
        DString dstrIterTaxType;
        iterTaxType.getObject()->getField(ifds::TaxType, dstrIterTaxType, BF::HOST);
        
        if (dstrIterTaxType.stripAll().upperCase() == dstrTaxType)
        {
            TaxTypeRule *pTaxTypeRule = dynamic_cast<TaxTypeRule*>(iterTaxType.getObject());
            if (pTaxTypeRule)
                checkAge = pTaxTypeRule->getCheckEligibleAge(BF::HOST);;

            break;
        }

        ++iterTaxType;
    }

    return checkAge;
}

//******************************************************************************
bool TaxTypeRuleList::getTFSAEligibleAge(const DSTCWorkSession &workSession, const DString &srchTaxJuris, int &iElgbAge)
{
    bool isFound = false;
    DString dstrTFSAProvCode, dstrTFSAAgeOfMajor;

    workSession.getOption(ifds::TFSAProvCode, dstrTFSAProvCode, BF::HOST, false);
    workSession.getOption(ifds::TFSAAgeOfMajor, dstrTFSAAgeOfMajor, BF::HOST, false);

    while (!dstrTFSAProvCode.empty() && !dstrTFSAAgeOfMajor.empty())
    {
        DString::size_type pos = 0;
        DString dstrProv, dstrElgbAge;

        EXTRACT_VALUE(dstrTFSAProvCode, dstrProv, I_(","));
        CHOP_STRING(dstrTFSAProvCode, I_(","));

        EXTRACT_VALUE(dstrTFSAAgeOfMajor, dstrElgbAge, I_(","));
        CHOP_STRING(dstrTFSAAgeOfMajor, I_(","));

        if (dstrProv == srchTaxJuris)
        {
            isFound = true;
            iElgbAge = dstrElgbAge.asInteger();

            break;
        }
    }

    return isFound;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxTypeRuleList.cpp-arc  $
 * 
 *    Rev 1.22   15 Apr 2008 12:10:14   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.21   Sep 18 2005 08:47:00   purdyech
 * PTS604322 - TaxTypeRule objects are mgmt co level but were being lazy-loaded at the transaction level.  This caused a deadlock in the BPServer between the locks here and the locks in BFNotification.
 * 
 *    Rev 1.20   Dec 10 2004 14:55:00   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.19   Nov 23 2004 16:09:34   popescu
 * Turned versioning off, removed idDataGroup from TaxTypeRuleList::createTaxTypesList
 * 
 *    Rev 1.18   Nov 18 2004 13:28:32   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.17   Nov 14 2004 14:57:10   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Mar 21 2003 18:26:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Oct 09 2002 23:55:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 12:56:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:30:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Nov 2001 16:17:06   KOVACSRO
 * bug fixed
 * 
 *    Rev 1.11   11 May 2001 10:37:32   HSUCHIN
 * Sync up with SSB (1.9.1.0)
 * 
 *    Rev 1.10   03 May 2001 14:07:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Mar 30 2001 11:10:20   OLTEANCR
 * added function getTaxTypeSubstList
 * 
 *    Rev 1.8   09 Feb 2001 14:56:16   SMITHDAV
 * Do Async Requests...
 * 
 *    Rev 1.7   Jan 18 2001 16:09:58   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 17 2000 20:24:38   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.5   Dec 06 2000 14:50:28   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.4   Nov 02 2000 15:04:30   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.3   May 25 2000 15:35:28   WINNIE
 * add getsessionId
 * 
 *    Rev 1.2   May 18 2000 16:44:50   WINNIE
 * Implement TaxTypeRule and related validation

*/


