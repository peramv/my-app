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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <commonport.h>
#include <bfproc\command.hpp>
#include "interprocessdata.hpp"

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

// Forward declare
class GenericInterface;
class BFSession;

/**
 * Singleton class which manages the lifetime of modeless process/dialog
 * subclasses.
 *
 * This class manages all modeless process/dialog entities which are in-process.
 * The entity will call destroyMyself when it is being destroyed by the user, 
 * typically when the user presses OK/Cancel.  The container will destroy the
 * object and notify it's parent that the modeless process/dialog has completed.
 * There are also methods provided by which modeless hierarchies of process/
 * dialog entities my be shut down programatically (like in response to end a 
 * call.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/07/98</dd></dl>
 * @version 0.1
 */

class BPBASE_LINKAGE GenericInterfaceContainer
{
public:

   GenericInterfaceContainer();

   virtual ~GenericInterfaceContainer();

   /**
    * This method is used to add a GenericInterface pointer to the map
    * of managed modeless process/dialog subclasses.
    * 
    * @param pGI    A pointer to the modeless object.
    * 
    * @return true if successful, false if failed
    */
   bool add( GenericInterface *pGI );
   /**
    * This method is used to destroy a specific process/dialog and its
    * children.
    * 
    * @param pGI    A pointer to the modeless object to destroy.
    * 
    * @return true if successful, false if failed
    */
   bool destroy( GenericInterface *pGI );
   /**
    * This method is used to destroy everything in the
    * GenericInterfaceContainer for a specific user/work session.
    * 
    * @param bfSession The session for which everything should be destroyed
    * 
    * @return true if successful, false if failed
    */
   bool destroyAll( BFSession *bfSession = NULL );
   /**
    * This method is used to destroy all children and their descendents for a
    * specific object.
    * 
    * @param rpGI   A reference pointer of the modeless object whose children
    *               are to be destroyed.
    * 
    * @return true if successful, false if failed
    */
   bool destroyChildren( GenericInterface *rpGI );

   /**
    * This method is used to destroy all screens opened within screen whose GI is rpGI
    * 
    * @param rpGI   A reference pointer of the modeless object whose children
    *               are to be destroyed.
    */
   void destroyGUIChildren( GenericInterface *rpGI );
   /**
    * This method is used to by an object manager to tell the container
    * to destroy an object.  It should only be used for this in this way.
    * 
    * @param pGI    A pointer to the object to be destroyed.
    * 
    * @return true if successful, false if failed
    */
   bool destroySelf( GenericInterface *pGI );
   /**
    * This method is used to find an existing process/dialog.
    * 
    * @param bfSession the work/user session in which to look for the process/dialog
    * @param strKey    A string reference to the key literal
    * 
    * @return GenericInterface pointer, NULL if not found
    */
   GenericInterface *findGI( BFSession *bfSession, const DString &strKey ) const;
   /**
    * This method finds the number of direct descendents for a specified
    * parent that are currently in the container.
    * 
    * @param rpGIParent A reference pointer to the parent object to check.
    * 
    * @return number of children
    */
   int getChildCount( GenericInterface *rpGIParent );\

   /**
    * This method returns the InterProcessData object used to pass parms and
    * globals.
    * 
    * @return reference pointer to InterProcessData.
    */
   const InterProcessData& getInterProcessData() const
   {
      return(_interProcessData);
   }

   /**
    * This method returns the InterProcessData object used to pass parms and
    * globals.
    * 
    * @return reference pointer to InterProcessData.
    */
   InterProcessData& getInterProcessData()
   {
      return(_interProcessData);
   }

