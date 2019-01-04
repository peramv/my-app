#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_not_for_acct_designation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_not_for_acct_designation() { }
		~CIFast_IFast_ifastcbo_err_tax_type_not_for_acct_designation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type invalid for the account designation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart ungültig für Kontozuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo tributario no válido para la designación de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'imposition invalide pour la désignation du compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype is ongeldig voor de accountnaam")); }

        // Actions
	};
}



