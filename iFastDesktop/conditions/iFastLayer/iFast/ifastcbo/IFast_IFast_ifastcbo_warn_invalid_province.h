#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_province : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_province() { }
		~CIFast_IFast_ifastcbo_warn_invalid_province() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_PROVINCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid province of registration.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Region d'enregistrement invalide")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Registrierungs-Provinz.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Provincia de registro no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Province d'enregistrement invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige registratieprovincie")); }

        // Actions
	};
}



