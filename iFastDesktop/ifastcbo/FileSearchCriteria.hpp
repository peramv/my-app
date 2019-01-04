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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FileSearchCriteria.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// ^CLASS    : FileSearchCriteria
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

class IFASTCBO_LINKAGE FileSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

   FileSearchCriteria( BFAbstractCBO &parent );
   virtual ~FileSearchCriteria();

   SEVERITY init(const BFDataGroupId& idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

protected:

   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   
   /**
    * virtual function. It should be overwriten in order to do field validation. It is called by
    * validateField
    * @param idField     - the identifier of the field for which we are doing the validation
    * @param strValue     - the value of the field on which the validation is based on
    * @param idDataGroup - the identifier of the data group for which we are doing the validation
   */
   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
 
private:

	SEVERITY loadNetworkIDValues (const BFDataGroupId &idDataGroup);
   DString getCurrentBusDate();

	//field validations
   SEVERITY validateDateRange(const BFDataGroupId& idDataGroup);
  
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FileSearchCriteria.hpp-arc  $
//
//   Rev 1.0   Feb 24 2005 17:41:18   ZHANGCEL
//Initial revision.
//
*/

