//******************************************************************************
//
// ^FILE   : DSTCAWDDataConvert.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Dec. 18, 2003
//
// ^CLASS    : DSTCAWDDataConvert
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
//#include <ifastcbo\mfcancbo.hpp>
//#include <boost\utility.hpp>
//#include <core\bfsessn\bfcpsession.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

// from MFAccount
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0091_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>
#include <ifastdataimpl\dse_dstc0120_vw.hpp>
#include <ifastdataimpl\dse_dstc0142_vw.hpp>
#include <ifastdataimpl\dse_dstc0144_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
// From Trade
#include <ifastdataimpl\dse_dstc0147_req.hpp>
#include <ifastdataimpl\dse_dstc0147_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
// From Address
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_req.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_vw.hpp>
// From Entity
#include <ifastdataimpl\dse_dstc0051_req.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>


#include <bfsessn\bfcpsessiontags.h>

#include "DSTCAWDSession.hpp"
#include "DSTCAWDDataConvert.hpp"

#include <ifastcbo\DSTCWorkSession.hpp>

#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\demographics.hpp>
#include <ifastcbo\regdocumentlist.hpp>
#include <ifastcbo\regdocument.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\addresslist.hpp>
#include <assert.h>
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "DSTCAWDDataConvert" );
   const I_CHAR * WORKSTATION           = I_( "Workstation" );
   const I_CHAR * SETTINGS              = I_( "Settings" );
   const I_CHAR * AWDWORK				= I_( "AwdWork" );
   const I_CHAR * AWDTABLE				= I_( "AwdTable" );
   const I_CHAR * const ICHARS_Y             = I_( "Y" );
   const I_CHAR * const ICHARS_N             = I_( "N" );
   const I_CHAR * const ICHARS_DD            = I_( "DD" );
   const I_CHAR * const ICHARS_MM            = I_( "MM" );
   const I_CHAR * const ICHARS_YYYY          = I_( "YYYY" );
   const I_CHAR * const ICHARS_MINUS         = I_( "-" );
 }


namespace SessionTags
{
   const I_CHAR *SESSION = I_( "Session" );

}

namespace ifds
{

   extern CLASS_IMPORT const BFTextFieldId CallerName;
   extern CLASS_IMPORT const BFTextFieldId Operator_Extension;
   extern CLASS_IMPORT const BFTextFieldId RelationShip;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId HomePhone;
   extern CLASS_IMPORT const BFTextFieldId CallStartTime;
   extern CLASS_IMPORT const BFTextFieldId CallEndTime;
	extern CLASS_IMPORT const BFTextFieldId Batch;
   extern CLASS_IMPORT const BFTextFieldId RegDocStatus;
}


//*******************************************************************************

DSTCAWDDataConvert::DSTCAWDDataConvert(DSTCAWDSession* pSession)
//m_pSession(pSession)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	m_pSession = pSession;

	assert( m_pSession );
	
}
//*******************************************************************************
DSTCAWDDataConvert::~DSTCAWDDataConvert()
{

}


//*************************************************************************************************
void DSTCAWDDataConvert::getExportAwdCallerInfo( BFData &data  )
{
  ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
  Configuration cfgTable = pMgr->retrieveConfig( I_( "CALLER INFO" ) );
  DString dstrFieldName,dstrValue,awdFieldId;
  Configuration::iterator iter = cfgTable.begin();
  while( iter != cfgTable.end() )
  {
		awdFieldId = ( *iter ).getKey();
		dstrFieldName = cfgTable.getValueAsString(awdFieldId);
		const BFFieldId  fieldId( BFFieldId::getId( dstrFieldName ) );
		getSession()->getAwdField( fieldId, dstrValue );
		data.setElementValue( awdFieldId, dstrValue, true);
		++iter;
  }	

}

//************************************************************************************************
void DSTCAWDDataConvert::getAwdFormatData (const DString &eventTable,
                                           BFData &data)
{
	ConfigManager *pMgr = ConfigManager::getManager (SessionTags::SESSION);
	Configuration cfgTable = pMgr->retrieveConfig (eventTable);
	Configuration::iterator iter = cfgTable.begin();
	DString dstrTabName,
      dstrTabdsc;
	
   while (iter != cfgTable.end())
	{
		dstrTabName = (*iter).getKey();
		dstrTabdsc =  cfgTable.getValueAsString (dstrTabName);

		if (dstrTabName != AWDWORK  && dstrTabName != AWDTABLE) 
		{	
			getAwdFieldFromCBO (dstrTabdsc, data);		
		}
      ++iter;
	}
}

