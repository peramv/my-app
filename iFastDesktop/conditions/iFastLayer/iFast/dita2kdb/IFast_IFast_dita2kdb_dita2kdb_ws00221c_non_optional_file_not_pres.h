#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_non_optional_file_not_pres : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_non_optional_file_not_pres() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_non_optional_file_not_pres() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_NON_OPTIONAL_FILE_NOT_PRES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account update failed due to problem with Account Entity update.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account update failed due to problem with Account Entity update.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Aktualisierung fehlgeschlagen wegen Problem mit Konto-Objekt-Aktualisierung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la actualización de la cuenta debido a un problema con la actualización de la entidad de cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mise à jour du compte a échoué en raison d'un problème avec la mise à jour de l'entité du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account kon niet worden bijgewerkt, er zijn problemen met het bijwerken van accounteenheden")); }

        // Actions
	};
}



