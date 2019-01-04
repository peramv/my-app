#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_start_month : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_start_month() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_start_month() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_START_MONTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - User account not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Compte d'utilisateur desactive")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Benutzerkonto nicht aktiv")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - La cuenta del usuario no está activa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – le compte de l'utilisateur est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Gebruikersaccount is niet actief")); }

        // Actions
	};
}



