#pragma once
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : VerificationConf.hpp
// ^AUTHOR : Adrian Vasile/ Zijian 
// ^DATE   : July 19, 2000
//
// ^CLASS  : VerificationConf
// ^PARENT : MFCanCbo
//
// ^CLASS DESCRIPTION :
//    Implements View 145.
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace ENTITY_TYPE
{
   extern IFASTCBO_LINKAGE const long ACCOUNT_OWNER_1;
   extern IFASTCBO_LINKAGE const long ACCOUNT_OWNER_2;
   extern IFASTCBO_LINKAGE const long ACCOUNT_BENEFICIARY;
}

struct FieldMap
{
   const I_CHAR *fieldName, *mapTo;
};

struct TableData
{
   const I_CHAR *tableName, *dbTableName;
   FieldMap *fieldMap;
};



typedef std::map< DString, DString >    FIELD_MAP;
typedef FIELD_MAP::iterator             FIELD_MAP_ITER;


typedef std::map< DString, BFData* >    EXISTING_TABLT_MAP;
typedef std::map< DString, BFData** >   EXISTING_TABLT_FOR_UPDATES_MAP;
typedef EXISTING_TABLT_MAP::iterator   EXISTING_TABLE_MAP_ITER;
typedef EXISTING_TABLT_FOR_UPDATES_MAP::iterator   EXISTING_TABLE_FOR_UPDATES_MAP_ITER;

struct TableInfo
{
   const I_CHAR *dbTableName;
   FIELD_MAP* fieldMap;
};

typedef std::map< const DString, TableInfo* >   TABLE_INFO_MAP;
typedef TABLE_INFO_MAP::iterator             TABLT_INFO_MAP_ITER;

class VerificationStringProcessor
{
public:
   VerificationStringProcessor( );
   virtual ~VerificationStringProcessor( );

   void init( DString& inputStr, TableData *verifConfTableData, int NumItem );
   bool Process( BFData *request );
   bool ProcessUpdates( );
   void getShareholderData( BFData **data );
   void getAccountData( BFData **data );
   bool getEntityData( BFData **data, long type = ENTITY_TYPE::ACCOUNT_OWNER_1 );
   bool getAddressData( BFData **data );
   void getTradesData( BFData **data );
   void getAccDistributionData( BFData **data );

private:
   DString *_inputStr;
   TableData *tableData;
   DString UpdType;
   int currentPos;
   int beneficiary_index;
   int addresses_index;


   TABLE_INFO_MAP m_TableInfoMap;
   EXISTING_TABLT_MAP m_ExistingTableMap;
   EXISTING_TABLT_FOR_UPDATES_MAP m_ExistingTableForUpdatesMap;

   void initTableInfoMap( TableData *_TableInfo, int NumItem );
   void clearTableInfoMap( TableData *_TableInfo  );
   void clearExistingTableMap();

   void fillFieldMap( FieldMap *_fieldMapInfo, FIELD_MAP& _FieldMap );
   void setField( BFData* request, FIELD_MAP * _FieldMap, DString& field, DString& value );
   void setFieldForUpdates( BFData** request, FIELD_MAP * _FieldMap, DString& field, DString& value );

   void Begin()
   {
      currentPos = 0;
   };

   bool NextTagValue( DString& Tag, DString& Value );

   void AnalyseTag( DString& Tag, DString& FieldName, FIELD_MAP ** Map, DString& TableTag, DString& TablePostfix );
   BFData * GetData( DString& Tag, DString& FieldName, FIELD_MAP **fieldMap );
   BFData ** GetDataForUpdates( DString& Tag, DString& FieldName, FIELD_MAP **fieldMap );
};

class IFASTCBO_LINKAGE VerificationConf : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   VerificationConf( BFAbstractCBO &parent );
   virtual ~VerificationConf();

   // Initialize function
   SEVERITY init( DString& param, 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );


private:
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/VerificationConf.hpp-arc  $
//
//   Rev 1.19   Nov 14 2004 14:59:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.18   Mar 21 2003 18:28:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.17   Oct 09 2002 23:55:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.16   Aug 29 2002 12:54:02   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.15   22 May 2002 18:18:22   PURDYECH
//BFData Implementation
//
