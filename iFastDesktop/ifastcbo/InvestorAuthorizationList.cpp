//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorizationList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2009
//
// ^CLASS    : InvestorAuthorizationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0395_vw.hpp>
#include <ifastdataimpl\dse_dstc0395_req.hpp>
#include <ifastdataimpl\dse_dstc0395_vwrepeat_record.hpp>

#include "InvestorAuthorization.hpp"
#include "InvestorAuthorizationList.hpp"
#include "mfaccount.hpp"
#include "whereusedlist.hpp"

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest INVESTOR_AUTHORIZATION_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "InvestorAuthorizationList" );
   const I_CHAR * const ACCOUNT                 = I_( "02" );
   const I_CHAR * const ACCOUNT_OWNER           = I_( "01" );
   const I_CHAR * const NON_REGISTERED_TAX_TYPE = I_( "0" );
   const I_CHAR * const CLIENT_ACCOUNT_TYPE     = I_( "1" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

   extern CLASS_IMPORT const BFTextFieldId WhereUse;
   extern CLASS_IMPORT const BFTextFieldId WhereUseCode;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
}

namespace CND
{
   extern const long ERR_SHARE_HOLDER_HOLD_MULTIPLE_ACCOUNTS;
   extern const long ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,          Group Flags 
   { ifds::AccountNum               , BFCBO::NONE,                0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
InvestorAuthorizationList::InvestorAuthorizationList( BFAbstractCBO &parent )
: MFCanBFCbo(parent),
_accountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
InvestorAuthorizationList::~InvestorAuthorizationList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY InvestorAuthorizationList::init( const DString& accountNum,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init( DString&, BFDataGroupId& )"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0395_REQ);

   _accountNum = accountNum;
   setFieldNoValidate (ifds::AccountNum, _accountNum , BF::HOST, false);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   requestData.setElementValue (ifds::AccountNum, accountNum);
   requestData.setElementValue (ifds::DuplicateCheck, I_("N"));

   ReceiveData( DSTC_REQUEST::INVESTOR_AUTHORIZATION_INQUIRY,
                requestData, 
                ifds::DSTC0395_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestorAuthorizationList::doCreateNewObject (BFCBO *& pBase, 
                                                       DString &strKey, 
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase =  new InvestorAuthorization( *this );

   ((InvestorAuthorization* )pBase)->initNew( _accountNum, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestorAuthorizationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new InvestorAuthorization( *this );
   ((InvestorAuthorization*) pObjOut )->init( _accountNum, data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestorAuthorizationList::doValidateAll( const BFDataGroupId& idDataGroup, 
                                                   long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   MFAccount *pMFAccount = NULL;
   
   pMFAccount = dynamic_cast<MFAccount*>(getParent());
   
   if (pMFAccount != NULL )
   {
      DString dstrTaxType, dstrAcctDesignation;
      pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup,false);
      pMFAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup,false);

      if ( dstrTaxType != NON_REGISTERED_TAX_TYPE || dstrAcctDesignation != CLIENT_ACCOUNT_TYPE )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY );
      }
   }

   BFObjIter iterList (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
   
   // look for record which is 'blank' due to reset button and remove it
   // otherwise it cause error 183 from backend side
   while (!iterList.end ())
   {
      DString strKey;
      InvestorAuthorization* pObj = dynamic_cast<InvestorAuthorization*>(iterList.getObject());
      if ( pObj && pObj->isResetRecord(idDataGroup) )
      {
         strKey = iterList.getStringKey();
         if( !strKey.empty() )
         {
            deleteObject(strKey, idDataGroup, true);
         }
      }
      ++iterList;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestorAuthorizationList.cpp-arc  $
// 
//    Rev 1.7   Oct 19 2009 04:07:42   dchatcha
// IN# 1864779 - Rel95_PET156681_dlr_rep code, Fix issue found when reset button is pressed.
// 
//    Rev 1.6   23 Jul 2009 12:58:44   popescu
// PET156681 FN14 H36 Investor Authorization, some more fixes
// 
//    Rev 1.5   Jul 23 2009 08:40:14   dchatcha
// PET156681 FN14 H36 Investor Authorization, fix on update existing IA record.
// 
//    Rev 1.4   22 Jul 2009 18:07:30   popescu
// PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
// 
//    Rev 1.3   Jul 22 2009 08:39:44   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code review. 
// 
//    Rev 1.2   Jul 16 2009 19:35:32   dchatcha
// PET156681 FN14 H36 Investor Authorization, Integration issues.
// 
//    Rev 1.1   Jul 09 2009 15:21:28   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.0   29 Jun 2009 16:26:04   popescu
// Initial revision.
//
*/
