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
// ^FILE   : RSPReceiptsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RSPReceiptsList
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

class IFASTCBO_LINKAGE RSPReceiptsList : public MFCanBFCbo, private boost::noncopyable
{
public:

   /**
    * Constructor
    */
   RSPReceiptsList( BFAbstractCBO &parent );

   /**
    * Destructor
    */
   ~RSPReceiptsList();

   /**
    * Initializes the List for view call.  The only required field is Account Number 
    * and Tax Year.
    * @param   const DString& dstrAccountNum - Account Number
    * @param   const DString& dstrTaxYear - Tax Year
    * @param   const DString& dstrTrack - Default "N"
    * @param   const DString& dstrPageName - Default NULL_STRING 
    */
   SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrTaxYear,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   /**
    * Method to retrieve more RSP Receipts
    */
   SEVERITY getMore();

protected:
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:   

   // Data object storing the request data for later use (getMore).
   BFData _requestData;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPReceiptsList.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:53:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Oct 09 2002 23:54:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:53:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:20:08   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:18:22   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   20 Aug 2001 14:07:34   HSUCHIN
//added comments
//
//   Rev 1.1   18 Aug 2001 09:26:06   HSUCHIN
//implemented get More
//
//   Rev 1.0   01 Aug 2001 14:29:46   HSUCHIN
//Initial revision.
*/
