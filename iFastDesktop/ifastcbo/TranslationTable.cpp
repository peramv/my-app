
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
// ^FILE   : TranslationTable.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TranslationTable 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0254_req.hpp>
#include <ifastdataimpl\dse_dstc0254_vw.hpp>
#include "mgmtco.hpp"
#include "TranslationTable.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MISC_INFO_TRANSLATION_TABLE;   
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "TranslationTable" ); 
}

// TransTable constants identifier names and codes come 
// from the Translation Table (search by Group Code 00)
namespace TransTable
{
   const I_CHAR * const EntityCategory = I_( "EA" );
   const I_CHAR * const FeeParmTrailerFeeBasedOn = I_( "BA" );
   const I_CHAR * const FeeParmSplitCommissionBasedOn = I_( "BC" ); 
   const I_CHAR * const FeeParmManagementFeeBasedOn = I_( "BH" ); 
   const I_CHAR * const FeeParmGuaranteeFeeBasedOn = I_( "BW" ); 
   const I_CHAR * const AllowableDocumentTypeMailingsOverride = I_( "OM" ); 
   const I_CHAR * const RiskLevelCategory = I_( "RK" ); 
   const I_CHAR * const SuppressionReasonCode = I_( "PRC" ); 
   const I_CHAR * const RegClassification     = I_( "FFI" ); 
   const I_CHAR * const DocIdMethod     = I_( "IDM" ); 
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DocumentType;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBA;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBC;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBH;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBW;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClass;
   extern CLASS_IMPORT const BFTextFieldId RiskLevel;
   extern CLASS_IMPORT const BFTextFieldId SuppressionReasonCode;
   extern CLASS_IMPORT const BFTextFieldId FFIClass;
   extern CLASS_IMPORT const BFTextFieldId IDMethod;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//    Field DD Id,         State Flags,            Group Flags 
   { ifds::MiscCode,       BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************

TranslationTable::TranslationTable(BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _pRequestData(nullptr)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   //setVersionable( false );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//*********************************************************************************

TranslationTable::~TranslationTable()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if(_pRequestData != nullptr)
   {
      delete _pRequestData;
      _pRequestData = nullptr;
   }
}

//**********************************************************************************

SEVERITY TranslationTable::init(const DString& dstrGroupCode, const DString& dstrTrack,
                                  const DString& dstrPageName  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_dstrGroupCode = dstrGroupCode;
   DString mgmtCoIdOut;

   _pRequestData = new BFData(ifds::DSTC0254_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::GroupCode, dstrGroupCode );

   ReceiveData(DSTC_REQUEST::MISC_INFO_TRANSLATION_TABLE, *_pRequestData, ifds::DSTC0254_VW, 
               DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************

void TranslationTable::getSubstitutionList(DString& dstrSubstitutionList, bool bRequireViewDesc)
{
   dstrSubstitutionList = NULL_STRING;
   DString dstrCode, dstrDescription;
   linkSubstituteSet();
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

   if(!bRequireViewDesc)//MT53X
   {
      while( !iter.end() )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );

         if ( !bfutil::isServerContext() )
         {
            setFieldNoValidate(ifds::MiscCode, dstrCode, BF::HOST, false );
            getField( ifds::MiscCode, dstrDescription, BF::HOST, true );
         }
         else
         {
            dstrDescription = dstrCode;
         }
         ++iter;
         dstrDescription.strip();
         dstrCode.strip();
         dstrSubstitutionList += dstrCode + I_("=") + dstrDescription + I_(";");    
      }
   }
   else //get Desc
   {
      while( !iter.end() )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         iter.getObject()->getField( ifds::MiscDesc, dstrDescription, BF::HOST, false );
         ++iter;
         dstrDescription.strip();
         dstrCode.strip();
         dstrSubstitutionList +=  dstrCode + I_("=") + dstrDescription + I_(";") ;  
      }
   }

   setUpdatedFlag( ifds::MiscCode, BF::HOST, false ); // clear update flag
}

//***********************************************************************************

void TranslationTable::getSubstitutionListByCodeAndDescription (DString& dstrSubstitutionList)
{
   dstrSubstitutionList = NULL_STRING;
   DString dstrCode, dstrDescription;
   linkSubstituteSet();

   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
      iter.getObject()->getField( ifds::MiscDesc, dstrDescription, BF::HOST, false );

      ++iter;

      dstrDescription.strip();
      dstrCode.strip();
      dstrSubstitutionList += dstrCode + I_("=") + dstrCode + I_(" - ") + dstrDescription + I_(";");    
   }

