#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_llp_repayment_prevent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_llp_repayment_prevent() { }
		~CIFast_IFast_ifastcbo_err_warn_llp_repayment_prevent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_LLP_REPAYMENT_PREVENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LLP repayment will prevent further LLP from withdrawals.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("LLP-Rückzahlung verhindert die Abhebung von weiteren LLPs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El reembolso LLP impedirá realizar más retiros de LLP .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le remboursement REEP empêchera les retraits des REEP supplémentaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("LLP-terugbetaling voorkomt opnames van toekomstig LLP")); }

        // Actions
	};
}



