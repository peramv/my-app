//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : VerificationConf.hpp
// ^AUTHOR : Adrian Vasile/Zijian Ying
// ^DATE   : July 19, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : VerificationConf
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "verificationconf.hpp"
#include <ifastdataimpl\dse_dstc0145_req.hpp>
#include <ifastdataimpl\dse_dstc0145_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest VERIFICATIONCONF;
}

FieldMap TrakShr_FieldMap[]=
{
   I_("SHRNUM"),                    I_("Repeating1"),
   I_("ACCTDESIGNATION"),                     I_("Repeating2"),
   I_("GROUPCODE"),                     I_("Repeating3"),
   I_("RESPROVCODE"),                     I_("Repeating4"),
   I_("TAXJURISCODE"),                    I_("Repeating5"),
   I_("INSTCODE"),                    I_("Repeating6"),
   I_("TRANSITNO"),                     I_("Repeating7"),
   I_("BANKACCTNUM"),                     I_("Repeating8"),
   I_("ADDITIONALINFO"),                    I_("Repeating9"),
   NULL
};

FieldMap TrakAct_FieldMap[]=
{
   I_("SHRNUM"),                    I_("Repeating1"),
   I_("ACCOUNTNUM"),                    I_("Repeating2"),
   I_("ADDITIONALINFO"),                    I_("Repeating3"),
   I_("ALTACCOUNT"),                    I_("Repeating4"),
   I_("BENOWNER"),                    I_("Repeating5"),
   I_("BRANCHCODE"),                    I_("Repeating6"),
   I_("BRANCHNAME"),                    I_("Repeating7"),
   I_("BROKERCODE"),                    I_("Repeating8"),
   I_("BROKERNAME"),                    I_("Repeating9"),
   I_("CURRENCY"),                    I_("Repeating10"),
   I_("EMPLOYEE"),                    I_("Repeating11"),
   I_("INTRUSTFOR"),                    I_("Repeating12"),
   I_("ITFDETAILS"),                    I_("Repeating13"),
   I_("MARKETMAIL"),                    I_("Repeating14"),
   I_("SALESREPCODE"),                    I_("Repeating15"),
   I_("SALESREPNAME"),                    I_("Repeating16"),
   I_("STOPPUR"),                     I_("Repeating17"),
   I_("STOPRED"),                     I_("Repeating18"),
   I_("STOPXFERIN"),                    I_("Repeating19"),
   I_("STOPXFEROUT"),                     I_("Repeating20"),
   I_("SUPCONF"),                     I_("Repeating21"),
   I_("UNSEIZABLE"),                    I_("Repeating22"),
   I_("TAXTYPE"),                     I_("Repeating23"),
   I_("ACCTTYPE"),                    I_("Repeating24"),
   I_("STATUS"),                    I_("Repeating25"),
   I_("MANAGEMENTSTYLE"),                    I_("Repeating26"),
   I_("DISCRETIONARY"),                    I_("Repeating27"),
   NULL
};

FieldMap TrakEnt_FieldMap[]=
{
   I_("ACCOUNTNUM"),                    I_("Repeating1"),
   I_("ENTITYID"),                    I_("Repeating2"),
   I_("AUTHORIZEDTOTRADE"),                     I_("Repeating3"),
   I_("BUSEXT"),                    I_("Repeating4"),
   I_("BUSFAX"),                    I_("Repeating5"),
   I_("BUSPHONE"),                    I_("Repeating6"),
   I_("DOFBIRTH"),                    I_("Repeating7"),
   I_("EMAIL"),                     I_("Repeating8"),
   I_("ENTITYTYPE"),                    I_("Repeating9"),
   I_("FIRSTNAME"),                     I_("Repeating10"),
   I_("GENDER"),                    I_("Repeating11"),
   I_("HOMEFAX"),                     I_("Repeating12"),
   I_("HOMEPHONE"),                     I_("Repeating13"),
   I_("LANG"),                    I_("Repeating14"),
   I_("LASTNAME"),                    I_("Repeating15"),
   I_("SALUTATION"),                    I_("Repeating16"),
   I_("SIN"),                     I_("Repeating17"),
   I_("BENIRREVOCABLE"),                    I_("Repeating18"),
   I_("BENPERCENTAGE"),                     I_("Repeating19"),
   I_("BENRELATECODE"),                     I_("Repeating20"),
   I_("JOINTDISPCODE"),                     I_("Repeating21"),
   I_("JOINTTYPE"),                     I_("Repeating22"),
   I_("ADDITIONALINFO"),                    I_("Repeating23"),
   NULL
};

