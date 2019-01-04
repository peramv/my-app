#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_province_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_province_is_required() { }
		~CIFast_IFast_ifastcbo_err_province_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROVINCE_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Province of registration is required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Province of registration is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierungs-Provinz ist notwendig. Wählen Sie eine Provinz.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La provincia de registro es obligatoria. Por favor seleccione una provincia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La province d'enregistrement est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Registratieprovincie is vereist. Selecteer een provincie")); }

        // Actions
	};
}



