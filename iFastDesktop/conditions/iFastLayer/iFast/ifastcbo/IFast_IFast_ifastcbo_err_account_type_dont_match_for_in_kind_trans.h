#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_type_dont_match_for_in_kind_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_type_dont_match_for_in_kind_trans() { }
		~CIFast_IFast_ifastcbo_err_account_type_dont_match_for_in_kind_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Type doesn't match.  It does not meet in-kind transfer criteria, reset to cash.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart passt nicht. Kauf-Transfer-Kriterien treffen nicht zu, zurücksetzen auf Bargeld.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cuenta no coincide. No cumple con los criterios de transferencia en especie, redefinir como efectivo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de compte ne correspond pas. Il ne répond pas au critère de transfert en biens, réinitialisez à comptant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounttype komt niet overeen. Voldoet niet aan de criteria voor een overdracht in natura, opnieuw ingesteld op contant")); }

        // Actions
	};
}



