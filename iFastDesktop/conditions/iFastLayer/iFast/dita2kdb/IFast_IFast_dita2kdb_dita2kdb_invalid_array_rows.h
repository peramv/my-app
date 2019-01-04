#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_array_rows : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_array_rows() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_array_rows() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ARRAY_ROWS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - User has no company access.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Utilisateur n'a pas acces a la societe")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Benutzer hat keinen Unternehmenszugriff")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - El usuario no tiene acceso a la compañía")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – l'utilisateur n'a pas d'accès d'entreprise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Gebruiker heeft geen bedrijfstoegang")); }

        // Actions
	};
}