   setUpdatedFlag( ifds::MiscCode, BF::HOST, false ); // clear update flag
}

//***********************************************************************************

void TranslationTable::getSubstitutionListByDescription(DString& dstrSubstitutionList)
{
   dstrSubstitutionList = NULL_STRING;
   DString dstrDescription;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscDesc, dstrDescription, BF::HOST, false );
      ++iter;
      dstrDescription.strip();
      dstrSubstitutionList += dstrDescription + I_("=") + dstrDescription + I_(";");    
   }
}

//***********************************************************************************

void  TranslationTable::linkSubstituteSet()
{
   if(m_dstrGroupCode == TransTable::AllowableDocumentTypeMailingsOverride )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::DocumentType );	
   }
   else if( m_dstrGroupCode == TransTable::FeeParmTrailerFeeBasedOn )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBA );	
   }
   else if( m_dstrGroupCode == TransTable::FeeParmManagementFeeBasedOn )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBH);	
   }
   else if( m_dstrGroupCode == TransTable::FeeParmSplitCommissionBasedOn )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBC );	
   }
   else if( m_dstrGroupCode == TransTable::FeeParmGuaranteeFeeBasedOn )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBW );	
   }		
   else if( m_dstrGroupCode == TransTable::EntityCategory )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::EmployeeClass );	
   }
   else if( m_dstrGroupCode == TransTable::RiskLevelCategory )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST, ifds::RiskLevel );	
   }
   else if( m_dstrGroupCode == TransTable::SuppressionReasonCode )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST, ifds::SuppressionReasonCode );	
   }
   else if( m_dstrGroupCode == TransTable::RegClassification )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST, ifds::FFIClass );	
   }
   else if( m_dstrGroupCode == TransTable::DocIdMethod )
   {
      setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST, ifds::IDMethod );	
   }
}

//***********************************************************************************

void TranslationTable::getCategory(const DString &dstrCode, DString &dstrCategory )
{
   DString dstrMiscCode;
   dstrCategory = NULL_STRING;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode, dstrMiscCode, BF::HOST, false );
      if( dstrCode == dstrMiscCode )
      {
         iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
         break;
      }
      ++iter;
   }
}
//***********************************************************************************
void TranslationTable::getAdminFeeRedCodeSubList(const DString & strRedCodesByTaxTypeList,DString& dstrAdminFeeRedCodeSubList)
{
   dstrAdminFeeRedCodeSubList = NULL_STRING;
   DString dstrCode, dstrDescription, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
      if(dstrCategory.stripAll().upperCase() == I_("AF") || dstrCategory.stripAll().upperCase() == I_("AFS") )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         if (DSTCommonFunctions::codeInList (dstrCode.strip(), strRedCodesByTaxTypeList))
            dstrAdminFeeRedCodeSubList += dstrCode + I_(",");     
      }
      ++iter;
   }
}

//***********************************************************************************
void TranslationTable::getRedCodeSubList(const DString & strRedCodesByTaxTypeList, DString& dstrRedCodeSubList)
{
	dstrRedCodeSubList = NULL_STRING;
   DString dstrCode, dstrDescription, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
      if(dstrCategory.stripAll().upperCase() == NULL_STRING )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         dstrCode.upperCase ();

         if (DSTCommonFunctions::codeInList (dstrCode.strip(), strRedCodesByTaxTypeList))
            dstrRedCodeSubList += dstrCode + I_(","); 
      }
      ++iter;
   }
}

//***********************************************************************************
void TranslationTable::getPurchaseSrcOfFundCodeList( DString &dstrPurchaseSrcOfFundCodeList )													 
{
   dstrPurchaseSrcOfFundCodeList = NULL_STRING;
   DString dstrCode, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
      if( dstrCategory.stripAll().upperCase() == I_( "10" ) )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         dstrPurchaseSrcOfFundCodeList += dstrCode + I_(","); 
      }
      ++iter;
   }
}