FieldMap TrakAdd_FieldMap[]=
{
   I_("SHRNUM"),                    I_("Repeating1"),
   I_("ADDRCODE"),                    I_("Repeating2"),
   I_("ADDRLINE1"),                     I_("Repeating3"),
   I_("ADDRLINE2"),                     I_("Repeating4"),
   I_("ADDRLINE3"),                     I_("Repeating5"),
   I_("ADDRLINE4"),                     I_("Repeating6"),
   I_("COUNTRYCODE"),                     I_("Repeating7"),
   I_("POSTALCODE"),                    I_("Repeating8"),
   I_("EXCEPTIONMAIL"),                     I_("Repeating9"),
   I_("EXCEPTIONDETAILS"),                    I_("Repeating10"),
   I_("MAILINGINSTRUCTIONS"),                     I_("Repeating11"),
   NULL
};

FieldMap TrakTxn_FieldMap[]=
{
   I_("ACCOUNTNUM"),                    I_("Repeating1"),
   I_("TRANSID"),                     I_("Repeating2"),
   I_("ADDITIONALINFO"),                    I_("Repeating3"),
   I_("AMOUNT"),                    I_("Repeating4"),
   I_("AMOUNTTYPE"),                    I_("Repeating5"),
   I_("CHEQUEADDR"),                    I_("Repeating6"),
   I_("CLASSFROMCODE"),                     I_("Repeating7"),
   I_("CLASSFROMNAME"),                     I_("Repeating8"),
   I_("CLASSTOCODE"),                     I_("Repeating9"),
   I_("CLASSTONAME"),                     I_("Repeating10"),
   I_("EXCHRATE"),                    I_("Repeating11"),
   I_("FEE"),                     I_("Repeating12"),
   I_("FLATPERCENT"),                     I_("Repeating13"),
   I_("FUNDFROMCODE"),                    I_("Repeating14"),
   I_("FUNDFROMNAME"),                    I_("Repeating15"),
   I_("FUNDTOCODE"),                    I_("Repeating16"),
   I_("FUNDTONAME"),                    I_("Repeating17"),
   I_("PAYTYPE"),                     I_("Repeating18"),
   I_("SETTLECURRENCY"),                    I_("Repeating19"),
   I_("SETTLEINFUNDCURR"),                    I_("Repeating20"),
   I_("TRANSTYPE"),                     I_("Repeating21"),
   I_("DIVTOSAMEFUND"),                     I_("Repeating22"),
   I_("DIVTOFUNDLIST"),                     I_("Repeating23"),
   I_("DIVTOCLASSLIST"),                    I_("Repeating24"),
   I_("DIVTOPERCENTLIST"),                    I_("Repeating25"),
   I_("INITPUR"),                    I_("Repeating26"),
   I_("INITPURDIVINST"),                     I_("Repeating26"),
   I_("REMARKS1"),                     I_("Repeating27"),
   I_("CLIENTTRADEID"),                    I_("Repeating28"),
   NULL
};

TableData _TableData[]=
{
   I_("TRAKSHR"),I_("Shr"), TrakShr_FieldMap,
   I_("TRAKACT"),I_("Act"), TrakAct_FieldMap,
   I_("TRAKENT"),I_("Ent"), TrakEnt_FieldMap,
   I_("TRAKADD"),I_("Add"), TrakAdd_FieldMap,
   I_("TRAKTXN"),I_("Txn"), TrakTxn_FieldMap
};

namespace
{
   const I_CHAR * const CLASSNAME = I_( "VerificationConf" );
}

namespace ENTITY_TYPE
{
   const long ACCOUNT_OWNER_1 = 1;
   const long ACCOUNT_OWNER_2 = 2;
   const long ACCOUNT_BENEFICIARY = 3;
}

namespace VERIFICATIONCONFLT //stands for verification confirmation literals
{
   const I_CHAR * const SHRNUM = I_( "ShrNum" );  
   const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
   extern CLASS_IMPORT const BFDataId DSTC0145_REQRepeat_Record;
   extern CLASS_IMPORT const BFDataId DSTC0069_VWRepeat_Record ;
   extern CLASS_IMPORT const BFDataId DSTC0004_VWRepeat_Record ;
   extern CLASS_IMPORT const BFDataId DSTC0050_VWRepeat_Record ;
   extern CLASS_IMPORT const BFDataId DSTC0051_VW ;
   extern CLASS_IMPORT const BFDataId DSTC0043_VWRepeat_Record ;
   extern CLASS_IMPORT const BFDataId DSTC0017_VWRepeat_Record ;
}

