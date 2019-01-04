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
// ^FILE   : ShrFamily.hpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 09-2003
//
// ^CLASS    : ShrFamily
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

class IFASTCBO_LINKAGE ShrFamily : public MFCanBFCbo, private boost::noncopyable
{
public:
   ShrFamily( BFAbstractCBO &parent );
   virtual ~ShrFamily();
   SEVERITY init( const BFData& data );
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY getFamilyName( const DString& dstrFamilyCode, 
                           DString &dstrFamilyName, 
                           const BFDataGroupId& idDataGroup );

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   bool needsCacheRefresh (const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup); 
   SEVERITY familyCodeRelatedChanges( const BFDataGroupId& idDataGroup );
   SEVERITY familyTypeRelatedChanges( const BFDataGroupId& idDataGroup );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFamily.hpp-arc  $
//
//   Rev 1.9   Dec 09 2011 11:42:06   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.8   Nov 21 2011 12:09:08   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.7   Nov 14 2011 20:12:56   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.6   Nov 08 2011 12:04:42   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.5   Nov 14 2004 14:55:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:24:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 21 2003 19:11:44   WINNIE
//add family code validation and display family name if exists
//
//   Rev 1.2   Jan 14 2003 17:40:26   sanchez
// Revision Control Entries
 */