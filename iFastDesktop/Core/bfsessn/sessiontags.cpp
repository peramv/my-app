//******************************************************************************
//
//  These tags are used in the session.ini file.  It is very important
//  that any information that session will send to AWD or to a log file
//  must have a #define here so that the tag may be consistant with
//  what it shall be in the session.ini file.
//
//******************************************************************************
#include "win32/stdafx.h"

#include "bfcpsessiontags.h"

namespace SessionTags
{
   const I_CHAR *AWD_COMMENT             = I_("AwdComment");
   const I_CHAR *AWD_EVENT               = I_("AwdEvent");
   const I_CHAR *AWD_ID                  = I_("AwdOperatorId");
   const I_CHAR *AWD_PROPAGATE           = I_("AwdPropagate");
   const I_CHAR *AWD_PWORK               = I_("AwdPaperWork");
   const I_CHAR *AWD_WORK                = I_("AwdWork");
   const I_CHAR *BEGIN_TIME              = I_("BeginTime");
   const I_CHAR *BUSINESS_AREA           = I_("BusinessArea");
   const I_CHAR *CALL_END                = I_("CallEndTime");
   const I_CHAR *CALL_START              = I_("CallStartTime");
   const I_CHAR *CONFIG                  = I_("Session");
   const I_CHAR *CREATE_CASE             = I_("CreateCase");
   const I_CHAR *CREATE_WORK             = I_("CreateWork");
   const I_CHAR *DEFAULT                 = I_("~default");
   const I_CHAR *DISPLAY_CSD             = I_("DisplayCsd");
   const I_CHAR *END_TIME                = I_("EndTime");
   const I_CHAR *EVENT_ID                = I_("EventId");
   const I_CHAR *EVENT_TIME              = I_("EventTime");
   const I_CHAR *EVENT_DURATION          = I_("EventDuration");
   const I_CHAR *HLLAPI                  = I_("HLLAPI");
   const I_CHAR *ISTATUS                 = I_("IndexStatus");
   const I_CHAR *LOG_EVENT               = I_("LogEvent");
   const I_CHAR *LOG_ITEM                = I_("LogItem");
   const I_CHAR *LOG_PASSWORD            = I_("LogPassword");
   const I_CHAR *LOG_PITEM               = I_("LogPaperItem");
   const I_CHAR *LOG_SOURCE              = I_("LogSource");
   const I_CHAR *LOG_USER                = I_("LogUser");
   const I_CHAR *MESSAGE                 = I_("Message");
   const I_CHAR *NEW_BEGIN_TIME          = I_("NewBeginTime");
   const I_CHAR *NO_WORK                 = I_("NoWork");
   const I_CHAR *ORIGINATION             = I_("Origination");
   const I_CHAR *ORIG_PAPER              = I_("Paper");
   const I_CHAR *ORIG_PHONE              = I_("Phone");
   const I_CHAR *PREVIOUS_EVENT_TIME     = I_("PreviousEventTime");
   const I_CHAR *PRIMARY                 = I_("Primary");
   const I_CHAR *PSTATUS                 = I_("ProcessStatus");
   const I_CHAR *QUEU                    = I_("QUEU");
   const I_CHAR *STATUS                  = I_("Status");
   const I_CHAR *STATUS_TYPE             = I_("StatusType");
   const I_CHAR *TA2K_ID                 = I_("TA2KID");
   const I_CHAR *TABLE                   = I_("AwdTable");
   const I_CHAR *UPDATE_WORK             = I_("UpdateWork");
   const I_CHAR *WORK_TYPE               = I_("WorkType");

   // These are Configuration objects
   const I_CHAR *AWD_CASE                = I_("Awd Case");
   const I_CHAR *AWD_PCASE               = I_("Awd Case Paper");
   const I_CHAR *CASE_TABLE              = I_("Case Table");
   const I_CHAR *EVENT_LOG               = I_("Event Log");
   const I_CHAR *EVENT_LOGGING           = I_("Event Logging");
   const I_CHAR *EXPORT_TABLE            = I_("Export Table");
   const I_CHAR *HLLAPI_EVENT            = I_("HLLAPI Create Work");
   const I_CHAR *NOT_PROCESSED           = I_("Not Processed");
   const I_CHAR *ROAD_TABLE              = I_("Road Table");
   const I_CHAR *USE_AWD                 = I_("Use Awd");
   const I_CHAR *USE_AWD_PORTAL                 = I_("Use Awd Portal");
   const I_CHAR *USE_MESSAGING           = I_("Use Messaging");
   const I_CHAR *WORK_TABLE              = I_("Work Table");
   const I_CHAR *USE_CALL_CENTRE         = I_("Use Call Centre");

   // These are the Configuration IDI name values
   const I_CHAR *WORK_OBJECT_DETAILS     = I_("WorkObjectDetails");
   const I_CHAR *AWD_ERROR               = I_("AWDError");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/sessiontags.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 08:58:52   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.1   Apr 20 2004 10:47:40   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.0   28 May 2002 12:11:14   SMITHDAV
// Initial revision.
// 
//    Rev 1.3   Apr 09 1999 13:30:00   DMUM
// Sync up with 1.6.x
//
//    Rev 1.1.1.0   Mar 31 1999 13:16:56   DMUM
//
//
//    Rev 1.0.1.1   Feb 26 1999 08:50:20   DMUM
// Development for TA2000 NT 3.4
//
//    Rev 1.0.1.0   Feb 08 1999 15:09:20   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0   29 Jul 1998 20:33:20   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.9   Jul 23 1998 10:26:04   dmum
// Added new tag
//
//    Rev 1.8   Jul 16 1998 11:44:02   dmum
// Added CREATE_CASE
//
//    Rev 1.7   Mar 27 1998 10:59:06   dmum
// Added new tags and moved some to GuiSessionTags
//
//    Rev 1.6   Mar 17 1998 11:04:40   dmum
// Added new begin time
//
//    Rev 1.5   Mar 16 1998 15:40:28   dmum
// Moving gui specific tags to guisessiontags
//
//    Rev 1.4   Jan 30 1998 14:00:42   dmum
// added tags
//