VerificationConf::VerificationConf( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
VerificationConf::~VerificationConf()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY VerificationConf::init( DString& param,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   if( param != NULL_STRING )
   {
      VerificationStringProcessor *pVerificationStringProcessor = new VerificationStringProcessor;
      int NumItem = sizeof(_TableData)/sizeof(_TableData[0]);
      pVerificationStringProcessor->init( param, _TableData, NumItem );

      BFData queryData(ifds::DSTC0145_REQ);

      pVerificationStringProcessor->Process( &queryData );
      delete pVerificationStringProcessor;

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );

      ReceiveData( DSTC_REQUEST::VERIFICATIONCONF, queryData, ifds::DSTC0145_VW, DSTCRequestor( getSecurity(), false) );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}



//************************************************************************************

VerificationStringProcessor::VerificationStringProcessor(  ) : 
_inputStr( NULL ), currentPos( 0 ), tableData( NULL ), beneficiary_index( 1 ), addresses_index( 1 )
{

}

//************************************************************************************
VerificationStringProcessor::~VerificationStringProcessor( ) 
{
   clearTableInfoMap( tableData );
   clearExistingTableMap( );
}
//************************************************************************************
void VerificationStringProcessor::clearExistingTableMap( )
{
   EXISTING_TABLE_MAP_ITER iter= m_ExistingTableMap.begin();

   while( iter != m_ExistingTableMap.end() )
   {
      // delete Data object
      if( (*iter).second )
         delete (*iter).second;
      ++iter;
   }
   m_ExistingTableMap.clear();

   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iterForUpdates = m_ExistingTableForUpdatesMap.begin();

   while( iterForUpdates != m_ExistingTableForUpdatesMap.end() )
   {
      // delete Data object
      delete ( ( *iterForUpdates ).second ) [0];
      delete ( ( *iterForUpdates ).second ) [1];
      delete [] ( (*iterForUpdates).second );
      ++iterForUpdates;
   }
   m_ExistingTableForUpdatesMap.clear();

}
//************************************************************************************
void VerificationStringProcessor::init( DString& inputStr, TableData *verifConfTableData, int NumItem )
{
   _inputStr = &inputStr;
   tableData = verifConfTableData;
   initTableInfoMap( tableData, NumItem );
}
//************************************************************************************
void VerificationStringProcessor::fillFieldMap( FieldMap *_fieldMapInfo, FIELD_MAP& _FieldMap )
{
   for( int i=0; ; i++ )
   {
      if( _fieldMapInfo[i].fieldName != NULL )
         _FieldMap[_fieldMapInfo[i].fieldName] = _fieldMapInfo[i].mapTo;
      else
         break;
   }
}

bool VerificationStringProcessor::Process( BFData *request )
{
   DString Tag, FieldName, Value;

   FIELD_MAP *fieldMap;
   BFData *_data;

   Begin();

   while( NextTagValue( Tag, Value ) )
   {
      if( Tag != NULL_STRING )
      {
         _data = GetData( Tag, FieldName, &fieldMap );

         if( _data )
            setField( _data, fieldMap, FieldName, Value );
      }
   };

   EXISTING_TABLE_MAP_ITER iter= m_ExistingTableMap.begin();


   DString tmp;

   int i=0;

   while( iter != m_ExistingTableMap.end() )
   {
      (*iter).second->setElementValue( I_("UpdType"), UpdType, false, false );

      // if it is entity table, create index
      tmp = (*iter).first;
      if( tmp.find( I_("TRAKENT") ) != DString::npos )
         (*iter).second->setElementValue( I_("Repeating24"), asString( ++i ), false, false );

      request->addRepeat( *(*iter).second );

      // delete Data object
      delete (*iter).second;
      (*iter).second = NULL;
      ++iter;
   }


   request->setElementValue( ifds::RepeatCount, asString( m_ExistingTableMap.size() ), false, false );
   m_ExistingTableMap.clear();
   return(true);   
}

bool VerificationStringProcessor::ProcessUpdates( void )
{
   DString Tag, FieldName, Value;

   FIELD_MAP *fieldMap;
   BFData **_data;

   Begin();

   while( NextTagValue( Tag, Value ) )
   {
      if( Tag != NULL_STRING )
      {
         _data = GetDataForUpdates( Tag, FieldName, &fieldMap );

         if( _data )
            setFieldForUpdates( _data, fieldMap, FieldName, Value );
      }
   };


   return(true);   
}

bool VerificationStringProcessor::NextTagValue( DString& Tag, DString& Value )
{
   int ipos;

   Tag = NULL_STRING;
   Value = NULL_STRING;
   if( (ipos = _inputStr->find(';', currentPos)) != DString::npos )
   {
      Tag.assign( *_inputStr, currentPos, ipos - currentPos);

      currentPos = ++ipos;

      if( (ipos = Tag.find('=')) != DString::npos )
      {
         Value = Tag.right(Tag.length()-ipos-1);
         Tag = Tag.left(ipos);

         if( UpdType == NULL_STRING && Tag == I_("UPDTYPE") )
            UpdType = Value;
      }

      return(true); // maybe still more to come
   }
   else
      return(false); // reach the end
}

// set value to field in request using _FieldMap
void VerificationStringProcessor::setField( BFData* request, FIELD_MAP *_FieldMap, DString& field, DString& value )
{
   FIELD_MAP_ITER iter = _FieldMap->find( field );

   if( iter != _FieldMap->end() )
      request->setElementValue( (*iter).second, value, false, false );
}

void VerificationStringProcessor::setFieldForUpdates( BFData** request, FIELD_MAP *_FieldMap, DString& field, DString& value )
{
   FIELD_MAP_ITER iter = _FieldMap->find( field );

   if( iter != _FieldMap->end() )
   {
/*      if( request[0] && request[0]->exists( (*iter).second ) )
       request[0]->setElementValue( (*iter).second, value, false, false );
      if( request[1] && request[1]->exists( (*iter).second ) )
       request[1]->setElementValue( (*iter).second, value, false, false );*/
      if( request[0] )
         request[0]->setElementValue( (*iter).second, value, true, false );
      if( request[1] )
         request[1]->setElementValue( (*iter).second, value, true, false );
   }
}

void VerificationStringProcessor::AnalyseTag( DString& Tag, DString& FieldName, FIELD_MAP ** Map, 
                                              DString& TableTag, DString& TablePostfix )
{
   int pos;
   TABLT_INFO_MAP_ITER iter= m_TableInfoMap.begin();

   *Map = NULL;
   while( iter != m_TableInfoMap.end() )
   {
      if( (pos = Tag.find(iter->first)) != DString::npos )
      {
         TableTag = iter->first;
         FieldName = Tag.left(pos-1);
         *Map = ((*iter).second )->fieldMap;

         TablePostfix = Tag.right(Tag.length()-pos);
         break;
      }
      ++iter;
   }
}

// get the data where field should be set and which field map it should use
// create Data if necessary
BFData * VerificationStringProcessor::GetData( DString& Tag, DString& FieldName , FIELD_MAP **fieldMap )
{
   DString TableTag, TablePostfix;

   AnalyseTag( Tag, FieldName, fieldMap, TableTag, TablePostfix );

   BFData *_data = NULL;
   if( *fieldMap )
   {
      EXISTING_TABLE_MAP_ITER iter;

      iter = m_ExistingTableMap.find( TablePostfix );
      if( iter != m_ExistingTableMap.end() )
         _data = iter->second;
      else
      {
         if( Tag.find(I_("_LABEL")) == DString::npos ) // exclude label
         {
            _data = new BFData( ifds::DSTC0145_REQRepeat_Record );
            m_ExistingTableMap[TablePostfix] = _data;

            TABLT_INFO_MAP_ITER iter1 = m_TableInfoMap.find( TableTag );

            _data->setElementValue( I_("TableTag"), (iter1->second)->dbTableName, false, false );
         }
      }
   }

   return(_data);
}

BFData ** VerificationStringProcessor::GetDataForUpdates( DString& Tag, DString& FieldName , FIELD_MAP **fieldMap )
{
   DString TableTag, TablePostfix;

   AnalyseTag( Tag, FieldName, fieldMap, TableTag, TablePostfix );

   BFData **_data = NULL;

   if( *fieldMap )
   {
      EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;

      iter = m_ExistingTableForUpdatesMap.find( TablePostfix );
      if( iter != m_ExistingTableForUpdatesMap.end() )
         _data = iter->second;
      else
      {
         if( Tag.find(I_("_LABEL")) == DString::npos ) // exclude label
         {
            _data = new BFData*[2];
            _data[0] = NULL;
            _data[1] = NULL;
/*            if( TablePostfix.find( I_("TRAKSHR") ) != DString::npos )
           _data[0] = new Data( DBR::DSTC0069_VWRepeat_Record );
            else if( TablePostfix.find( I_("TRAKACT") ) != DString::npos )
               _data[0] = new Data( DBR::DSTC0004_VWRepeat_Record );
            else if( TablePostfix.find( I_("TRAKENT") ) != DString::npos )
            {
               _data[0] = new Data( DBR::DSTC0050_VWRepeat_Record );
               _data[1] = new Data( DBR::DSTC0051_VW );
            }
            else if( TablePostfix.find( I_("TRAKADD") ) != DString::npos )
               _data[0] = new Data( DBR::DSTC0043_VWRepeat_Record );
            else if( TablePostfix.find( I_("TRAKTXN") ) != DString::npos )
               _data[0] = new Data( DBR::DSTC0017_VWRepeat_Record );
*/
            if( TablePostfix.find( I_("TRAKSHR") ) != DString::npos )
               _data[0] = new BFData;
            else if( TablePostfix.find( I_("TRAKACT") ) != DString::npos )
               _data[0] = new BFData;
            else if( TablePostfix.find( I_("TRAKENT") ) != DString::npos )
            {
               _data[0] = new BFData;
               _data[1] = new BFData;
            }
            else if( TablePostfix.find( I_("TRAKADD") ) != DString::npos )
               _data[0] = new BFData;
            else if( TablePostfix.find( I_("TRAKTXN") ) != DString::npos )
               _data[0] = new BFData;
            else if( TablePostfix.find( I_("TRAKDIS") ) != DString::npos )
               _data[0] = new BFData;

            m_ExistingTableForUpdatesMap[ TablePostfix ] = _data;
         }
      }
   }

   return(_data);
}

void VerificationStringProcessor::initTableInfoMap( TableData *_TableInfo, int NumItem )
{
   TableInfo *tmpMap;

   for( int i=0; i<NumItem; i++ )
   {
      tmpMap = new TableInfo;

      tmpMap->fieldMap = new FIELD_MAP;

      fillFieldMap( _TableInfo[i].fieldMap, *(tmpMap->fieldMap) );
      tmpMap->dbTableName = _TableInfo[i].dbTableName;

      m_TableInfoMap[_TableInfo[i].tableName] = tmpMap;
   }
}

void VerificationStringProcessor::clearTableInfoMap( TableData *_TableInfo  )
{
   TABLT_INFO_MAP_ITER iter= m_TableInfoMap.begin();

   while( iter != m_TableInfoMap.end() )
   {
      delete iter->second->fieldMap;
      delete iter->second;

      ++iter;
   }

   m_TableInfoMap.clear();
}

void VerificationStringProcessor::getShareholderData( BFData **data )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;

   iter = m_ExistingTableForUpdatesMap.find( I_( "TRAKSHR") );
   if( iter != m_ExistingTableForUpdatesMap.end() )
      *data = ( ( *iter ).second ) [0];
}