//***********************************************************************************
// currently we only support one first CBO item in list because AWD issue
//
void DSTCAWDDataConvert::getAwdFieldFromCBO ( const DString &dstrTabName,
                                              BFData &data)
{
   DSTCWorkSession *pDSTCWorkSession = getSession()->getDSTCWorkSession();	
	ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
	Configuration cfgTable = pMgr->retrieveConfig (dstrTabName);
	DString accountNum;
	
   getSession()->getAwdField (ifds::AccountNum, accountNum); // last account number
	MFAccount* pMFAccount (NULL);
	
   if ( pDSTCWorkSession ->getMFAccount (BF::HOST, accountNum, pMFAccount) &&
        pMFAccount)
   {
	   if (dstrTabName == I_("ACCOUNT_TABLE"))
	   {
         retrieveCBOInfo (pMFAccount, cfgTable, data);
	   }
	   else if (dstrTabName == I_("ADDRESS_TABLE"))
	   {
			DString shrNum;
			Shareholder* pShr (NULL);

         pMFAccount->getField (ifds::ShrNum, shrNum, BF::HOST);		
			if ( pDSTCWorkSession->getShareholder (BF::HOST, shrNum, pShr) <=WARNING && 
              pShr)
			{
				AddressList *pAddressList (NULL);
				
            if (pShr->getAddressList (pAddressList, BF::HOST ) <= WARNING &&
                pAddressList)
            {
				   BFObjIter iterAddrList( *pAddressList, 
                                        BF::HOST,
                                        true,
                                        BFObjIter::ITERTYPE::NON_DELETED);
		         
               if (!iterAddrList.end())
				   { 
					   BFAbstractCBO* pCBO = iterAddrList.getObject() ;
					   retrieveCBOInfo (pCBO, cfgTable, data);
				   }
            }
		   }			
	   }
	   else if (dstrTabName == I_("TRADE_TABLE"))
	   {
	      WorksessionTradesList *pWorksessionTradesList (NULL);

		   pDSTCWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
   		
         BFObjIter iter ( *pWorksessionTradesList, 
                          BF::HOST, 
                          false, 
                          BFObjIter::ITERTYPE::NON_DELETED);
   		
         while (!iter.end())
         {
            // in release 59, WorkdsessionTradeList is not only contain Trade object anymore.
            // Incident 335528
            //
            Trade* pTrade = dynamic_cast <Trade*> (iter.getObject());
            if (pTrade)
            {
			      retrieveCBOInfo (pTrade, cfgTable, data);
               break;
            }
            ++iter;
         }	
	   }
	   else if (dstrTabName == I_("ENTITY_TABLE"))
	   {
         AccountEntityXref *pAccountEntityXref (NULL);
         Entity* pEntity (NULL);
         DString entityId;
         
         pDSTCWorkSession->getAccountEntityXref (BF::HOST, pAccountEntityXref);
         pAccountEntityXref->GetEntityIdForAccountOwnerSequence1 (accountNum, BF::HOST, entityId);
         if (pDSTCWorkSession->getEntity( BF::HOST, entityId, pEntity) <= WARNING && 
             pEntity)
         {
            retrieveCBOInfo (pEntity, cfgTable, data);
         }	
	   }
	   else if (dstrTabName == I_("SHAREHOLDER_TABLE"))
	   {
         DString shrNum;
			Shareholder* pShr (NULL);

         pMFAccount->getField (ifds::ShrNum, shrNum, BF::HOST, false);
			if ( pDSTCWorkSession->getShareholder (BF::HOST, shrNum, pShr) <= WARNING && 
              pShr)
			{
			   if (pShr)
			   {
				   retrieveCBOInfo (pShr, cfgTable, data);
			   }
		   }
	   }
	   else if (dstrTabName == I_("CONFIRMATION_TABLE"))
	   {
		   DString awdFieldId, 
            cboFieldName, 
            dstrBatchNum;

         getSession()->getAwdField (ifds::Batch, dstrBatchNum); 

		   Configuration::iterator iter = cfgTable.begin();
		   while (iter != cfgTable.end())
		   {
			   awdFieldId = (*iter ).getKey();
			   cboFieldName = cfgTable.getValueAsString (awdFieldId);

			   if (cboFieldName == I_("BatchName"))
			   {
				   dstrBatchNum.stripLeading().stripTrailing().upperCase();
				   if (!dstrBatchNum.empty())
				   {
					   data.setElementValue (awdFieldId, dstrBatchNum, true);
				   }
			   }
			   ++iter;
		   }
	   }
	   else if (dstrTabName == I_("KYC_TABLE"))
	   {
			Demographics* pDemographics (NULL);

         if (pMFAccount->getDemographicsList (pDemographics, BF::HOST) <= WARNING && 
             pDemographics)
			{
		 		retrieveCBOInfo (pDemographics, cfgTable, data);		 
			}	
	   }
	   else if (dstrTabName == I_("OSTDOC_TABLE"))
	   {
		   ENTITIES_VECTOR acctOwnerEntities;

         pMFAccount->getAcctOwnerEntities (acctOwnerEntities, BF::HOST);
      	Configuration::iterator iterCfgTable = cfgTable.begin();

		   int iNumOfEntities = acctOwnerEntities.size();

		   for (int i = 0; i < iNumOfEntities; ++i)
		   {
   			DString entityId = acctOwnerEntities [i];
   
            Entity *pEntity (NULL);
            WorkSessionEntityList *pWorkEntityList = NULL;
            
            pDSTCWorkSession->getWorkSessionEntityList (pWorkEntityList);
            if (pWorkEntityList)
            {
               pWorkEntityList->getEntity (BF::HOST, entityId, pEntity);
               if (pEntity && !pEntity->isDead (BF::HOST))
               {
			         RegDocumentList *pRegDocumentList (NULL);

			         pMFAccount->getRegDocumentsList (pRegDocumentList, entityId, BF::HOST) ;
   	
                  if (pRegDocumentList)
                  {
                     BFObjIter iter (*pRegDocumentList, 
                                    BF::HOST, 
                                    false, 
                                    BFObjIter::ITERTYPE::NON_DELETED);
               	
                     while (!iter.end())
                     {
                        RegDocument* pRegDocument = dynamic_cast <RegDocument*> (iter.getObject());
                        DString regDocStatus;
                        
                        pRegDocument->getField (ifds::RegDocStatus, regDocStatus, BF::HOST);
                        if (pRegDocument && regDocStatus == I_("O")) //outstanding documents
                        {
			                  if (iterCfgTable != cfgTable.end ())
                           {
		                        DString awdFieldId,
                                 cboFieldName,
                                 strValue;

                              awdFieldId =  (*iterCfgTable).getKey();
		                        cboFieldName = cfgTable.getValueAsString (awdFieldId);
                              
                              const BFFieldId fieldId (BFFieldId::getId (cboFieldName));
                              
                              pRegDocument->getField (fieldId, strValue, BF::HOST);
                              data.setElementValue (awdFieldId, strValue, true);
                              ++iterCfgTable;
                           }
                        }
                        ++iter;
                     }	
                  }
               }
            }
		   }
	   }
   }
}

