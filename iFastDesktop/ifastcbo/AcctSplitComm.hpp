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
// ^FILE   : AcctSplitComm.hpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
// ^CLASS    : AcctSplitComm
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

class AcctSplitCommRepList;

class IFASTCBO_LINKAGE AcctSplitComm : public MFCanBFCbo, private boost::noncopyable
{
public:

   /**
    * Constructor
    * @param   BFAbstractCBO &parent - Pointer to the calling class.
    */
   AcctSplitComm( BFAbstractCBO &parent );

   /**
    * Destructor
    */
   ~AcctSplitComm();

   /**
    * Initializes the CBO based on the data object passed in.
    * @param   const Data& data - data passed in from the list class
    * @param   bool bBaseDelete - flag to determine who deletes the CBO
    * @return  SEVERITY if view call failed, NO_CONDITION if view passed.
    */
   SEVERITY init( DString& dstrEffectiveDate,
                  DString& dstrStopDate,
                  const BFData& acctSplitCommData,
                  const BFData& allData, 
                  bool bBaseDelete = false ); 

   SEVERITY getAcctSplitCommRepList ( AcctSplitCommRepList*& pAcctSplitCommRepList, 
                                      const BFDataGroupId& idDataGroup );

   void set9999StopDate (const BFDataGroupId& idDataGroup);

protected:

   SEVERITY doValidateField( const BFFieldId& idField, 
                             const DString& strValue, 
                             const BFDataGroupId& idDataGroup );

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
                                   const BFDataGroupId& idDataGroup );

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:

   void allFieldsReadOnly( bool benable, const BFDataGroupId& idDataGroup );
   void validateDateRange (const BFDataGroupId& idDataGroup);

   AcctSplitComm* _pLastActiveAcctSplitComm;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitComm.hpp-arc  $
//
//   Rev 1.8   Mar 21 2003 17:56:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   Aug 08 2002 15:05:30   HSUCHIN
//added set9999StopDate and validateDateRange functions.
//
//   Rev 1.4   22 May 2002 18:22:00   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:14:54   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   16 Nov 2001 16:31:20   HSUCHIN
//bug fix for stop date of previous active record
//
//   Rev 1.1   29 Aug 2001 16:11:30   HSUCHIN
//added enhancements and validation
//
//   Rev 1.0   23 Aug 2001 14:51:38   HSUCHIN
//Initial revision.
*/
