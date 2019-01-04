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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : PayToEntityList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : PayToEntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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
class PayToEntity;

class IFASTCBO_LINKAGE PayToEntityList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   PayToEntityList( BFAbstractCBO &parent );
   virtual ~PayToEntityList();

   // Initialize function
   SEVERITY init( const DString &dstrBrokerCode = NULL_STRING,
		            const DString &dstrSearchTypeMgmt = NULL_STRING,
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString &dstrTrack = I_("N"), 
						const DString &dstrPageName = NULL_STRING);
   SEVERITY checkDuplicate (const PayToEntity *pPayToEntityToCheck, 
                            const BFDataGroupId &idDataGroup,
                            bool bDuplicateError = true);
   SEVERITY getMore();
protected:
   SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, 
                               const BFDataGroupId& idDataGroup);
//   virtual void getStrKey (DString &strKey, const BFData *data);
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, 
                           long lValidateGroup);
private:
/*   void buildKey ( DString& dstrKey, 
                   const DString &dstrBrokerCode, 
                   const DString &dstrPayFor, 
                   const DString &dstrPayToEntity,
                   const DString &dstrPayToRid);
*/
   BFData *_pRequestData;
	DString _searchType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PayToEntityList.hpp-arc  $
//
//   Rev 1.6   Sep 07 2006 21:38:00   popescu
//STP 2192/02
//
//   Rev 1.5   Jul 27 2006 18:02:22   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.4   Nov 14 2004 14:50:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Aug 07 2003 14:57:54   popescu
//doValidateAll, checks whther there are payment instrucitons records set-up for a pay to entity record
//
//   Rev 1.2   Jul 10 2003 22:21:22   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.1   Jul 01 2003 18:08:04   popescu
//Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
//
//   Rev 1.0   Jun 27 2003 18:16:52   popescu
//Initial revision.
//
 */
