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
// ^FILE   : ExternalInstitutionList.cpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : ExternalInstitutionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "externalinstitutionlist.hpp"

#include "externalinstitution.hpp"
#include "mgmtco.hpp"
#include "translationtablebyasyncreading.hpp"

#include <bfdata\bfdataid.hpp>
#include <bfdata\bfdata.hpp>

#include <conditions\iFastLayer\iFast\ifastdbrkr\IFast_IFast_ifastdbrkr_err_data_not_found.h>

#define EXTRACT_VALUE(s, val, delimiter) \
   pos = s.find (delimiter); \
   val = s.substr (0, pos);

#define CHOP_STRING(s, delimiter) \
   pos = s.find (delimiter); \
   pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
   if (pos != DString::npos) \
   s = s.substr (pos); \
         else \
         s = NULL_STRING;

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyName;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
   extern CLASS_IMPORT const BFTextFieldId ExternalInstitution;
   extern CLASS_IMPORT const BFTextFieldId TrackTrOther;
}

namespace SERACH_INIST_BY
{
   const I_CHAR * CODE = I_("00");
   const I_CHAR * NAME = I_("01");
   const I_CHAR * ALL  = I_("02");
}

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("ExternalInstitutionList");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,                    State Flags,            Group Flags 
   {ifds::ExternalInstitution,         BFCBO::NOT_ON_HOST,        0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ExternalInstitutionList::ExternalInstitutionList(BFAbstractCBO &parent)
   :MFCanBFCbo (parent)
   ,_maxNumRecord(5)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   setObjectAsList();
}

//******************************************************************************
ExternalInstitutionList::~ExternalInstitutionList()
{
   TRACE_DESTRUCTOR(CLASSNAME);

   if (_mapSubstitutionList.size()>0)
      _mapSubstitutionList.clear();
}

