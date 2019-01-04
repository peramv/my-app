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
// ^FILE   : SysIndex.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 5/1/01
//
// ^CLASS    : SysIndex
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

class IFASTCBO_LINKAGE SysIndex : public MFCanBFCbo, private boost::noncopyable
{
public:
   SysIndex( BFAbstractCBO &parent );
   ~SysIndex();

   SEVERITY init( const BFData& data, bool bBaseDelete = false );
   void markReadOnly ( const BFDataGroupId& idDataGroup );

protected:
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

private:
   DString getNextIndexDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateDateRange( const BFDataGroupId& idDataGroup );   
   SEVERITY validateFrequency( const DString& dstrIndexFreq, const BFDataGroupId& idDataGroup );
   SEVERITY validateIndexDate( const BFDataGroupId& idDataGroup );   
   void defaultFrequency( const BFDataGroupId& idDataGroup, DString& dstrFreq );
   void defaultFrequency( const BFDataGroupId& idDataGroup, int& iFreq);
   int numSysFrequency ( const BFDataGroupId& idDataGroup );   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysIndex.hpp-arc  $
//
//   Rev 1.13   Nov 14 2004 14:56:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Mar 21 2003 18:25:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Oct 09 2002 23:55:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:53:44   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   22 May 2002 18:19:44   PURDYECH
//BFData Implementation
//
//   Rev 1.8   19 Mar 2002 13:18:38   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.7   02 Aug 2001 18:26:52   HSUCHIN
//added function to mark SysIndex readonly
//
//   Rev 1.6   25 Jul 2001 09:09:20   HSUCHIN
//replaced validateStartDate and validateEndDate functions with validateDateRange
//
//   Rev 1.5   11 Jul 2001 15:09:28   HSUCHIN
//change defaultfrequency function
//
//   Rev 1.4   06 Jun 2001 13:38:02   HSUCHIN
//code cleanup and additional business logic added
//
//   Rev 1.3   01 Jun 2001 11:36:20   HSUCHIN
//validate rule changes and bug fix
//
//   Rev 1.2   23 May 2001 12:32:14   HSUCHIN
//validation rules added
//
//   Rev 1.1   11 May 2001 09:31:50   HSUCHIN
//Session management restructuring
//
//   Rev 1.0   03 May 2001 13:42:12   BUZILAMI
//Initial revision.
 * 
*/