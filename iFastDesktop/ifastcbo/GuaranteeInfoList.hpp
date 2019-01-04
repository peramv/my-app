#pragma once
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeInfoList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// ^CLASS    : GuaranteeInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE GuaranteeInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   GuaranteeInfoList( BFAbstractCBO &parent );
   virtual ~GuaranteeInfoList( void );

   SEVERITY getMore();

   SEVERITY init( const DString& dstrGuarSummRecId,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );


protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );    

private:   
   BFData _requestData;

};

///#endif

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeInfoList.hpp-arc  $
 * 
 *    Rev 1.15   Sep 02 2005 12:10:58   porteanm
 * Incident 393611 - Removed getStrKey() in order to keep the view sorting.
 * 
 *    Rev 1.14   Aug 17 2005 16:29:10   porteanm
 * Incident 351033 - Layout change.
 * 
 *    Rev 1.13   Nov 14 2004 14:43:46   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Mar 21 2003 18:12:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:52:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:20:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:17:20   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   Dec 13 2001 16:26:54   ZHANGCEL
 * Remove function doCreateNewObject()
 * 
 *    Rev 1.6   11 May 2001 12:54:02   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.5   May 11 2001 11:22:12   OLTEANCR
 * unchanged
 * 
 *    Rev 1.4   Jan 18 2001 16:12:08   YINGBAOL
 * add etrack
 * 
 *    Rev 1.3   Nov 06 2000 10:11:48   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.2   Mar 30 2000 15:23:12   ZHANGCEL
 * Modification for getMore
 * 
 *    Rev 1.1   Mar 10 2000 14:52:10   ZHANGCEL
 * Updated
 * 
 *    Rev 1.0   Feb 15 2000 10:59:10   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 28 2000 14:37:12   ZHANGCEL
// Initial revision.
 * 
 *
 */