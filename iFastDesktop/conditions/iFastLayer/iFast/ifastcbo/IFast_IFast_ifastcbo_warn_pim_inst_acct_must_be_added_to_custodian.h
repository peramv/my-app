#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pim_inst_acct_must_be_added_to_custodian : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pim_inst_acct_must_be_added_to_custodian() { }
		~CIFast_IFast_ifastcbo_warn_pim_inst_acct_must_be_added_to_custodian() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PIM and Institutional accounts must be added to the Account Custodian and Middle Office account groups to capture the Account Custodian ID and Middle Office ID. A Custodian Account Number CDN or Custodian Account Number USD must also be added on the Account Identifier screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les comptes de GPP et institutionnels doivent être ajoutés aux groupes de comptes administratifs et de dépositaires pour obtenir leurs identifiants respectifs. Un numéro de compte de dépositaire en $ CA ou en $ US ou des numéros de comptes dans les deux devises doivent être également ajoutés dans l’écran d’identification des comptes.")); }

        // Actions
	};
}



