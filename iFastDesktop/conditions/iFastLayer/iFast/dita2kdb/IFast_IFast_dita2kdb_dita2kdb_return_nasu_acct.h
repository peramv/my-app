#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_return_nasu_acct : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_return_nasu_acct() { }
		~CIFast_IFast_dita2kdb_dita2kdb_return_nasu_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RETURN_NASU_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No setup record for/after the year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No setup record for/after the year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Erstellungs-Eintrag für/nach diesem Jahr")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay registro de configuración para/después del año")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de réglage pour/après l'année")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen instellingsrecord voor/na het jaar")); }

        // Actions
	};
}



