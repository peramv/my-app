
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
// ^FILE   : DocumentTypeList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Semptember. 11, 2002
//
// ^CLASS    : DocumentTypeList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0215_req.hpp>
#include <ifastdataimpl\dse_dstc0215_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "DocumentTypeList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_MAIL_DELIVER_OPTION;   
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DeliveryOption;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryMethods;
}


namespace  
{
   const I_CHAR * const CLASSNAME = I_( "DocumentTypeList" );  
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//    Field DD Id,         State Flags,            Group Flags 
   { ifds::DeliveryOption,       BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//*********************************************************************************
DocumentTypeList::DocumentTypeList(BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( false );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//*********************************************************************************
DocumentTypeList::~DocumentTypeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//**********************************************************************************

SEVERITY DocumentTypeList::init(  const DString& dstrTrack,
                                  const DString& dstrPageName  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData _requestData(ifds::DSTC0215_REQ);
   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ENTITY_MAIL_DELIVER_OPTION, _requestData, ifds::DSTC0215_VW, 
               DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
void  DocumentTypeList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrDocType;
   dstrDocType = data->getElementValue( I_( "DocumentType" ) );
   dstrDocType.strip();
   strKey = dstrDocType;
}

//***********************************************************************************
void DocumentTypeList::getDocumentTypeSubstitute(DString& dstrDocTypeList,bool bEntity)
{
   dstrDocTypeList = NULL_STRING;
   DString dstrCode,dstrDes;
   DString dstrShareHolderOnly = I_("12,13,14,15,16");

   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::DocumentType,dstrCode,BF::HOST,false );
      iter.getObject()->getField( ifds::DocumentType,dstrDes,BF::HOST,true );
      ++iter;
      dstrDes.strip();
      dstrCode.strip();
      if( bEntity )
      {
         if( dstrShareHolderOnly.find(dstrCode) != DString::npos )
            continue;
      }
      dstrDocTypeList += dstrCode + I_("=") + dstrDes + I_(";");    
   }
}
//************************************************************************************
void DocumentTypeList::getDeliverySubstitute(DString& dstrDocType, DString& dstrDelList,DString& dstrDeliveryMethod )
{
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   iter.positionByKey(dstrDocType);
   DString dstrCode,dstrDes,dstrCodeList;


   dstrDelList = NULL_STRING;
   if( !iter.end() )
   {
      iter.getObject()->getField(ifds::DeliveryList,dstrCodeList,BF::HOST,false);
      dstrCodeList.strip(); 
   }
   BFProperties* pBFP  = getFieldProperties(ifds::DeliveryOption,BF::HOST );
   assert(pBFP);
   if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");
   int iPos =  dstrCodeList.find_first_of(I_(",") );
   while( iPos != DString::npos )
   {
      iPos =  dstrCodeList.find_first_of(I_(",") );
      if( iPos == DString::npos ) break;
      dstrCode = dstrCodeList.left(iPos);
      dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
      if( dstrDeliveryMethod.find( dstrCode ) == DString::npos ) continue;
      dstrDes = dstrCode;
      pBFP->formatValue(ifds::DeliveryOption,dstrDes,true);
      dstrDelList += dstrCode + I_("=") + dstrDes + I_(";");
   };
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DocumentTypeList.cpp-arc  $
// 
//    Rev 1.10   Dec 10 2004 14:34:40   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.9   Nov 24 2004 10:17:48   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.8   Nov 18 2004 13:27:58   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.7   Nov 14 2004 14:31:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:03:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Mar 10 2003 11:39:16   YINGBAOL
// SemiAnnual is only applicable to mailing for shareholder
// 
//    Rev 1.4   Oct 09 2002 23:54:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Oct 08 2002 11:46:18   YINGBAOL
// change getDocument Type to distinguish shareholder and entity
// 
//    Rev 1.2   Sep 26 2002 09:54:10   YINGBAOL
// fielter substitute list according to view 149
// 
//    Rev 1.1   Sep 23 2002 15:21:12   YINGBAOL
// fix
 * 



  */




