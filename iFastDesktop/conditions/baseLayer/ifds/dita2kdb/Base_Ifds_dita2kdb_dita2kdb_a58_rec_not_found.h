#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_a58_rec_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_a58_rec_not_found() { }
		~CBase_Ifds_dita2kdb_dita2kdb_a58_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A58_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The current country settings are not supported.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nächster Schlüssel passte nicht zum erwarteten Format")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The current country settings are not supported.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les paramètres du pays actuels ne sont pas reconnus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The current country settings are not supported.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



