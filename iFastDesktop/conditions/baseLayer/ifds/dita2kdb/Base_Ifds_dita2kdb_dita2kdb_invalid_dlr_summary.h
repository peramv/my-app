﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_summary : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_summary() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_summary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DLR_SUMMARY")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There was an internal error.  An illegal call was made.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mittler (Intermediary) nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There was an internal error.  An illegal call was made.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu une erreur interne. Un appel illégal a été fait.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("There was an internal error.  An illegal call was made.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



