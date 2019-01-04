#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_bank_micr_id : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_bank_micr_id() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_bank_micr_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_BANK_MICR_ID")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  %CMD% command must run modally.  (Attempted to run modeless.)")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  %CMD% command must run modally.  (Attempted to run modeless.)")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There is an internal problem.  %CMD% command must run modally.  (Attempted to run modeless.)")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El comando %CMD% debe ejecutarse modalmente.  (Se intentó ejecutarlo sin modo.)")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La commande %COMMAND% doit s'exécuter de façon modale (tentative de s'exécuter de façon amodale).")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
	};
}



