#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_batch_num : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_batch_num() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_batch_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_BATCH_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There was an internal error.  A field was expected but was not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer ist ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There was an internal error.  A field was expected but was not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu une erreur interne. Un champ était escompté, mais reste introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("There was an internal error.  A field was expected but was not found.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



