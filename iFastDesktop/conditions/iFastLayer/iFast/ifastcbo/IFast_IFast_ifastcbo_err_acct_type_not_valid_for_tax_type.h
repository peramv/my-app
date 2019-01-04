#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_type_not_valid_for_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_type_not_valid_for_tax_type() { }
		~CIFast_IFast_ifastcbo_err_acct_type_not_valid_for_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Type is not valid for the input tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account Type is not valid for the input tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart ist für die Vorsteuerart nicht gültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cuenta no es válido para el tipo tributario introducido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de compte invalide pour le type d'imposition saisi")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounttype is ongeldig voor ingevoerde belastingtype")); }

        // Actions
	};
}



