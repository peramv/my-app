#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_designation_must_same_in_kind_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_designation_must_same_in_kind_trans() { }
		~CIFast_IFast_ifastcbo_err_acct_designation_must_same_in_kind_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_DESIGNATION_MUST_SAME_IN_KIND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Designation must be the same for In-Kind Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Kauf-Transfer muss die gleiche Konto-Bezeichnung verwendet werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La designación de la cuenta debe ser igual para la transferencia en especie")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La désignation du compte doit être la même pour un transfert en biens.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnaam moet dezelfde zijn als voor overdracht in natura")); }

        // Actions
	};
}