void VerificationStringProcessor::getAccountData( BFData **data )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;

   iter = m_ExistingTableForUpdatesMap.find( I_( "TRAKACT") );
   if( iter != m_ExistingTableForUpdatesMap.end() )
      *data = ( ( *iter ).second ) [0];
}

bool VerificationStringProcessor::getEntityData( BFData **data, long type )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;
   bool res = false;

   switch( type )
   {
      case ENTITY_TYPE::ACCOUNT_OWNER_1:
         iter = m_ExistingTableForUpdatesMap.find( I_( "TRAKENT_AO") );
         if( iter != m_ExistingTableForUpdatesMap.end() )
         {
            *data = ( ( *iter ).second ) [0];
            res = true;
         }
         break;
      case ENTITY_TYPE::ACCOUNT_OWNER_2:
         iter = m_ExistingTableForUpdatesMap.find( I_( "TRAKENT_JA") );
         if( iter != m_ExistingTableForUpdatesMap.end() )
         {
            *data = ( ( *iter ).second ) [0];
            res = true;
         }
         break;
      case ENTITY_TYPE::ACCOUNT_BENEFICIARY:
         DString temp( I_( "TRAKENT_BEN_") );
         temp += asString( beneficiary_index++ );
         iter = m_ExistingTableForUpdatesMap.find( temp );
         if( iter != m_ExistingTableForUpdatesMap.end() )
         {
            *data = ( ( *iter ).second ) [0];
            res = true;
         }
         else
            beneficiary_index = 1;
         break;
   }

   return(res);
}

