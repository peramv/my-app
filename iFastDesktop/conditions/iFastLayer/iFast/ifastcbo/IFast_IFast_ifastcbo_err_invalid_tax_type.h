#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_tax_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid tax type for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Type de taxe invalide pour ce compte")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Steuerart für dieses Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo tributario no válido para esta cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'imposition invalide pour ce compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig belastingtype voor dit account")); }

        // Actions
	};
}



