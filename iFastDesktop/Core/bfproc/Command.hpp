#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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

#include <bfproc\commandenum.h>
#include <conditionmanager.hpp>
#include <string>
#include <bfproc\commandtraits.hpp>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is used to represent a command.
 *
 * This class is created by the CommandDispatcher when it performs a lookup on
 * the command string by some mechanism (currently the Command constructor does
 * a look up in internal memory, but this should change) and filled in with
 * whatever information is available.  The Command is passed on to the 
 * sub-dispatchers and ultimately ends up contained in the process/dialog subclass
 * which is created to handle the command.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/14/98</dd></dl>
 * @version 0.1
 */

class BPBASE_LINKAGE Command
{
public:
   /**
     * Default constructor.
     */
   Command();
   /**
     * Copy constructor.
     * @param cmd - A reference to the command to copy.
     */
   Command( const Command &cmd );

   Command( const CommandTraits& traits );

   virtual ~Command();

   /**
     * Can this command be run modally?
     * @returns bool - true = yes, false = no
     */
   bool canRunModal() const;
   /**
     * Can this command be run modelessly?
     * @returns bool - true = yes, false = no
     */
   bool canRunModeless() const;
   /**
     * Get the key for this command.
     * @returns reference to string with key value
     */
   const DString &getKey() const
   {  //  What is the makeup of this key ?????  command name + something if multiples allowed?
      return(_strKey);
   }
   /**
     * Use this method to determine the number of objects per user session 
     * allowed for this command.
     * @returns max count of objects per user session allowed
     */
   int getMaxPerUserSession() const
   {
      return(_maxPerUserSession);
   }
   /**
     * Use this method to determine the number of objects per work session
     * allowed for this command.
     * @returns max count of objects per work session allowed
     */
   int getMaxPerWorkSession() const
   {
      return(_maxPerWorkSession);
   }
   /**
     * Get the unique ID associated with this command.
     * @returns an integer ID.
     */
   int getId() const
   {
      return(_id);
   }
   /**
     * Get the string name of this command.
     * @returns a reference to a string that identifies the command.
     */
   const DString &getName() const
   {
      return(_strName);
   }
   /**
     * Get the process type associated with this command.
     * @returns an enum representing the process type
     */
   E_PROCESSTYPE getProcessType() const
   {
      return(_eProcessType);
   }
   /**
     * Get the web page name associated with this command.
     * @returns a reference to a string that identifies the command.
     */
   const DString &getWebPageName() const
   {
      return(_webPageName);
   }
   /**
   /**
     * This method is required when using the default constructor.
     * @param szCommand - A string literal used to look up the command.
     * @param type - An enum representing the process type for the command.
     * @param bModal - A boolean flag where true = modal, false = modeless.
     * @returns SEVERITY with conditions
     */
   SEVERITY init(
                const I_CHAR *szCommand,
                E_PROCESSTYPE type,
                bool bModal
                );
   /**
     * Find out if a command is within the hierarchy of a certain command type.
     * @param type - An integer command type wanted.
     * @returns true if command is within the hierarchy
     */
   bool isCommandTypeOf(
                       int type
                       ) const;
   /**
     * Get the modality of this object.
     * @returns true if modal, false if modeless
     */
   bool isModal() const
   {
      return(_bModal);
   }
   /**
     * Set the key for the command.  This key is used to distinguish among
     * multiple copies of the same process/dialog.
     * @param strKey - A string reference to the key value
     */
   void setKey(
              const DString &strKey
              )
   {
      _strKey = strKey;
   }
   /**
     * Set the number of allowed commands per user session.
     * @param max - Maximum number of commands per user session.
     */
   void setMaxPerUserSession(
                            int max
                            )
   {
      _maxPerUserSession = max;
   }
   /**
     * Set the number of allowed commands per work session.
     * @param max - Maximum number of commands per work session.
     */
   void setMaxPerWorkSession(
                            int max
                            )
   {
      _maxPerWorkSession = max;
   }
   /**
     * Set the process type for the command.
     * @param eType - Set the enum of the process type desired.
     */
   void setProcessType(
                      E_PROCESSTYPE eType
                      )
   {
      _eProcessType = eType;
   }

   int getWindowHeight() const
   {
      return(_windowHeight);
   }

   int getWindowWidth() const
   {
      return(_windowWidth);
   }

private: 
   bool _bModal;                       // This is set dynamically at creation
   int _commandType;
   E_MODETYPE _eAllowedModes;
   E_PROCESSTYPE _eProcessType;        // This is set dynamically at creation
   int _id;
   int _maxPerUserSession;
   int _maxPerWorkSession;
   DString _strKey;                   // Key to object - set dynamically
   DString _strName;
   DString _webPageName;
   int _windowHeight;					// used only for browser based dialogs
   int _windowWidth;					// used only for browser based dialogs
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/Command.hpp-arc  $
//
//   Rev 1.6   06 Dec 2007 15:19:52   popescu
//Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.5   Oct 09 2002 17:40:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   27 Mar 2002 19:52:40   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   22 Mar 2002 15:08:16   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Mar 27 2001 10:29:30   ROSIORUC
 * noth
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:36   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
