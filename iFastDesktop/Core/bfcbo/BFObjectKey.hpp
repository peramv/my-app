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
// ^FILE   : BFObjectKey.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : BFObjectKey
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include <commonport.h>
#include <dstring.hpp>
#include <bfcbo\bfcboid.hpp>
#include <bfcbo\bfdatagroupid.hpp>

/**
 * This enum contains the posible object activities
 *
 * <pre>
 *@@  OBJ_ACTIVITY_NONE    - existing object. His state is unchanged
 *@@  OBJ_ACTIVITY_DELETED - deleted object
 *@@  OBJ_ACTIVITY_ADDED   - newly added object
 * </pre>
 */
enum BF_OBJ_ACTIVITY 
{
   OBJ_ACTIVITY_NONE,
   OBJ_ACTIVITY_DELETED,
   OBJ_ACTIVITY_ADDED,
   OBJ_ACTIVITY_MODIFIED
};

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This struct describes the key with wich contained objects are indexed inside a CBO
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/07/1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFObjectKey
{
public:
   /**
    *  constructor
    */
   BFObjectKey( const DString& strkey = NULL_STRING,
                const BFDataGroupId& idDataGroup = BF::HOST, 
                BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE, 
                BF_OBJ_TYPE type = OBJ_TYPE_NONE);

   BFObjectKey( const BFObjectKey& rhs );
   BFObjectKey& operator=( const BFObjectKey& rhs );

   bool operator ==(const BFObjectKey &rhs ) const;

   const BFDataGroupId& getDataGroupId() const { return idDataGroup_; }
   void setDataGroupId( const BFDataGroupId& idDataGroup ) { idDataGroup_ = idDataGroup; }

   const BF_OBJ_ACTIVITY& getActivity() const { return activity_; }
   void setActivity( BF_OBJ_ACTIVITY objActivity ) { activity_ = objActivity; }

   const BF_OBJ_TYPE& getType() const { return type_; }
   void setType( const BF_OBJ_TYPE& objType ) { type_ = objType; }

   const DString& getStringKey() const { return dstrKey_; }
   void setStringKey( const DString& dstrKey ) { dstrKey_ = dstrKey; }

private:
   /**
    *  data group of this entry
    */
   BFDataGroupId idDataGroup_;
   /**
    *  activity grup of this entry
    */
   BF_OBJ_ACTIVITY activity_;
   /**
    *  type of this entry
    */
   BF_OBJ_TYPE type_;
   /**
    *  subtype of this entry
    */
   DString dstrKey_;
};

/**
 * This struct contains the less operator for BFObjectKey
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/07/1999 </dd></dl>
 * @version 0.1
 */
struct less_BFObjectKey
{
   /**
    * operator() is used for map ordering
    */
   bool operator() ( const BFObjectKey &a, const BFObjectKey &b ) const
   {
      if( a.getDataGroupId() != b.getDataGroupId() )
      {
         return(a.getDataGroupId() < b.getDataGroupId() );
      }
      if( a.getActivity() != b.getActivity() )
      {
         return(a.getActivity() < b.getActivity() );
      }
      if( a.getType() != b.getType() )
      {
         return( a.getType() < b.getType() );
      }
      if( a.getStringKey() != b.getStringKey() )
      {
         return( a.getStringKey() < b.getStringKey() );
      }
      return( false );
   }
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/BFObjectKey.hpp-arc  $
//
//   Rev 1.13   23 Oct 2008 15:11:06   popescu
//Incident 1154478 - AMS back-date fix
//
//   Rev 1.12   Mar 12 2003 09:09:12   PURDYECH
//Hide public data.
//Create accessor functions for all data
//
//   Rev 1.11   Jan 06 2003 16:41:08   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.10   Nov 27 2002 15:02:10   PURDYECH
//Documentation Changes
//
//   Rev 1.9   Nov 08 2002 09:58:02   PURDYECH
//Added #include of bfcboid.hpp
//Removed BF_OBJ_TYPE (now handled in bfcboid.hpp)
//
//   Rev 1.8   Oct 09 2002 17:40:06   PURDYECH
//New PVCS Database
//
//   Rev 1.7   May 27 2002 09:31:02   YINGBAOL
//Add Settlement
//
//   Rev 1.6   24 May 2002 15:00:44   KOVACSRO
//added Client bank and Fund bank
//
//   Rev 1.5   22 May 2002 18:08:48   PURDYECH
//BFData Implementation
//
//   Rev 1.4   22 Mar 2002 15:11:40   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   Nov 18 2001 11:32:54   YINGBAOL
//Add OBJ_TYPE_ENTITY_ADDRESS
//
//   Rev 1.2   Oct 03 2001 19:20:00   OLTEANCR
//added   OBJ_TYPE_FAST_RSF_UPDATE
//
//   Rev 1.1   Jun 12 2001 11:24:26   MCNABBGL
//session update changes
//
//   Rev 1.0   03 May 2001 14:44:48   SMITHDAV
//Initial revision.
*/