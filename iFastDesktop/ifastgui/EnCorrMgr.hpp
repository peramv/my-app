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
//
// ^FILE   : EnCorrMgr.hpp
// ^AUTHOR : Michael James McGarry
// ^DATE   : 29 Jul 1998
//
// ^CLASS  : EnCorrMgr
// ^PARENT : RoadComMgr
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#include <ifastgui\roadcommgr.hpp>
#include <tinstancemanager.hpp>
#include <bfproc\genericinterface.hpp>
#include <string>

class RoadEncorr;

class EnCorrMgr : public RoadComMgr
{
   // Public Methods
public:
   static EnCorrMgr *getInstance();

   void start( GenericInterface *pGI );
   virtual void end();

protected:

   virtual BOOL performTask( COleDispatchDriver *pOleDispatch );

   virtual COleDispatchDriver *createDispatch();

   virtual void releaseDispatch( COleDispatchDriver *pOleDispatch = NULL );


private:
   EnCorrMgr( const DString &id );
   virtual ~EnCorrMgr();

private:
   typedef TInstanceManager<DString, EnCorrMgr> InstanceManager;
   friend InstanceManager;

   static InstanceManager m_instanceManager;
   DString m_id;
   BOOL m_exitEnCorr;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/EnCorrMgr.hpp-arc  $
 * 
 *    Rev 1.5   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 19:15:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   Jun 19 2001 18:43:30   HERNANDO
 * Changed Parameter passed to Start() - GI instead of GIC
 * 
 *    Rev 1.2   03 May 2001 14:07:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Feb 15 2000 18:59:22   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Jul 12 1999 18:27:06   HSUCHIN
 * removed getExportAwdConvertedData
 * 
 *    Rev 1.2   Jul 12 1999 18:26:14   HSUCHIN
 * removed getExportAwdConvertedData
 * 
 *    Rev 1.1   Jul 08 1999 10:05:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

