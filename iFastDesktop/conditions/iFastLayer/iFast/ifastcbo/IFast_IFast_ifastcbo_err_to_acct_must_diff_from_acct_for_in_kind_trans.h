#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_in_kind_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_in_kind_trans() { }
		~CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_in_kind_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_IN_KIND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("In-kind transfer must be between different accounts, reset to cash.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kauf-Transfer muss zwischen verschiedenen Konten sein, zurücksetzen auf Bargeld.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia en especie debe ser entre diferentes cuentas, redefinir como efectivo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert en biens doit se faire entre des comptes différents, réinitialisez à comptant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht in natura moet tussen twee verschillende accounts zijn, opnieuw ingesteld op contant")); }

        // Actions
	};
}