bool VerificationStringProcessor::getAddressData( BFData **data )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;
   bool res = false;

   DString temp( I_( "TRAKADD_") );
   temp += asString( addresses_index++ );
   iter = m_ExistingTableForUpdatesMap.find( temp );
   if( iter != m_ExistingTableForUpdatesMap.end() )
   {
      *data = ( ( *iter ).second ) [0];
      res = true;
   }
   else
      addresses_index = 1;

   return(res);
}

void VerificationStringProcessor::getTradesData( BFData **data )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;

   DString temp( I_( "TRAKTXN") );
   iter = m_ExistingTableForUpdatesMap.find( temp );
   if( iter != m_ExistingTableForUpdatesMap.end() )
      *data = ( ( *iter ).second ) [0];
}

void VerificationStringProcessor::getAccDistributionData( BFData **data )
{
   EXISTING_TABLE_FOR_UPDATES_MAP_ITER iter;

   DString temp( I_( "TRAKDIS") );
   iter = m_ExistingTableForUpdatesMap.find( temp );
   if( iter != m_ExistingTableForUpdatesMap.end() )
      *data = ( ( *iter ).second ) [0];
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/VerificationConf.cpp-arc  $
 // 
 //    Rev 1.30   Nov 14 2004 14:59:16   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.29   Mar 21 2003 18:28:22   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.28   Oct 09 2002 23:55:14   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.27   Aug 29 2002 12:57:02   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.26   22 May 2002 18:30:14   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.25   May 08 2001 13:29:00   FENGYONG
 // fix for etracker 
 // 
 //    Rev 1.24   03 May 2001 14:07:16   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.23   Apr 02 2001 10:46:44   FENGYONG
 // Add remarks and clienttradeId
 // 
 //    Rev 1.22   Mar 29 2001 12:28:06   FENGYONG
 // Add managementstyle and discretionary
 // 
 //    Rev 1.21   Jan 18 2001 16:10:40   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.20   Dec 17 2000 20:24:52   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.19   Dec 06 2000 15:21:36   OLTEANCR
 // modif. ReceiveData
 // 
 //    Rev 1.18   Nov 29 2000 14:27:16   OLTEANCR
 // new data brokering
 // 
 //    Rev 1.17   Nov 01 2000 10:36:14   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.16   Oct 27 2000 16:11:06   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.15   Oct 20 2000 11:13:58   VASILEAD
 // Fixed NASU process
 // 
 //    Rev 1.14   Oct 17 2000 16:17:54   VASILEAD
 // Fixed crash when delete VerificationStringProcessor
 // 
 //    Rev 1.13   Oct 16 2000 16:27:18   VASILEAD
 // Added Shareholder and Account in NASU
 // 
 //    Rev 1.12   Oct 11 2000 11:55:48   VASILEAD
 // Added server updates support
 // 
 //    Rev 1.11   Oct 03 2000 11:19:48   VASILEAD
 // Added NASU server support
 // 
 //    Rev 1.9   Sep 22 2000 14:13:26   YINGZ
 // fix field name spelling problem
 // 
 //    Rev 1.8   Sep 20 2000 13:34:20   YINGZ
 // deal with special field
 // 
 //    Rev 1.7   Sep 15 2000 17:37:34   YINGZ
 // make address, entity repeate work
 // 
 //    Rev 1.6   Sep 14 2000 11:57:46   YINGZ
 // add new field
 // 
 //    Rev 1.5   Aug 10 2000 14:58:10   YINGZ
 // clean up
 // 
 //    Rev 1.4   Aug 09 2000 11:40:12   YINGZ
 // working
 // 
 //    Rev 1.3   Aug 08 2000 13:43:40   YINGZ
 // add VerificationStringProcessor
 // 
 //    Rev 1.2   Aug 03 2000 17:10:28   VASILEAD
 // dummy
 // 
 //    Rev 1.1   Aug 03 2000 14:41:56   VASILEAD
 // Added tracking support to VerifConf
 // 
 //    Rev 1.0   Jul 26 2000 09:37:04   VASILEAD
 // Initial revision.
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:12:34   FENGYONG
// Initial revision.
// 
// Xchgdata issue; create and delete the object in the CBO
// 
*/