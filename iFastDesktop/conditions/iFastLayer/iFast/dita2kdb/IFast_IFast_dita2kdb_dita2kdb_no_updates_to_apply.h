#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_no_updates_to_apply : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_no_updates_to_apply() { }
		~CIFast_IFast_dita2kdb_dita2kdb_no_updates_to_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_UPDATES_TO_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Past password grace period.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Delai de grace de mot de passe revolu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach Kennwort-Frist-Periode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Pasó el período de gracia de la contraseña")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – délai de grâce du mot de passe dépassé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Na vervalperiode wachtwoord")); }

        // Actions
	};
}



