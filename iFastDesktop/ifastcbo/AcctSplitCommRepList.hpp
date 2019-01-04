#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommRepList.hpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
// ^CLASS    : AcctSplitCommRepList
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

class IFASTCBO_LINKAGE AcctSplitCommRepList : public MFCanBFCbo, private boost::noncopyable
{
public:

   AcctSplitCommRepList( BFAbstractCBO &parent );
   ~AcctSplitCommRepList();   

   /**
    * Initializes the List for view call.  The only required field is Account Number
    * @param   const DString& dstrAccountNum - Account Number
    * @param   const DString& dstrTrack - Default "N"
    * @param   const DString& dstrPageName - Default NULL_STRING 
    * @return  SEVERITY if view call failed, NO_CONDITION if view passed.
    */
   SEVERITY init( const DString& dstrEffectiveDate,
                  const DString& dstrStopDate,
                  const BFData& allData );

   void setCBOFields ( const BFFieldId& idField, 
                       const DString& dstrValue, 
                       const BFDataGroupId& idDataGroup );

   DString getTotalRenunciation( const BFDataGroupId& idDataGroup );

protected:

   /**
     * virtual function. Should be overwritten in order to do special processing on new list element creation
     * @param pBase         - here will be filled in the new object
     * @param strKey        - here will be filled in string key
     * @param idDataGroup  - the identifier of the data group with which we want to add a new object
    */
   virtual SEVERITY doCreateNewObject(BFCBO*& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY validateMultipleFundServCommReps(const BFDataGroupId& idDataGroup);

private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommRepList.hpp-arc  $
//
//   Rev 1.8   Mar 21 2003 17:56:18   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:21:50   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:14:56   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   25 Sep 2001 15:10:52   HSUCHIN
//changed to way renunciation total is calculated
//
//   Rev 1.2   03 Sep 2001 13:25:40   HSUCHIN
//added dovalidateall
//
//   Rev 1.1   29 Aug 2001 16:11:38   HSUCHIN
//added enhancements and validation
//
//   Rev 1.0   23 Aug 2001 14:51:42   HSUCHIN
//Initial revision.
*/
