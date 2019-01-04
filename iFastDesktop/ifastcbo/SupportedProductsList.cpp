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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SupportedProductsList.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : May 2004
//
// ^CLASS    : SupportedProductsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "supportedproductslist.hpp"
#include <ifastdataimpl\dse_dstc0291_req.hpp>
#include <ifastdataimpl\dse_dstc0291_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SUPPORTED_PRODUCTS;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("SupportedProductsList");
}

namespace CND
{
}

namespace PRODUCTS
{
	extern const I_CHAR * const LSIF = I_("LSIF");
	extern const I_CHAR * const SSBAU = I_("SSBAU");
}

//******************************************************************************
SupportedProductsList::SupportedProductsList  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setObjectAsList ();
   setVersionable( false );

}

//******************************************************************************
SupportedProductsList::~SupportedProductsList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY SupportedProductsList::init (
   const DString &dstrTrack, 
   const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData queryData (ifds::DSTC0291_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   AsyncReceiveData (DSTC_REQUEST::SUPPORTED_PRODUCTS, queryData, 
      ifds::DSTC0291_VW, DSTCRequestor (getSecurity (), true));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void SupportedProductsList::buildKey (const DString &productCtrlCode, DString &strKey)
{
   strKey = productCtrlCode;
   strKey.strip ();
   strKey.upperCase ();
}

//******************************************************************************
void SupportedProductsList::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey (data->getElementValue (ifds::ProductCtrlCode), strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//*****************************************************************************
bool SupportedProductsList::isLSIFProductActive ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isLSIFProductActive"));

   return isProductActive (PRODUCTS::LSIF);
}

//*****************************************************************************
bool SupportedProductsList::isSSBAUProductActive ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSSBAUProductActive"));

   return isProductActive (PRODUCTS::SSBAU);
}

//*****************************************************************************
bool SupportedProductsList::isProductActive (const DString &productCtrlCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isProductActive "));

   bool isActive = false;
   DString strKey;

   buildKey (productCtrlCode, strKey);
   
   BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
   
   if (iter.positionByKey (strKey))
   {
      DString active;

      iter.getObject ()->getField (ifds::ActiveCode, active, BF::HOST, false); 
      active.strip ().upperCase ();
      isActive = active == I_("1");
   }
   return isActive;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SupportedProductsList.cpp-arc  $
// 
//    Rev 1.5   Dec 10 2004 14:54:44   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.4   Nov 24 2004 10:19:50   yingbaol
// PET1117:take out version feature untill base fully support it.
// 
//    Rev 1.3   Nov 18 2004 13:28:28   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.2   Nov 14 2004 14:56:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   May 09 2004 20:10:42   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.0   May 06 2004 18:43:38   popescu
// Initial revision.
*/