//************************************************************************************
void DSTCAWDDataConvert::retrieveCBOInfo (const BFAbstractCBO *pcbo,
                                          Configuration &cfg,
                                          BFData &data)
{
	Configuration::iterator iter = cfg.begin();
	DString cboFieldName,
       awdFieldId,
       dstrValue;

   while (iter != cfg.end())
	{
		awdFieldId = ( *iter ).getKey();
		cboFieldName = cfg.getValueAsString (awdFieldId);
		
      const BFFieldId fieldId (BFFieldId::getId (cboFieldName));
		
      pcbo->getField (fieldId, dstrValue, BF::HOST, false);
	
		const BFDataFieldProperties* pProp = BFDataFieldProperties::get( fieldId );
		
      if (pProp->isText())
		{	
			dstrValue.stripLeading().stripTrailing();
			int n;
			
         while ((n = dstrValue.find(I_(";"))) != -1)
			{  // convert ; to , because it will cause AWD issue.
				dstrValue[n] = I_(',');
			}
      }
		else if (pProp->isDate())
		{
         if (!dstrValue.empty())
         {
            DString dstrTempDate,
               dstrDateMask = GetConfigValueAsString (I_("LocaleFormats"), I_("HostMasks"), I_("D"));
            dstrDateMask.upperCase();
            dstrTempDate = dstrValue.substr (dstrDateMask.find (ICHARS_YYYY), 4);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrValue.substr (dstrDateMask.find (ICHARS_MM), 2);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrValue.substr (dstrDateMask.find(ICHARS_DD), 2);
            dstrValue = dstrTempDate;
         }
		}
		else if (pProp->isDecimal() || 
               pProp->isNumeric())
		{
			dstrValue.strip().stripLeading ('0');		
		}
//according Linh,Batch in AWD has to be upper Case. PTS10029297			
		if (cboFieldName.strip() == I_("BatchName"))
		{
			dstrValue.stripLeading().stripTrailing().upperCase();
		}
		data.setElementValue (awdFieldId, dstrValue, true);
		++iter;
	}
}

