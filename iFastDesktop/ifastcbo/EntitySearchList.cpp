//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntitySearchList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/11/99
//
// ^CLASS    : EntitySearchList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This list handles the server response after a search. Keeps a list of 
//                      entities.
//
//******************************************************************************

#include "stdafx.h"
#include "entitysearchlist.hpp"
#include "errmsgruleslist.hpp"
#include "entity.hpp"

#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEARCH;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS; 
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_INVALID_BUSINESSNO;
	extern const long WARN_INVALID_BUSINESSNO;          
	extern const long ERR_ENTITY_LASTNAME_CANNOT_BE_BLANK;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_ ("EntitySearchList");

   const I_CHAR * const PREPARESEARCH = I_ ("prepareSearch");
   const I_CHAR * const MORERECORDSEXIST = I_ ("moreRecordsExist");
   const I_CHAR * const DOVALIDATEFIELD = I_ ("doValidateField");
   const I_CHAR * const SEARCH = I_ ("search");
   const I_CHAR * const CLEARPREVIOUSSEARCH = I_ ("clearPreviousSearch");
   const I_CHAR * const INIT = I_ ("init");

   // View literals
   const I_CHAR * const SIN_ALLOWED_CHARS = I_ ("0123456789-");
   const I_CHAR * const TEL_ALLOWED_CHARS = I_ ("0123456789()- ");

   const I_CHAR * const SORTED_BY_LAST_NAME = I_ ("LN");
   const I_CHAR * const SORTED_BY_BIRTH_LAST_NAME = I_ ("BN");
   const I_CHAR * const SORTED_BY_SLSREP = I_ ("SR");
   const I_CHAR * const ACCOUNT_HOLDERS_ONLY = I_ ("01");
}

namespace IDS
{
   extern const I_CHAR * const DRIVERS_LICENSE;
   extern const I_CHAR * const PASSPORT;
   extern const I_CHAR * const BIRTH_CERTIFICATE;
   extern const I_CHAR * const CREDIT_CARD;
   extern const I_CHAR * const NATIONAL_ID;
   extern const I_CHAR * const SIN;
   extern const I_CHAR * const BIC_CODE;
   extern const I_CHAR * const ADDITIONAL_ACCT_NUMBER;
   extern const I_CHAR * const CIF;
   extern const I_CHAR * const ACCESS_ID;
   extern const I_CHAR * const CLEARING_PLATFORM;
   extern const I_CHAR * const OTHER;
   extern const I_CHAR * const CPFB_ACCNUM;
   extern const I_CHAR * const ACCOUNT_MANAGER_UNIQUE_ID;
}

namespace AllEntitySearchType
{
   const I_CHAR * const NAME = I_ ("NAME");
   const I_CHAR * const SIN = I_ ("SIN");
   const I_CHAR * const IDTYPE = I_ ("IDTYPE");
   const I_CHAR * const WHEREUSE = I_ ("WHEREUSE");
};
namespace ENTITYSEARCHTYPE
{
   extern IFASTCBO_LINKAGE const int NO_SEARCH = 0;
   extern IFASTCBO_LINKAGE const int USING_ACCOUNT_NUM = 1;
   extern IFASTCBO_LINKAGE const int USING_SIN = 2;
   extern IFASTCBO_LINKAGE const int USING_NAME = 3;
   extern IFASTCBO_LINKAGE const int USING_SHAREHOLDER_NUM = 4;
   extern IFASTCBO_LINKAGE const int USING_DRIVER_LICENSE = 5;
   extern IFASTCBO_LINKAGE const int USING_PASSPORT = 6;
   extern IFASTCBO_LINKAGE const int USING_BIRTH_CERTIFICATE = 7;
   extern IFASTCBO_LINKAGE const int USING_CREDIT_CARD = 8;
   extern IFASTCBO_LINKAGE const int USING_NATIONAL_ID = 9;
   extern IFASTCBO_LINKAGE const int USING_SOCIAL_SEC_INS_CARD = 10;
   extern IFASTCBO_LINKAGE const int USING_OTHER_ID = 11;
   extern IFASTCBO_LINKAGE const int USING_ALT_ACCT_BRK_CODE = 12;
   extern IFASTCBO_LINKAGE const int USING_BRK_CODE = 13;
   extern IFASTCBO_LINKAGE const int USING_TELEPHONE_NUM = 14;
   extern IFASTCBO_LINKAGE const int USING_BIRTH_NAME = 15;
   extern IFASTCBO_LINKAGE const int USING_INTERMEDIARY = 16;
   extern IFASTCBO_LINKAGE const int USING_OTHER_REFERENCE = 17;
   extern IFASTCBO_LINKAGE const int USING_BUSINESSNO = 18;
   extern IFASTCBO_LINKAGE const int USING_CIF = 19;
   extern IFASTCBO_LINKAGE const int USING_ACCESS_ID = 20;
   extern IFASTCBO_LINKAGE const int USING_CLEARING_PLATFORM_ID = 21; //MT535/MT536
   extern IFASTCBO_LINKAGE const int USING_HOUSEHOLD = 22;
   extern IFASTCBO_LINKAGE const int USING_REGISTRATION_AGENT = 23;
   extern IFASTCBO_LINKAGE const int USING_CPFB_ACCNUM = 24;
   extern IFASTCBO_LINKAGE const int USING_ACCOUNT_MANAGER_UNIQUE_ID = 25;
};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::SrchAccountNum, BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchSIN,        BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchShrNum,     BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchIdValue,    BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchAltAcct,    BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchBroker,     BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchPhoneNum,   BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchPhoneArea,  BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchIntCode,    BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchIntAcct,    BFCBO::READ_ONLY, 0 }, 
   { ifds::SrchBusinessNo, BFCBO::READ_ONLY, 0 }, 
	{ ifds::SrchBirthLName, BFCBO::READ_ONLY, 0 },
	{ ifds::SrchLastName, BFCBO::READ_ONLY, 0 },
};

