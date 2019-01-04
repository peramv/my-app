#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_err_warn_account_type_dont_match_for_in_kind_trans : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_err_warn_account_type_dont_match_for_in_kind_trans() { }
		~CIFast_Infrastructure_dita2kdb_err_warn_account_type_dont_match_for_in_kind_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCOUNT_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to open .DAT file: %file%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to open .DAT file: %file%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DAT-Datei kann nicht geöffnet werden: %file%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible abrir archivo .DAT: %file%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ouvrir le fichier .DAT : %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bestand .DAT kan niet worden geopend: %file%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