//***********************************************************************************
void TranslationTable::getRedemptionSrcOfFundCodeList( DString &dstrRedemptionSrcOfFundCodeList )													 
{
   dstrRedemptionSrcOfFundCodeList = NULL_STRING;
   DString dstrCode, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
      if( dstrCategory.stripAll().upperCase() == I_( "20" ) )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         dstrRedemptionSrcOfFundCodeList += dstrCode + I_(","); 
      }
      ++iter;
   }
}

//***********************************************************************************
void TranslationTable::getTransferSrcOfFundCodeList( DString &dstrTransferSrcOfFundCodeList )													 
{
   dstrTransferSrcOfFundCodeList = NULL_STRING;
   DString dstrCode, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, dstrCategory, BF::HOST, false );
      if( dstrCategory.stripAll().upperCase() == I_( "30" ) )
      {
         iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
         dstrTransferSrcOfFundCodeList += dstrCode + I_(","); 
      }
      ++iter;
   }
}
//***********************************************************************************
void TranslationTable::getDescByCode( const DString &dstrCode, 
                                      DString &dstrDesc )
{//P0186486FN09 - Employee and Agent Account Gap#8A
   dstrDesc = NULL_STRING;
   DString miscCode;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode, miscCode, BF::HOST, false );

      if(miscCode.stripAll().upperCase() == dstrCode )
      {
         iter.getObject()->getField( ifds::MiscDesc, dstrDesc, BF::HOST, false );
         break;
      }

      ++iter;
   }
}

//***********************************************************************************
bool TranslationTable::isCodeInCategory( const DString &dstrCode, const DString &dstrCategory )													 
{ //P0186486_FN15_The Source of Funds
   bool ret(false);
   DString miscCode, miscCategory;
   
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCategory, miscCategory, BF::HOST, false );
      if( dstrCategory == miscCategory.stripAll().upperCase() )
      {
         iter.getObject()->getField( ifds::MiscCode, miscCode, BF::HOST, false );
         if( dstrCode == miscCode.stripAll().upperCase() )
         {
            ret = true;
            break;
         }
      }
      ++iter;
   }
   
   return ret;
}

//***********************************************************************************
void TranslationTable::getCodeList( DString &dstrCodeList )
{
   dstrCodeList = NULL_STRING;
   DString dstrCode, dstrCategory;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode, dstrCode, BF::HOST, false );
      dstrCodeList += dstrCode + I_(","); 
      ++iter;
   }
}

//******************************************************************************
SEVERITY TranslationTable::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData(DSTC_REQUEST::MISC_INFO_TRANSLATION_TABLE, *_pRequestData, ifds::DSTC0254_VW, DSTCRequestor(getSecurity(), false ));
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TranslationTable.cpp-arc  $
// 
//    Rev 1.13   Apr 20 2012 03:24:12   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.12   Apr 08 2012 22:40:44   panatcha
// P0186486FN09 - Employee and Agent Account Gap#8A
// 
//    Rev 1.11   Aug 16 2010 06:16:16   panatcha
// P0172931_FN01_MT53X_Entity Creation
// 
//    Rev 1.10   Oct 23 2009 10:45:02   jankovii
// IN 1873069 - R95 P0164824 Based On Field on shows 0 and 1 in the Fee Parameter Screen.
// 
//    Rev 1.9   Nov 26 2007 11:01:04   jankovii
// PET 5685 FN25 - Age 71
// 
//    Rev 1.8   Jun 26 2006 17:51:04   porteanm
// PET2102 FN04 - BasedOnBW.
// 
//    Rev 1.7   Nov 10 2005 11:24:52   fengyong
// Incident 414773 - BPServer internal error fix
// 
//    Rev 1.6   May 02 2005 11:48:26   porteanm
// Incident 290690 - Source Of Fund.
// 
//    Rev 1.5   Nov 24 2004 10:20:00   yingbaol
// PET1117:take out version feature untill base fully support it.
// 
//    Rev 1.4   Nov 18 2004 13:28:40   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.3   Nov 14 2004 14:58:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Sep 09 2004 10:10:06   ZHANGCEL
// PET1094_FN8 -- AdminFee related changes
// 
//    Rev 1.1   Oct 01 2003 13:22:14   HERNANDO
// Modified TranslationTable to include support for Employee Class.
*/