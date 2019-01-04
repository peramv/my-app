#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : WhereUsed.hpp
// ^AUTHOR : 
// ^DATE   : November 19, 2004
//
// ^CLASS    : WhereUSed
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

class IFASTCBO_LINKAGE WhereUsed : public MFCanBFCbo, private boost::noncopyable
{

public:   

   //****************************************************************************
   // Constructor
   //****************************************************************************
   WhereUsed( BFAbstractCBO &parent );

   //****************************************************************************
   // Destructor
   //****************************************************************************
   ~WhereUsed();  

   //****************************************************************************
   //Initializes the CBO
   //@param const BFData& InstData - Data object to attach to WhereUsedList.
   //@returns SEVERITY
   //****************************************************************************   
   SEVERITY init( const DString &entityId, const BFData& InstData );
 
 //****************************************************************************
   //Initializes new object
   //@param const BFDataGroupId& idDataGroup - data group ID
   //@returns SEVERITY
   //****************************************************************************   
  
   SEVERITY initNew(const DString &entityId, const BFDataGroupId& idDataGroup);
protected:
         virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
         virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, long lValidateGroup);
         SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
         SEVERITY WhereUsed::doValidateField( const BFFieldId& idField,	const DString& strValue, const BFDataGroupId& idDataGroup );
private:
         void setAllFieldsReadOnlyforAccountRelated( const BFDataGroupId& idDataGroup );
         void CommInit(const BFData* pData,const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WhereUsed.hpp-arc  $ */
//
//   Rev 1.5   Nov 06 2008 02:08:02   daechach
//PET5517 FN71 Unclaimed Property Phase 2 - Put revision control entry.
// 