//******************************************************************************
SEVERITY ExternalInstitutionList::init(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   if (_mapSubstitutionList.size() == 0)
   {
      DString allSubstitution = NULL_STRING;

      // get string from mgmtco
      MiscInfoExternalInstitutionList* pMiscInfoExternalInstitutionList = nullptr;
      if ( getWorkSession().getMgmtCo().getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList) <= WARNING &&
         pMiscInfoExternalInstitutionList != nullptr)
      {
         pMiscInfoExternalInstitutionList->getSubstitutionList(allSubstitution);
      }

      if (!allSubstitution.empty())
      {
         while (allSubstitution != NULL_STRING)
         {
            DString::size_type pos = 0;
            DString dstrExtInstDesc, dstrExtInstCode;

            EXTRACT_VALUE(allSubstitution, dstrExtInstDesc, I_(";"));
            CHOP_STRING(allSubstitution, I_(";"));

            EXTRACT_VALUE(dstrExtInstDesc, dstrExtInstCode, I_("="));
            CHOP_STRING(dstrExtInstDesc, I_("="));

            _mapSubstitutionList[dstrExtInstCode] = dstrExtInstDesc;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ExternalInstitutionList::doCreateObject( const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   ExternalInstitution* pExternalInstitution = new ExternalInstitution( *this );

   pExternalInstitution->init (data);
   pObjOut = pExternalInstitution;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ExternalInstitutionList::doSearch(bool bNext, const DString& searchBy, const DString searchKey, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doSearch" ) );

   if(_mapSubstitutionList.size() > 0)
   {
      DString dstrSearchBy(searchBy), dstrSearchKey(searchKey);
      dstrSearchBy.strip().upperCase();
      dstrSearchKey.strip();

      if (!bNext && !dstrSearchBy.empty())
      {
         removedExistingItems(idDataGroup);
         _setCurrItemInList.clear();
         _moreRecordsAvailable = false;

         for (auto a : _mapSubstitutionList)
         {
            BFCBO *pObj = nullptr;
            bool bFound = false;
            BFData data;

            if( dstrSearchBy == SERACH_INIST_BY::ALL && dstrSearchKey.empty()) // all
            {
               data.addElement(ifds::CompanyCode,a.first,false);
               data.addElement(ifds::CompanyName,a.second,false);
               bFound = true;
            }
            else if(!dstrSearchKey.empty())
            {
               if (SERACH_INIST_BY::CODE == dstrSearchBy)
               {
                  DString strCode = a.first;

                  bFound = (strCode.find(dstrSearchKey) != DString::npos);

                  if(bFound)
                  {
                     data.addElement(ifds::CompanyCode,a.first,false);
                     data.addElement(ifds::CompanyName,a.second,false);
                  }
               }
               else if (SERACH_INIST_BY::NAME == dstrSearchBy)
               {
                  DString strName = a.second;
                  DString strSearchKey = dstrSearchKey;

                  strName.lowerCase();
                  strSearchKey.lowerCase();

                  bFound = (strName.find(strSearchKey) != DString::npos);

                  if (bFound)
                  {
                     data.addElement(ifds::CompanyCode,a.first,false);
                     data.addElement(ifds::CompanyName,a.second,false);
                  }
               }
            }

            if (bFound)
            {
               BFObjIter iterSearch(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

               if (iterSearch.getNumberOfItemsInList() >= _maxNumRecord)
               {
                  _moreRecordsAvailable = true;
                  break;
               }

               doCreateObject( data, pObj );

               if( pObj != nullptr )
               {
                  BFObjectKey objKey;
                  getKey( objKey, &(data) );
                  setObject( objKey, pObj );

                  // clear this for HOST
                  pObj->clearUpdatedFlags( idDataGroup );
                  pObj->setAllFieldsValid( idDataGroup );

                  _setCurrItemInList.insert(a.first);
               }
            }
         }
      }
      else if (bNext && !dstrSearchBy.empty())
      {
         unsigned int iNumAddRecord = 0;
         std::set<DString> setMatchedItem;
         for (auto a : _mapSubstitutionList)
         {
            if( dstrSearchBy == SERACH_INIST_BY::ALL && dstrSearchKey.empty()) // all
            {
               setMatchedItem.insert(a.first);
            }
            else if(!dstrSearchKey.empty() && SERACH_INIST_BY::CODE == dstrSearchBy)
            {
               DString strCode = a.first;
               if( (strCode.find(dstrSearchKey) != DString::npos))
               {
                  setMatchedItem.insert(a.first);
               }
            }
            else if(!dstrSearchKey.empty() && SERACH_INIST_BY::NAME == dstrSearchBy)
            {
               DString strName = a.second;
               DString strSearchKey = dstrSearchKey;

               strName.lowerCase();
               strSearchKey.lowerCase();
               if ( (strName.find(strSearchKey) != DString::npos))
               {
                  setMatchedItem.insert(a.first);
               }
            }
         }

         for (auto b : setMatchedItem)
         {
            if (_setCurrItemInList.find(b) == _setCurrItemInList.end() &&
               iNumAddRecord < _maxNumRecord)
            {
               BFCBO *pObj = nullptr;
               bool bFound = false;
               BFData data;

               auto& c = _mapSubstitutionList[b];

               data.addElement(ifds::CompanyCode,b,false);
               data.addElement(ifds::CompanyName,c,false);

               doCreateObject( data, pObj );

               if( pObj != nullptr )
               {
                  BFObjectKey objKey;
                  getKey( objKey, &(data) );
                  setObject( objKey, pObj );

                  // clear this for HOST
                  pObj->clearUpdatedFlags( idDataGroup );
                  pObj->setAllFieldsValid( idDataGroup );

                  _setCurrItemInList.insert(b);
                  iNumAddRecord++;

                  if (_setCurrItemInList.size() == setMatchedItem.size())
                  {
                     _moreRecordsAvailable = false;
                  }
                  else
                  {
                     _moreRecordsAvailable = true;
                  }
               }
            }
         }
      }

      if (!_moreRecordsAvailable)
      {
          appendOtherToSearchList(idDataGroup);
      }
   }
   else 
   {
       removedExistingItems(idDataGroup);
       appendOtherToSearchList(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ExternalInstitutionList::appendOtherToSearchList(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("appendOtherToSearchList"));

    DString strOtherCode;

    getWorkSession().getOption2(ifds::TrackTrOther, strOtherCode, idDataGroup, false);
    strOtherCode.strip().upperCase();

    if (!strOtherCode.empty()) //&& _setCurrItemInList.size() == 0)
    {
        BFCBO *pObj = nullptr;
        bool bFound = false;
        BFData data;

        data.addElement(ifds::CompanyCode, strOtherCode, false);
        data.addElement(ifds::CompanyName, I_("Other"), false);

        doCreateObject(data, pObj);

        if (pObj != nullptr)
        {
            BFObjectKey objKey;
            getKey(objKey, &(data));
            setObject(objKey, pObj);

            // clear this for HOST
            pObj->clearUpdatedFlags(idDataGroup);
            pObj->setAllFieldsValid(idDataGroup);

            _setCurrItemInList.insert(strOtherCode);
        }

        return GETCURRENTHIGHESTSEVERITY();
    }
}


//******************************************************************************
void ExternalInstitutionList::removedExistingItems(const BFDataGroupId &idDataGroup)
{
   BFObjIter iterSearch(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   if (iterSearch.getNumberOfItemsInList() >= 0)
   {
      iterSearch.begin();

      while(!iterSearch.end())
      {
         iterSearch.removeObjectFromMap(true);
      }
   }
}

//******************************************************************************
bool ExternalInstitutionList::doesCodeExist(const DString key, const BFDataGroupId &idDataGroup)
{
   bool bRetValue = false;
   DString strOtherCode, srcKey(key);

   getWorkSession().getOption2(ifds::TrackTrOther, strOtherCode, idDataGroup, false);
   strOtherCode.strip().upperCase();

   if (!strOtherCode.empty() && srcKey.stripAll().upperCase() == strOtherCode)
   {
       bRetValue = true;
   }
   else if (_mapSubstitutionList.size() > 0)
   {
      DString strCode = key;
      std::map<DString,DString>::iterator itPos = _mapSubstitutionList.find(strCode.upperCase());

      bRetValue = (itPos != _mapSubstitutionList.end());
   }

   return bRetValue;
}

//******************************************************************************
void ExternalInstitutionList::getExternalInstitutionSubstitutionList(DString& listOut, const BFDataGroupId &idDataGroup)
{
   if (_mapSubstitutionList.size() > 0)
   {
      listOut = NULL_STRING;
      for (auto a : _mapSubstitutionList)
      {
         listOut += a.first;
         listOut += I_("=");
         listOut += a.second;
         listOut += I_(";");
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ExternalInstitutionList.cpp-arc  $
// 