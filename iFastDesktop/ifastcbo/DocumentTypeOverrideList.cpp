
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
//    Copyright 2003 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : DocumentTypeOverrideList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : April. 17, 2003
//
// ^CLASS    : DocumentTypeOverrideList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0254_req.hpp>
#include <ifastdataimpl\dse_dstc0254_vw.hpp>
#include "mgmtco.hpp"
#include "DocumentTypeOverrideList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DOCUMENT_TYPE_OVERRIDE_LIST;   
}


namespace  
{
   const I_CHAR * const CLASSNAME = I_( "DocumentTypeOverrideList" ); 
   const I_CHAR * const OM = I_( "OM" ); 
   const I_CHAR * const BC = I_( "BC" ); 
   const I_CHAR * const BH = I_( "BH" ); 
   const I_CHAR * const BA = I_( "BA" ); 
   const I_CHAR * const EO = I_( "EO" ); 

}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DocumentType;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBA;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBC;
   extern CLASS_IMPORT const BFTextFieldId BasedOnBH;
   extern CLASS_IMPORT const BFTextFieldId EUSDTaxOption;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//    Field DD Id,         State Flags,            Group Flags 
   { ifds::MiscCode,       BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//*********************************************************************************
DocumentTypeOverrideList::DocumentTypeOverrideList(BFAbstractCBO &parent )
: MFCanBFCbo( parent )
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
DocumentTypeOverrideList::~DocumentTypeOverrideList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//**********************************************************************************

SEVERITY DocumentTypeOverrideList::init(const DString& dstrGroupCode, const DString& dstrTrack,
                                  const DString& dstrPageName  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	m_strGroupCode = dstrGroupCode;
   BFData _requestData(ifds::DSTC0254_REQ);
   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::GroupCode, dstrGroupCode );

   ReceiveData(DSTC_REQUEST::DOCUMENT_TYPE_OVERRIDE_LIST, _requestData, ifds::DSTC0254_VW, 
               DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************************************************
void DocumentTypeOverrideList::getDocumentTypeSubstitute(DString& dstrDocTypeList)
{
   dstrDocTypeList = NULL_STRING;
   DString dstrCode,dstrDes;
	linkSubstituteSet();
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode,dstrCode,BF::HOST,false );
      setFieldNoValidate(ifds::MiscCode,dstrCode,BF::HOST,false );
		getField( ifds::MiscCode,dstrDes,BF::HOST,true );
      ++iter;
      dstrDes.strip();
      dstrCode.strip();
      dstrDocTypeList += dstrCode + I_("=") + dstrDes + I_(";");    
   }
	setUpdatedFlag( ifds::MiscCode, BF::HOST, false ); // clear update flag

}

//***********************************************************************************
void  DocumentTypeOverrideList::linkSubstituteSet()
{
	if(m_strGroupCode == OM )
	{
		setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::DocumentType );	
	}
	else if( m_strGroupCode == BA )
	{
		setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBA );	
	}
	else if( m_strGroupCode == BH )
	{
	   setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBH);	
	}
	else if( m_strGroupCode == BC )
	{
	   setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::BasedOnBC );	
	}
   else if(m_strGroupCode == EO )
   {
	   setFieldAllSubstituteValues( ifds::MiscCode, BF::HOST,ifds::EUSDTaxOption );	
   }
}
//*******************************************************************************
// build substitution list based on category
// iMatchType: 0------equal
//             1------less
//             2------less equal
//             3------great
//             4------great equal
//
void DocumentTypeOverrideList::getDocumentTypeSubstituteByCategory(
                               DString& dstrDocTypeList,
                               int iMatchType,
                               DString category                               
                               )
{
   dstrDocTypeList = NULL_STRING;
   DString dstrCode,dstrDes,dbCategory;
	linkSubstituteSet();
   category.stripAll();
   int iCategory = category.asInteger(); 
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::MiscCode,dstrCode,BF::HOST,false );
      iter.getObject()->getField( ifds::MiscCategory,dbCategory,BF::HOST,false );
      int idbCat = dbCategory.stripAll().asInteger();
      if (iMatchType == 0)
      {
         if( idbCat != iCategory ) // does not equal skip
          {
            ++iter;
            continue;
          }     
      }
      else if ( iMatchType == 1 )
      {
         if( idbCat >= iCategory ) // not less skip
          {
            ++iter;
            continue;
          }          
      }

      else if ( iMatchType == 2 )
      {
         if( idbCat > iCategory ) // not less equal skip
          {
            ++iter;
            continue;
          }          
      }
      else if ( iMatchType == 3 )
      {
         if( idbCat <= iCategory ) // not great  skip
          {
            ++iter;
            continue;
          }          
      }
      else if ( iMatchType == 4 )
      {
         if( idbCat < iCategory ) // not great or equal  skip
          {
            ++iter;
            continue;
          }          
      }
	  if ( !bfutil::isServerContext() )
	  {
		setFieldNoValidate(ifds::MiscCode,dstrCode,BF::HOST,false );
		getField( ifds::MiscCode,dstrDes,BF::HOST,true );
	  }
	  else
		  dstrDes = dstrCode;
	  
      ++iter;
      dstrDes.strip();
      dstrCode.strip();
      dstrDocTypeList += dstrCode + I_("=") + dstrDes + I_(";");    
   }
	setUpdatedFlag( ifds::MiscCode, BF::HOST, false ); // clear update flag

}







//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DocumentTypeOverrideList.cpp-arc  $
// 
//    Rev 1.6   Nov 10 2005 11:22:50   fengyong
// Incident 414773 BPServer internal error fix 
// 
//    Rev 1.5   Mar 01 2005 11:53:00   yingbaol
// PET1137,FN01: EU saving entity update
// 
//    Rev 1.4   Nov 24 2004 10:17:50   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.3   Nov 18 2004 13:28:00   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.2   Nov 14 2004 14:31:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   May 14 2003 14:03:12   YINGBAOL
// enhancement Misc infor
// 
//    Rev 1.0   Apr 21 2003 09:51:10   YINGBAOL
// Initial revision.
// 




  */