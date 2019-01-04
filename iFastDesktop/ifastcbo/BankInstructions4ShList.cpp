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
// ^FILE   : BankInstructions4ShList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : BankInstructions4ShList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include "shareholder.hpp"
#include "BankInstructions4ShList.hpp"
#include "mfaccount.hpp"
#include "mfaccountlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_ ("BankInstructions4ShList");
   const I_CHAR *  YES = I_ ("Y");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace BANKENTITY
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace ifds
{ 
    extern CLASS_IMPORT const BFTextFieldId DTAExist;
	 extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
    extern CLASS_IMPORT const  BFNumericFieldId rxAcctNum;
    extern CLASS_IMPORT const  BFTextFieldId rxBankingEntity;
}

namespace AcctUseCode
{
    extern const I_CHAR * const DIRECT_TRADING;
}

namespace BANKINGLEVEL
{
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_LEVEL               = I_("01");
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_LEVEL                   = I_("02");;
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_AND_ACCOUNT_LEVEL   = I_("03");
}
namespace CND
{
	extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,	   State Flags,   Group Flags
   { ifds::ShrNum,            BFCBO::NONE,            0 }, 
   { ifds::rxAcctNum,         BFCBO::NONE,            0 }, 
   { ifds::rxBankingEntity,   BFCBO::NONE,            0 },
};

static const int NUM_FIELDS = sizeof ( classFieldInfo ) / sizeof ( BFCBO::CLASS_FIELD_INFO );

namespace CND
{  // Conditions used
   extern const long ERR_AT_LEAST_ONE_DTABANKING_MUST_BE_SETUP;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
}

//******************************************************************************
BankInstructions4ShList::BankInstructions4ShList (BFAbstractCBO &parent)
: BankInstructionsList (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS,
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/* (const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList ();
   //the parent of this list should always be a Shareholder object
   assert (dynamic_cast<Shareholder*> (&parent));
}

//******************************************************************************
BankInstructions4ShList::~BankInstructions4ShList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY BankInstructions4ShList::initNew (const DString& dstrShrNum, 
   const DString& bankType,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   
   setFieldNoValidate (ifds::ShrNum, dstrShrNum, idDataGroup, false, true, true);
   BankInstructionsList::initNew (bankType, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions4ShList::init (const DString& dstrNum, 
   const DString &bankType,
   const DString &dstrTrack /*= I_ ("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);  
   
   if( BANKTYPE::SHAREHOLDER ==  bankType)
   {
     requestData.setElementValue (ifds::BankingEntity, BANKENTITY::SHAREHOLDER);
     requestData.setElementValue (ifds::ShrNum, dstrNum);
     requestData.setElementValue (ifds::AccountNum, I_("0"));//check this with Abhisek to see if they need the account number
     setFieldNoValidate (ifds::ShrNum, dstrNum, BF::HOST, false, true, true);
    
   }
   else if( BANKTYPE::ACCOUNT  ==  bankType)
   {
     requestData.setElementValue (ifds::BankingEntity, BANKENTITY::ACCOUNT);
     requestData.setElementValue (ifds::ShrNum, I_("0"));
     requestData.setElementValue (ifds::AccountNum, dstrNum);
     setFieldNoValidate (ifds::AccountNum, dstrNum, BF::HOST, false, true, true);     
   }
   BFData queryData(ifds::DSTC0052_VW);
   BankInstructionsList::init (requestData, bankType, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY BankInstructions4ShList::doValidateAll(const BFDataGroupId& idDataGroup, 
   long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ));

   BankInstructionsList::doValidateAll(idDataGroup, lValidateGroup); 
   
   bool bHaveDTABanking = false;
   DString dstrShrNum, 
      dstrAcctUseCode;
   DString dstrDTAExist(NULL_STRING);

   getField(ifds::ShrNum, dstrShrNum, idDataGroup, false);

   Shareholder* pShareholder = NULL;
   BFAbstractCBO *pBFBase;
   
   if (dstrShrNum != NULL_STRING)
   {
      if (getWorkSession().getShareholder (idDataGroup, dstrShrNum, 
         pShareholder) <= WARNING)
      {
         pShareholder->getField (ifds::DTAExist, dstrDTAExist, idDataGroup, false);
      }
   }
   if (dstrDTAExist == YES)
   {
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

      while (!iter.end())
		{
		   pBFBase = iter.getObject();
			if (!iter.isDummy() && pBFBase)
         {
            pBFBase->getField(ifds::AcctUseCode, dstrAcctUseCode, idDataGroup);
            if (dstrAcctUseCode == AcctUseCode::DIRECT_TRADING)
            {
               bHaveDTABanking = true;
               break;
            }
         }
         ++iter;
      }
      if (!bHaveDTABanking)
		{
		   ADDCONDITIONFROMFILE (CND::ERR_AT_LEAST_ONE_DTABANKING_MUST_BE_SETUP);
		}
   }

   if(pShareholder && !isNew()&& isUpdatedForDataGroup (idDataGroup))
   {
     MFAccountList *pMFAccountList;
	 MFAccount *pMFAccount = NULL;
	 if (pShareholder->getMFAccountList (pMFAccountList, idDataGroup)<=WARNING && pMFAccountList)
	 {
		BFObjIter iterMFAcct (*pMFAccountList, idDataGroup);
		while (!iterMFAcct.end ())
		{
			pMFAccount = dynamic_cast<MFAccount*> (iterMFAcct.getObject ());
			if (pMFAccount)
			{
				DString dstrShareholderNum,dstrCurrShrNumber;
				pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
				dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
				if(!dstrShareholderNum.empty()&& dstrShrNum != NULL_STRING
				   && dstrShareholderNum ==  dstrShrNum )
				{
				  {	
					bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
					pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
					if(bDisplyWarnSICAV)
						ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
					if(bDisplyWarnOEIC)
						ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
				  } 
				break;
				}
			}
			++iterMFAcct;
		}
	}
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4ShList.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:28:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 10 2003 14:54:58   popescu
// Initial revision.
// 
//    Rev 1.3   Oct 29 2003 17:40:56   FENGYONG
// Add field DTAExist
// 
//    Rev 1.2   Oct 28 2003 10:36:56   FENGYONG
// Add condition for direct trading banking validation
// 
//    Rev 1.1   Oct 23 2003 17:51:56   FENGYONG
// Override doValidateAll 
// 
//    Rev 1.0   Oct 19 2003 19:08:32   popescu
// Initial revision.
 */