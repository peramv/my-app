#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_paf_bucket : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_paf_bucket() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_paf_bucket() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PAF_BUCKET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Can not change password for %threshold% more days.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Impossible de modifier le mot de passe pour %threshold% jours supplementaires")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwort kann nicht für %threshold% weitere geändert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se puede cambiar la contraseña por %threshold% días más")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – impossible de changer le mot de passe avant %threshold% jours de plus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord kan pas worden gewijzigd over %threshold% dagen")); }

        // Actions
	};
}



