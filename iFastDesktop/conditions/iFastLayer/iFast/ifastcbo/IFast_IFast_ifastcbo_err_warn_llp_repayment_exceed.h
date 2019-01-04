#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_llp_repayment_exceed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_llp_repayment_exceed() { }
		~CIFast_IFast_ifastcbo_err_warn_llp_repayment_exceed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_LLP_REPAYMENT_EXCEED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LLP repayment exceeds outstanding LLP withdrawals.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("LLP-Rückzahlung übersteigt ausstehende LLP-Abhebungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El reembolso LLP excede los retiros de LLP pendientes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le remboursement REEP excède les retraits REEP en cours.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("LLP-terugbetaling overschrijdt uitstaande LPP-opnames")); }

        // Actions
	};
}



