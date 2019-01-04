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
//
//******************************************************************************
//
// ^FILE   : WhereUsedList.hpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : September 17, 1999
//
// ^CLASS    : WhereUsedList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

//Forward declarations
class WhereUsed;

class IFASTCBO_LINKAGE WhereUsedList : public MFCanBFCbo, private boost::noncopyable
{
public:
   WhereUsedList( BFAbstractCBO &parent );

   virtual ~WhereUsedList();
   SEVERITY checkDuplicate ( const WhereUsed *pWhereUseToCheck, 
                             const BFDataGroupId &idDataGroup);

   SEVERITY init( const DString& dstrEntityId,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING,
				  const DString& dstrDuplicateCheck = I_("N"),
				  const DString& dstrEntityWhereUseRid = I_( "0" ),
				  const DString& dstrWhereUse = NULL_STRING,
				  const DString& dstrWhereUseCode = NULL_STRING,
				  const DString& dstrEntityType = NULL_STRING,
				  const DString& dstrEffectiveDate = NULL_STRING,
				  const DString& dstrStopDate = NULL_STRING);
   SEVERITY init( const BFData& data );
   void initNew( const DString & entityID, const BFDataGroupId &idDataGroup );
   SEVERITY getMore();
   SEVERITY validateFundSponsor (const BFDataGroupId& idDataGroup);

   void  getFiedByEntityTypeWhereUseCode( 
                          const DString& entityType,
                          const DString& whereUse,    
                          const BFFieldId& idField,
                          DString& strValue,
                          const BFDataGroupId& idDataGroup,
                          bool  lFormatted );
   bool isNetworkSender (const BFDataGroupId& idDataGroup);
   bool isFundSponsor (const BFDataGroupId& idDataGroup);
   bool isNEQEntity (const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
private:
   DString _entityID;
   BFData _requestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WhereUsedList.hpp-arc  $
 * 
 *    Rev 1.21   Jan 10 2011 04:25:56   wutipong
 * IN2261419 - Not able to add Clearing Platform Entity 
 * 
 *    Rev 1.20   Apr 30 2010 11:14:32   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.19   Apr 07 2010 09:41:04   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.18   Nov 20 2006 13:50:50   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.17   Nov 14 2006 16:03:34   jankovii
 * PET FN - Temp checkin by Monica
 * 
 *    Rev 1.16   Jul 21 2006 13:59:50   jankovii
 * PET 2192 FN02 - Dealings-Sender Cut-Off Time.
 * 
 *    Rev 1.15   Nov 28 2005 09:49:54   jankovii
 * PET1228_FN02_ EU Savings Directive Phase Two
 * 
 *    Rev 1.14   Nov 08 2005 16:16:30   jankovii
 * PET1228 - added support for duplicate check.
 * 
 *    Rev 1.13   May 17 2005 17:26:02   Fengyong
 * #Incident 272055 - Add more button to where used screen
 * 
 *    Rev 1.12   Apr 21 2005 13:16:34   yingbaol
 * Incident290503: add new method getFieldbyentitytypewhereuse(....)
 * 
 *    Rev 1.11   Mar 09 2005 16:05:48   yingbaol
 * PET 1171,FN01: EU saving entity update
 * 
 *    Rev 1.10   Mar 01 2005 11:52:38   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.9   Nov 14 2004 14:59:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Mar 21 2003 18:28:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:55:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:54:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 22:22:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   22 May 2002 18:18:26   PURDYECH
 * BFData Implementation
 */