//**************************************************************
void DSTCAWDDataConvert::convertFieldValueForMarket(const BFFieldId& fieldId,DString& dstrInOut)
{

	DString dstrMarket = DSTCommonFunctions::getMarket();
	DString dstrValue( dstrInOut );
	if( dstrMarket == MARKET_IDS::LUXEMBOURG )
	{
		if( fieldId == ifds::AmtType )
		{
			dstrInOut = ( dstrValue == I_("D") )? I_("C") : I_("S");
		
		}
		else if( fieldId == ifds::TradesPayType )
		{
			dstrInOut = ( dstrValue == I_("E") )? I_("W") : I_("C");			
		}
		else if( fieldId == ifds::ExchRate )
		{
			dstrInOut = ( dstrValue.empty() ) ? I_("N") : I_("Y");			
		}
	}
}

//****************************************************************************
void DSTCAWDDataConvert::retrieveAwdBusinessArea(DString& dstrMgmtCoId,
												 DString& dstrBusinessArea )
{
	dstrMgmtCoId.strip();
	ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
	Configuration cfgTable = pMgr->retrieveConfig( I_( "MGMCO" ) );
	Configuration::iterator iter = cfgTable.begin();
	while( iter != cfgTable.end() )
	{
		DString dstrKey = ( *iter ).getKey();
		DString cboFieldName = cfgTable.getValueAsString( dstrKey );
		cboFieldName.strip();
        if( dstrMgmtCoId ==  cboFieldName )
		{
			dstrBusinessArea = dstrKey;
			break;
		}
		++iter;
	}	
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastawd/DSTCAWDDataConvert.cpp-arc  $
// 
//    Rev 1.16   31 Mar 2009 16:42:38   kovacsro
// IN#1644614 - KYC @ NASU not populating in Integration file
// 
//    Rev 1.15   22 Dec 2008 16:42:16   popescu
// Incident 1522603 - AWD ShowStopper - 
// 
//    Rev 1.14   04 Nov 2008 13:11:34   popescu
// KYC-AML fixes after system integrated testing
// 
//    Rev 1.13   31 Oct 2008 16:17:04   popescu
// KYC/AML - joint accounts feature
// 
//    Rev 1.12   28 Oct 2008 13:11:04   popescu
// PET 59888 FN03 AML KYC - check in to fix complile issues
// 
//    Rev 1.11   Aug 01 2008 11:25:30   jankovii
// PET 59888 FN01 AML Enhancement.
// 
//    Rev 1.10   Jan 11 2007 11:29:30   popescu
// Incident# 797275 - remove conversion of TradesPayType to W and also check if dates are empty before trying to format them.
// 
//    Rev 1.9   Jan 24 2006 09:34:54   zhengcon
// Incident #521273 -- Auto Clone - Integration  - Add new LOB (Batch) field to confirmation
// 
//    Rev 1.8   Jun 20 2005 16:04:30   Yingbaol
// Incident335528, retrieve field from Trade CBO has been changed due to WorkSessionTradeList changes.
// 
//    Rev 1.7   Apr 20 2004 10:10:30   YINGBAOL
// PTS10029297: uppercase batch
// 
//    Rev 1.6   Mar 12 2004 15:43:30   HERNANDO
// PET987 - Support for Lux specific FX value.  ExchRate is used as a flag.
// 
//    Rev 1.5   Jan 21 2004 17:52:32   YINGBAOL
// PET987: Business Area should not be retrieved from Configuration file
// 
//    Rev 1.4   Jan 21 2004 10:21:28   YINGBAOL
// PET 987:replace ";" with "," for AWD
// 
//    Rev 1.3   Jan 19 2004 17:39:04   YINGBAOL
// PET 987: correct spelling mistakes
// 
//    Rev 1.2   Jan 19 2004 14:03:20   YINGBAOL
// PET 987: DataType and market support
// 


  */