static const int NUM_FIELDS = sizeof (classFieldInfo) 
                              / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
EntitySearchList::EntitySearchList (BFAbstractCBO &parent) 
: MFCanBFCbo (parent), 
_requestData (NULL), 
_searchType (ENTITYSEARCHTYPE::NO_SEARCH), 
_usingBrokerInfo (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/);
   setObjectAsList();
}

//******************************************************************************
EntitySearchList::~EntitySearchList (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (_requestData)
   {
      delete _requestData;
      _requestData = NULL;
   }
}

//******************************************************************************
SEVERITY EntitySearchList::init (int searchType, 
                                 DString& field1,
                                 DString& field2,
                                 bool searchForAllEntities, 
                                 const DString& getExactSearch,
                                 const DString& getAllEntity,
                                 DString& field3,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName,
                                 const DString& dstrOverrideRepeats,
                                 const DString& dstrNextOrPrevious, 
                                 const DString& getALLrecords)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, INIT);

   _field1 = field1;
   _field2 = field2;
   _field3 = field3;

   _searchType = searchType;
   _searchForAllEntities = searchForAllEntities;
   _getALLrecords = getALLrecords;

   if (_requestData == NULL)
   {
      _requestData =  new BFData(ifds::DSTC0003_REQ);
   }
   if (_requestData != NULL)
   {
      DString mgmtCoIdOut;
      _requestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      _requestData->setElementValue (ifds::Track, dstrTrack);
      _requestData->setElementValue (ifds::Activity, dstrPageName);
      _requestData->setElementValue (ifds::OverrideRepeats, dstrOverrideRepeats);
      _requestData->setElementValue (ifds::NextOrPrevious, dstrNextOrPrevious);
      _requestData->setElementValue (ifds::AllEntitys, getAllEntity);
      _requestData->setElementValue (ifds::ExactMatch, getExactSearch);
      if(_field3 != I_("") && _field3 != I_("N"))
         _requestData->setElementValue (ifds::SrchWhereUse, _field3);
   }
   return search();
}

