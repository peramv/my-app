#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_del_rec_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_del_rec_not_found() { }
		~CBase_Ifds_dita2kdb_dita2kdb_del_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DEL_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid character was found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte erneut senden, da der letzte Eintrag gelöscht wurde")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("An invalid character was found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un caractère invalide a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("An invalid character was found.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Corrigez le champ et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Correct the field and try again.")); }
	};
}