   /**
    * This method determines if a GenericInterface pointer is still valid. This
    * should be used whenever the user has obtained a GenericInterface pointer
    * prior to any usage since the pointer may become invalid at any time.
    * 
    * @param rpGI   A reference pointer to the modeless object to check.
    * 
    * @return true if successful, false if failed
    */
   bool isValid( GenericInterface *rpGI ) const;
   /**
    * This method is used to by an object manager to tell the container
    * to destroy a modeless object.  It should only be used for this in this
    * way.
    * 
    * @param pGI    A pointer to the modeless object to be destroyed.
    * 
    * @return true if successful, false if failed
    */
   bool modelessDestroySelf( GenericInterface *pGI );
   /**
    * Method to invoke refresh on all modal parent's of calling object and all
    * modeless business processes.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return true if successful, call getErrors for errors if false
    */
   bool refresh( GenericInterface *rpGICaller );
   /**
    * Method to invoke refresh on all GUI children of parent.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    */
   void refreshGUIChildren( GenericInterface *rpGICaller );
   GenericInterface * getChild(GenericInterface *rpGIParent, int index );
   bool hasModalGI();

private:
   class GICData
   {
   public:
      bool _bDestroyed;
      GenericInterface *_pGI;

      GICData( GenericInterface *pGI ) :
      _bDestroyed( false ),
      _pGI( pGI )
      {}
   };

   // Class used as key in map
   class GIKey
   {
   public:
      BFSession *_bfSession;
      DString _strCommand;
      bool _bModal;

      GIKey( BFSession *bfSession, const DString &strCommand, bool bModal ) :
      _bfSession( bfSession ),
      _strCommand( strCommand ),
      _bModal( bModal )
      {}
      GIKey( GenericInterface *rpGI );
   };

   // Class used for comparison of key in map
   class less_GIKey
   {
   public:
      bool operator() ( const GIKey &a, const GIKey &b ) const
      {
         if( a._bfSession != b._bfSession )
         {
            return(a._bfSession < b._bfSession);
         }
         else if( a._strCommand != b._strCommand )
         {
            return(a._strCommand < b._strCommand);
         }
         else
         {
            return(a._bModal < b._bModal);
         }
      }
   };

   bool _bAlreadyDestroyingChildren;
   InterProcessData _interProcessData;

   std::map< GIKey, GICData *, less_GIKey > _processes;
   typedef std::map< GIKey, GICData *, less_GIKey >::iterator PROCESS_ITER;
#if _MSC_VER >= 1300
   typedef std::map< GIKey, GICData *, less_GIKey >::const_iterator PROCESS_CONST_ITER;
#else
   typedef std::map< GIKey, GICData *, less_GIKey >::iterator PROCESS_CONST_ITER;
#endif

   void deleteGenericInterface( PROCESS_ITER &iter );

   void destroyChildrenRecursive( GenericInterface *rpGI );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/GenericInterfaceContainer.hpp-arc  $
//
//   Rev 1.15   Oct 22 2004 08:58:20   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.14   May 14 2004 16:13:20   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.13   May 10 2004 15:04:32   SMITHDAV
//Add "getChild" member function to get the a child GI.
 * 
 *    Rev 1.12   Nov 27 2002 15:04:42   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.11   Oct 09 2002 17:40:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.10   22 Mar 2002 15:11:54   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.9   03 May 2001 14:03:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Mar 27 2001 13:58:08   YINGZ
 * add destroyGUIChildren
 * 
 *    Rev 1.7   Oct 26 2000 10:37:04   DT24433
 * Change to hold InterProcessData and userSessionId
 * 
 *    Rev 1.6   May 09 2000 15:36:22   DT24433
 * changed static variable to class member for thread changes
 * 
 *    Rev 1.5   Apr 28 2000 08:16:20   DT24433
 * removed static mutex class member
 * 
 *    Rev 1.4   Apr 07 2000 09:49:54   DT24433
 * removed old versions of getInstance, killInstance, and findGI
 * 
 *    Rev 1.3   Apr 04 2000 14:32:46   DT24433
 * changed to create GIC by userID and added a semaphore
 * 
 *    Rev 1.2   Mar 21 2000 10:44:52   DT24433
 * new methods/signatures for changes in cpp
 * 
 *    Rev 1.1   Feb 15 2000 18:55:00   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Dec 09 1999 11:22:08   DT24433
 * refresh support
 * 
 *    Rev 1.2   Jul 16 1999 12:27:30   POPESCUS
 * Added a method to count the children of a process
 * 
 *    Rev 1.1   Jul 08 1999 10:03:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