//********************************************************************************
void EntitySearchList::prepareSearch()
{
   DString dstrMarket = DSTCommonFunctions::getMarket();
   TRACE_METHOD (CLASSNAME, PREPARESEARCH);
   if (_requestData == NULL)
   {
      _requestData =  new BFData (ifds::DSTC0003_REQ);
   }
   if (_requestData != NULL)
   {
      _requestData->setElementValue (ifds::SortBy, SORTED_BY_LAST_NAME);

      if (Entity::bUsedByEntityAlone)
      {
         _requestData->setElementValue (ifds::AllEntitys, I_("Y"));
         _requestData->setElementValue (ifds::AllAccounts, I_ ("N"));
  
      }
      else 
      {
         _requestData->setElementValue (ifds::AllAccounts, I_ ("Y"));      
         if (!_searchForAllEntities)
            _requestData->setElementValue (ifds::SrchEntType, ACCOUNT_HOLDERS_ONLY);
      }
      switch (_searchType)
      {
         case ENTITYSEARCHTYPE::USING_ACCOUNT_NUM:
            {
               validateField (ifds::SrchAccountNum, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchAccountNum, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_SIN:
            {
               validateField (ifds::SrchSIN, _field1, BF::HOST);
               //for SIN strip the dashes
               _field1.stripAll ('-');
               _requestData->setElementValue (ifds::SrchSIN, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_NAME :
            {
               _requestData->setElementValue (ifds::SrchFirstName, _field1);
					validateField (ifds::SrchLastName, _field2, BF::HOST);
               _requestData->setElementValue (ifds::SrchLastName,  _field2);
            }
            break;
         case ENTITYSEARCHTYPE::USING_SHAREHOLDER_NUM:
            {
               validateField (ifds::SrchShrNum, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchShrNum, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_DRIVER_LICENSE:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::DRIVERS_LICENSE);
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
            }
            break;
         case ENTITYSEARCHTYPE::USING_PASSPORT:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::PASSPORT);
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
               break;
            }
         case ENTITYSEARCHTYPE::USING_BIRTH_CERTIFICATE:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::BIRTH_CERTIFICATE); 
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
               break;
            }
         case ENTITYSEARCHTYPE::USING_CREDIT_CARD:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::CREDIT_CARD); 
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
               break;
            }
         case ENTITYSEARCHTYPE::USING_NATIONAL_ID:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::NATIONAL_ID);
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
               break;
            }
         case ENTITYSEARCHTYPE::USING_SOCIAL_SEC_INS_CARD:
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::SIN); 
               _requestData->setElementValue (ifds::SrchIdValue, _field1); 
               break;
            }
         case ENTITYSEARCHTYPE::USING_OTHER_ID :
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::OTHER);
               _requestData->setElementValue (ifds::SrchIdValue, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_CIF :
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::CIF);
               _requestData->setElementValue (ifds::SrchIdValue, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_ACCESS_ID :
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::ACCESS_ID);
               _requestData->setElementValue (ifds::SrchIdValue, _field1);
               break;
            }
         //MT535/MT536
         case ENTITYSEARCHTYPE::USING_CLEARING_PLATFORM_ID :
            {
               validateField (ifds::SrchIdValue, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchIdType, IDS::CLEARING_PLATFORM);
               _requestData->setElementValue (ifds::SrchIdValue, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_HOUSEHOLD :
            {
               validateField (ifds::SrchFamily, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchFamily, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_ALT_ACCT_BRK_CODE:
            {
               _requestData->setElementValue (ifds::SrchAltAcct, _field1);
               _requestData->setElementValue (ifds::SrchBroker, _field2);
               break;
            }
         case ENTITYSEARCHTYPE::USING_BRK_CODE:
            {
               validateField (ifds::SrchBroker, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchBroker, _field1);
               _requestData->setElementValue (ifds::SrchBranch, _field2);
               _requestData->setElementValue ( ifds::SrchSlsrep, _field3);
               break;
            }
         case ENTITYSEARCHTYPE::USING_TELEPHONE_NUM :
            {
               validateField (ifds::SrchPhoneNum, _field1, BF::HOST);
               _requestData->setElementValue (ifds::SrchPhoneNum, _field1);
               validateField (ifds::SrchPhoneArea, _field2, BF::HOST);
               _requestData->setElementValue (ifds::SrchPhoneArea, _field2);
               break;
            }
         case ENTITYSEARCHTYPE::USING_BIRTH_NAME :
            //there is no need to validate the names
            {
               _requestData->setElementValue (ifds::SortBy, SORTED_BY_BIRTH_LAST_NAME);
               _requestData->setElementValue (ifds::SrchBirthFName, _field1);
					validateField (ifds::SrchBirthLName, _field2, BF::HOST);
               _requestData->setElementValue (ifds::SrchBirthLName, _field2);
               break;
            }
         case ENTITYSEARCHTYPE::USING_INTERMEDIARY:
            {
               validateField (ifds::SrchIntCode, _field1, BF::HOST);
               validateField (ifds::SrchIntAcct, _field2, BF::HOST);
               _requestData->setElementValue (ifds::SrchIntCode, _field1);
               _requestData->setElementValue (ifds:: SrchIntAcct, _field2);
               break;
            }
         case ENTITYSEARCHTYPE::USING_BUSINESSNO:
            {
               validateField (ifds::SrchBusinessNo, _field1, BF::HOST);
               _field1.stripAll('-').stripAll(' ').length();
				   _requestData->setElementValue (ifds::SrchBusinessNo, _field1);
               break;
            }
         case ENTITYSEARCHTYPE::USING_OTHER_REFERENCE:
            {
               _requestData->setElementValue (ifds::SrchXrefNum, _field1);
               break;
            }
		 case ENTITYSEARCHTYPE::USING_REGISTRATION_AGENT:
			{
		    	validateField (ifds::SrchIdValue, _field2, BF::HOST);
				_requestData->setElementValue (ifds::SrchAcctRegKey, _field1); 
				_requestData->setElementValue (ifds::SrchRefCode,    _field2);
				_requestData->setElementValue (ifds::SrchWhereUse,   _field3);

			   break;
			}
		 case ENTITYSEARCHTYPE::USING_CPFB_ACCNUM:
			{
		    	validateField (ifds::SrchIdValue, _field1, BF::HOST);
				_requestData->setElementValue (ifds::SrchIdType, IDS::CPFB_ACCNUM);
				_requestData->setElementValue (ifds::SrchIdValue, _field1); 
			   break;
			}
		 case ENTITYSEARCHTYPE::USING_ACCOUNT_MANAGER_UNIQUE_ID:
			{
				validateField (ifds::SrchIdValue, _field1, BF::HOST);
				_requestData->setElementValue (ifds::SrchIdType, IDS::ACCOUNT_MANAGER_UNIQUE_ID);
				_requestData->setElementValue (ifds::SrchIdValue, _field1); 
			   break;
			}
         case ENTITYSEARCHTYPE::NO_SEARCH:
            break;
         default:
            assert (0);
      }
      if (_usingBrokerInfo)
      {
         _usingBrokerInfo = false;
         _requestData->setElementValue (ifds::SortBy, SORTED_BY_SLSREP);
      }
   }
}

//******************************************************************************
SEVERITY EntitySearchList::search()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, SEARCH);   
   try
   {
      prepareSearch();

      if (_getALLrecords!=I_("Y"))
      {
         // BUZILAMI for Ident Account we want to have DATA_NOT_FOUND as an error (4th param of DSTCRequestor::DSTCRequestor(...) made true
         ReceiveData(DSTC_REQUEST::SEARCH,*_requestData, ifds::DSTC0003_VW, DSTCRequestor (getSecurity(), false, true));
      }
      else 
      {
         ReceiveData(DSTC_REQUEST::SEARCH,*_requestData, ifds::DSTC0003_VW, DSTCRequestor (getSecurity(), true, true));
      }
   }
   catch (ConditionException &ce)
   {
      throw ce;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntitySearchList::doValidateField ( const BFFieldId &idField, 
                                             const DString &strValue, 
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, DOVALIDATEFIELD);

   DString tmp (strValue);
   if (idField == ifds::SrchAccountNum)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
   // implemented as a separated entry since you may need different condition
   else if (idField == ifds::SrchSIN)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
      else
      {
         if (!containOnlyAllowedChars (SIN_ALLOWED_CHARS, strValue))
         {
            throw EXCEPTIONFROMFILE (CND::ERR_INVALID_CHAR);
         }
      }
   }
   else if (idField == ifds::SrchPhoneNum)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
      else
      {
         if (!containOnlyAllowedChars (TEL_ALLOWED_CHARS, strValue))
         {
            throw EXCEPTIONFROMFILE (CND::ERR_INVALID_CHAR);
         }
      }
   }
   else if (idField == ifds::SrchPhoneArea)
   {
      /*if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
      else
      {
         if (!containOnlyAllowedChars (TEL_ALLOWED_CHARS, strValue))
         {
            throw EXCEPTIONFROMFILE (CND::ERR_INVALID_CHAR);
         }
      }*/
   }
   else if (idField == ifds::SrchShrNum)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
   else if (idField == ifds::SrchIdValue)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
   else if (idField == ifds::SrchAltAcct)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
   else if (idField == ifds::SrchBroker)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_BROKER_EMPTY);
      }
   }
   else if (idField == ifds::SrchIntCode)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
   else if (idField == ifds::SrchIntAcct)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }
	else if (idField == ifds::SrchLastName)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTITY_LASTNAME_CANNOT_BE_BLANK);
      }
	}
	else if (idField == ifds::SrchBirthLName)
   {
      if (isStringEmptyOrJustContainSpace (strValue))
      {
         throw EXCEPTIONFROMFILE (CND::ERR_ENTITY_LASTNAME_CANNOT_BE_BLANK);
      }
	}
   else if (idField == ifds::SrchBusinessNo)
   {
		DString dstrErrValue;
	   ErrMsgRulesList* pErrMsgRulesList;
	   if  (getMgmtCo().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
		     NULL != pErrMsgRulesList)
		{
			pErrMsgRulesList->getEWIValue(I_("370"), idDataGroup, dstrErrValue);
			dstrErrValue.stripAll();
		}

		// Trigger validation only if the environment was setup for business no usage,
		// i.e. error message 370 has severity "E" or "W"
		if  (dstrErrValue.upperCase() == I_ ("E") || dstrErrValue.upperCase() == I_ ("W"))
		{		
			DString tmp = strValue;
			if (isStringEmptyOrJustContainSpace (strValue))
			{
				throw EXCEPTIONFROMFILE (CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
			}
			else
			{
				if (tmp.stripAll('-').stripAll(' ').length() != 15 ||
				 !containOnlyAllowedChars (SIN_ALLOWED_CHARS, tmp.left(9)) ||
				 !containOnlyAllowedChars (SIN_ALLOWED_CHARS, tmp.right(4))  )
				{
					if  (dstrErrValue.upperCase() == I_ ("E"))
						throw EXCEPTIONFROMFILE (CND::ERR_INVALID_BUSINESSNO);
					if  (dstrErrValue.upperCase() == I_ ("W"))
						throw EXCEPTIONFROMFILE (CND::WARN_INVALID_BUSINESSNO);
				}
			}
		}
   }
   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
bool EntitySearchList::isStringEmptyOrJustContainSpace (const DString& str)
{
   DString tmp (str);
   return(tmp == NULL_STRING || tmp.strip() == NULL_STRING);
}

//******************************************************************************
bool EntitySearchList::containOnlyAllowedChars (const DString& AllowedChars, const DString& str)
{
   bool rte = true;

   for (DString::size_type i = 0; i < str.length(); i++)
      if (AllowedChars.find (str[ i ]) == -1)
      {
         rte = false;
         break;
      }
   return(rte);
}

//******************************************************************************
void EntitySearchList::setBrokerInfo (const DString &BrokerCode, 
                                      const DString &BranchCode, 
                                      const DString &Slsrep)
{
   _usingBrokerInfo = true;
   if (_requestData == NULL)
      _requestData =  new BFData(ifds::DSTC0003_REQ);
   if (_requestData != NULL)
   {
      _requestData->setElementValue (ifds::SrchBroker, BrokerCode);
      _requestData->setElementValue (ifds::SrchBranch, BranchCode);
      _requestData->setElementValue (ifds::SrchSlsrep, Slsrep);
   }
}

//**************************************************************************************
// support search by 1. firstname/last name
//                   2. sin
//                   3. Entity ID Type   
//                   4. Where Used : 01--Fund Broker; 03---Client
//                   5. All entity Flag will be YES
//   
SEVERITY EntitySearchList::init ( const DString &searchBy, 
                                  const DString &firstName,
                                  const DString &lastName,
                                  const DString &sin, 
                                  const DString &idType,
                                  const DString &idValue, 
                                  const DString &whereUse, 
                                  const DString &fundCode /*= NULL_STRING*/,
                                  const DString &dstrTrack /*= I_("N")*/,
                                  const DString &dstrPageName /*= NULL_STRING*/)
{
 MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init by sin, firstname, lastname,idType, idvalue..."));

   DString dstrMarket = DSTCommonFunctions::getMarket();
   if (_requestData == NULL)
   {
      _requestData =  new BFData(ifds::DSTC0003_REQ);
   }
   if (_requestData != NULL)
   {
      _requestData->setElementValue (ifds::SortBy, SORTED_BY_LAST_NAME);
      _requestData->setElementValue (ifds::AllEntitys, I_("Y"));
      DString mgmtCoIdOut;
      _requestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      _requestData->setElementValue (ifds::Track, dstrTrack);
      _requestData->setElementValue (ifds::Activity, dstrPageName);
      //     _requestData->setElementValue (ifds::OverrideRepeats, dstrOverrideRepeats);
      //checked with Isabella, NextOrPrevious should be always N 
      // ExactMatch does matter,view does not read it
      //
       _requestData->setElementValue (ifds::NextOrPrevious, I_("N"));
      _requestData->setElementValue (ifds::ExactMatch, I_("N"));
      _requestData->setElementValue (ifds::AllAccounts, I_("N"));
      if (searchBy == AllEntitySearchType::NAME)
      {
         _requestData->setElementValue (ifds::SrchFirstName, firstName);
			validateField (ifds::SrchLastName, lastName, BF::HOST);
         _requestData->setElementValue (ifds::SrchLastName,  lastName);					
      }
      else if (searchBy == AllEntitySearchType::SIN)
      {
         validateField (ifds::SrchSIN, sin, BF::HOST);
         //for SIN strip the dashes
         DString sin1(sin);
         sin1.stripAll ('-');
         _requestData->setElementValue (ifds::SrchSIN, sin1);
      }
      else if (searchBy == AllEntitySearchType::IDTYPE)
      {  
         validateField (ifds::SrchIdValue, idValue, BF::HOST);
         _requestData->setElementValue(ifds::SrchIdType, idType); 
         _requestData->setElementValue (ifds::SrchIdValue, idValue); 
      }
      else if (searchBy == AllEntitySearchType::WHEREUSE)
      {
         _requestData->setElementValue (ifds::SrchWhereUse, whereUse);		  
		   if (fundCode != NULL_STRING)
         {
			   _requestData->setElementValue (ifds::SrchWhereUseCode, fundCode);
         }
      }
      ReceiveData ( DSTC_REQUEST::SEARCH,
                    *_requestData, 
                    ifds::DSTC0003_VW, 
                    DSTCRequestor (getSecurity(), false, false));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY EntitySearchList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getMore"));
   if (doMoreRecordsExist())
   {
      ReceiveData( DSTC_REQUEST::SEARCH,
                   *_requestData, 
                   ifds::DSTC0003_VW, 
                   DSTCRequestor (getSecurity(), false, true));
   }

   return GETCURRENTHIGHESTSEVERITY();
}
   
   //******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntitySearchList.cpp-arc  $
 * 
 *    Rev 1.55   Apr 27 2012 09:53:38   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.54   Apr 18 2012 11:29:00   if991250
 * SrcRefCode mandatory for search by reg agent
 * 
 *    Rev 1.53   Apr 16 2012 17:28:06   if991250
 * CPF Account Setup
 * 
 *    Rev 1.52   Apr 04 2012 21:34:26   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.51   Oct 27 2011 07:28:14   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.50   16 Jan 2009 17:23:26   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.49   Dec 15 2008 01:54:42   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.48   12 Jul 2007 18:41:16   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 *    Rev 1.47   Jul 26 2006 16:02:00   jankovii
 * PET 2192 FN02 Dealings Sender Cut Off Time.
 * 
 *    Rev 1.46   Oct 28 2005 17:02:40   jankovii
 * PET1228_FN01 Savings Directive Phase - enabled code (view is ready).
 * 
 *    Rev 1.45   Oct 27 2005 10:20:20   jankovii
 * PET1228_FN01-EU Savings Directive Phase
 * 
 *    Rev 1.44   Apr 18 2005 09:25:22   yingbaol
 * Incident: 288575, add search by where use code
 * 
 *    Rev 1.43   Mar 09 2005 16:04:46   yingbaol
 * PET 1171,FN01: EU saving entity update
 * 
 *    Rev 1.42   Mar 01 2005 11:52:28   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.41   Nov 23 2004 17:25:00   Fengyong
 * PET1117FN54 - adjustment after first day intergretion test
 * 
 *    Rev 1.40   Nov 14 2004 14:36:46   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.39   Nov 05 2004 16:24:32   FENGYONG
 * Add ExactSearch and AllEntity
 * 
 *    Rev 1.38   Aug 17 2004 17:45:04   ZHANGCEL
 * PTS Ticket 10033003 -- add new logic to force user enter at least 1 character in Lastname and Birth LastName fieled
 * 
 *    Rev 1.37   Jan 09 2004 17:07:28   VADEANUM
 * PTS 10025910 - Search for Business No.
 * 
 *    Rev 1.36   Dec 15 2003 11:54:40   linmay
 * modified prepareSearch for SSB
 * 
 *    Rev 1.35   Nov 11 2003 12:01:58   FENGYONG
 * PTS 10023901, fix condition
 * 
 *    Rev 1.34   Oct 06 2003 11:11:36   VADEANUM
 * PTS 10022547 - Cannot search by Business No
 * 
 *    Rev 1.33   Jul 16 2003 15:52:30   FENGYONG
 * Add business no search account
 * 
 *    Rev 1.32   Mar 21 2003 18:08:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.31   Oct 09 2002 23:54:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.30   Aug 29 2002 12:55:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.29   Aug 07 2002 15:47:44   FENGYONG
 * temp fix 
 * 
 *    Rev 1.28   Aug 07 2002 11:21:52   FENGYONG
 * add a default parameter and fix back the previous change
 * 
 *    Rev 1.27   Jul 24 2002 15:15:36   KOVACSRO
 * PTS 10009113 : fixed search by broker code failed.
 * 
 *    Rev 1.26   22 May 2002 18:28:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.25   May 14 2002 16:02:48   ZHANGCEL
 * PTS 10008189: Changed the conditon for the searching using Alt Account and Broker code
 * 
 *    Rev 1.24   May 08 2002 14:26:48   YINGBAOL
 * PTS10008102
 * 
 *    Rev 1.23   Aug 22 2001 15:03:48   DINACORN
 * Fixed search by telephone bug
 * 
 *    Rev 1.22   08 Aug 2001 12:05:24   HSUCHIN
 * code cleanup
 * 
 *    Rev 1.21   08 Aug 2001 12:02:58   HSUCHIN
 * bug fix for EntitySearchList::search();
 * 
 *    Rev 1.20   03 May 2001 14:06:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.19   Mar 29 2001 15:59:54   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.18   Mar 22 2001 10:01:08   YINGBAOL
 * implement searching other reference number
 * 
 *    Rev 1.17   Mar 18 2001 18:17:12   VASILEAD
 * Added NextOrPrevious
 * 
 *    Rev 1.16   Mar 12 2001 12:58:46   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.15   Feb 28 2001 11:23:00   VASILEAD
 * Enable search after a criteria and using broker information
 * 
 *    Rev 1.14   Feb 12 2001 15:01:48   DINACORN
 * Change "MSDW_JAPAN" to "JAPAN"
 * 
 *    Rev 1.13   Feb 09 2001 08:10:48   BUZILAMI
 * DATA_NOT_FOUND should be an Error for this list
 * 
 *    Rev 1.12   Jan 22 2001 11:56:20   YINGBAOL
 * fix null pointer
 * 
 *    Rev 1.11   Jan 18 2001 16:04:50   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.10   Dec 17 2000 20:23:22   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.9   Dec 06 2000 11:13:08   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.8   Nov 06 2000 11:49:44   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.7   Oct 18 2000 13:55:08   KOVACSRO
 * Changed 'CFDS - Canada' in 'Canada'.
 * 
 *    Rev 1.6   Oct 13 2000 15:01:16   FENGYONG
 * Add sortby SR for broker srch
 * 
 *    Rev 1.5   Sep 26 2000 15:32:44   KOVACSRO
 * Added classFieldInfo and AreaCode for search.
 * 
 *    Rev 1.4   Sep 22 2000 14:34:44   FENGYONG
 * Add field3 for slsrep search
 * 
 *    Rev 1.3   Sep 14 2000 17:28:00   VASILEAD
 * Modified to accomodate the new infra from Sept 12
 * 
 *    Rev 1.2   Aug 29 2000 15:15:00   YINGBAOL
 * add search account using intermediary code and account
 * 
 *    Rev 1.1   Jun 01 2000 14:56:54   BUZILA
 * putting LastName first on entity search
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.19   Jan 16 2000 17:03:02   VASILEAD
 * ?
 * 
 *    Rev 1.18   Jan 14 2000 08:51:56   POPESCUS
 * allow spaces for telephone number search
 * 
 *    Rev 1.17   Jan 11 2000 14:54:42   POPESCUS
 * quick fix
 * 
 *    Rev 1.16   Jan 09 2000 13:30:36   VASILEAD
 * Modifications for the new slot
 * 
 *    Rev 1.15   Jan 05 2000 20:10:44   BUZILA
 * adding list flag
 * 
 *    Rev 1.14   Dec 12 1999 16:25:20   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/