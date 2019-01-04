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


#include <bfproc\AbstractProcess.hpp>
///#endif


#include <ifastcbo\DSTCUserSession.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Implementation class for a user session process.
 *
 * The UserSessionProcess class represents the main process of logging on which
 * is required for all other processes.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/14/98</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE UserSessionProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   UserSessionProcess();
   UserSessionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~UserSessionProcess();
   void getSessionIdFromPage(DString& sessionId, DString& language, DString& companyId);
protected:
   /**
     * This method is being overridden temporarily to support fields without
     * a CBO.  This
     * method is called based on flags in the FieldDetails structure.
     * An exception will be thrown if the field cannot be found.
     * Override this method and set appropriate flags in FieldDetails structure,
     * if the derived class must process getField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - CBO data group ID we are operating with
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       )
   {  // A child has completed - here we don't care and don't end
      return(false);
   }
   /**
     * Implementation to override base ok processing.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual SEVERITY ok2(
                       GenericInterface *rpGI
                       );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation to support the send method.  STARTSESSION message
     * is supported
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szMessage - A string literal representing the message.
     * @returns true if successful, check conditions if false
     */
   virtual bool doSend(
                      GenericInterface *rpGICaller,
                      const I_CHAR *szMessage
                      );
   /**
     * This method is overridden temporarily so can run without CBO.
     * An exception will be thrown if the field is not found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - CBO data group ID we are operating with
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

private:
   void initUserSession();

   DString _strSystMgmt;
   DString _strNewPassword;
   DString _strPassword;
   DString _strUserID;
   DString _strMgmtCoName;
   DString _strAwdProfile;
   DString _language;
   DString _sessionId;
   DString _strAccessAllSlsRep;
   DString _strETrack;
   DString _strPageName;
   DString _strOldAwdProfile;
   DString _strOldMgmtCoName;
   DString _strXMLConfigFile;
   DSTCUserSession* _dstcUserSession;

   void clearSignonData();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UserSessionProcess.hpp-arc  $
 * 
 *    Rev 1.18   Sep 19 2011 14:49:32   dchatcha
 * Usability Improvement on iFAST/Desktop
 * 
 *    Rev 1.17   May 08 2004 13:28:16   YINGBAOL
 * PTS10029514:AWD Container disappears when Mgmt Co changed
 * 
 *    Rev 1.16   Mar 21 2003 17:49:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 12:54:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   19 Mar 2002 13:20:12   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.12   17 Jul 2001 11:24:36   PURDYECH
 * DSTCUserSession is now a pointer.  This allows us to fine tune the creation of the user session.
 * 
 *    Rev 1.11   14 May 2001 13:57:52   YINGZ
 * code sync up
 * 
 *    Rev 1.10   Jan 23 2001 15:18:48   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.9   Nov 08 2000 12:25:40   DT24433
 * moved server context flag to GenericInterface
 * 
 *    Rev 1.8   Nov 01 2000 13:03:44   DT24433
 * changes to make logon functionality more consistent between server and gui modes
 * 
 *    Rev 1.7   Oct 26 2000 10:43:46   DT24433
 * changes to work from parms passed in and no longer creating GIC or getting new usersessionid
 * 
 *    Rev 1.6   Sep 19 2000 15:20:40   VASILEAD
 * Cleanup services, UserSeesionProcess and security object
 * 
 *    Rev 1.5   Aug 02 2000 15:31:52   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Jul 27 2000 17:37:46   BUZILA
 * ClientLocale changes
 * 
 *    Rev 1.3   Jul 26 2000 11:45:48   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.2   Jul 25 2000 11:52:36   YINGZ
 * take out logon off for the existing user
 * 
 *    Rev 1.1   Feb 15 2000 18:57:06   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Dec 13 1999 14:19:44   DT24433
 * changed from using refresh to send
 * 
 *    Rev 1.5   13 Dec 1999 09:32:52   HSUCHIN
 * ?
 * 
 *    Rev 1.4   Dec 07 1999 12:18:04   DT24433
 * added idDataGroup to doGetField/doSetField parms
 * 
 *    Rev 1.3   Oct 29 1999 14:53:48   DT24433
 * changed doOk to OK2
 * 
 *    Rev 1.2   Aug 30 1999 18:18:02   DT24433
 * changed dosetfield/dogetfield method parms
 * 
 *    Rev 1.1   Jul 08 1999 10:04:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
