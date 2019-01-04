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
// ^FILE   : Residency.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 9/23/2008
//
// ^CLASS    : Residency
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

class IFASTCBO_LINKAGE Residency : public MFCanBFCbo, private boost::noncopyable
{
public:
   Residency( BFAbstractCBO &parent );
   virtual ~Residency();

   SEVERITY init( const DString& dstrTaxType, 
                  const DString& dstrTaxJurisd, 
                  const BFDataGroupId& idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init( const DString& dstrAccountNum, 
                  const DString& dstrAsOfDate, 
				  const DString& dstrDepositType, 
                  const BFDataGroupId& idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY initForShr ( const DString& dstrShrNum, 
                         const DString& dstrTaxJurisd, 
                         const BFDataGroupId& idDataGroup = BF::HOST, 
                         const DString& dstrTrack = I_("N"),
                         const DString& dstrPageName = NULL_STRING );

   bool isTaxJurisdictionValid();
   bool isDateValid();

protected:
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );


private:
   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Residency.hpp-arc  $
//
//   Rev 1.0   06 Oct 2008 14:28:46   kovacsro
//Initial revision.
 * 
*/