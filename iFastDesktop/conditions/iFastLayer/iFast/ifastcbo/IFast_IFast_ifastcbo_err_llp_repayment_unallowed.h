#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_llp_repayment_unallowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_llp_repayment_unallowed() { }
		~CIFast_IFast_ifastcbo_err_llp_repayment_unallowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LLP_REPAYMENT_UNALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LLP repayment is allowed only from non-registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("LLP-Rückzahlung ist nur von einem nicht-registriertem Konto erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El reembolso LLP sólo se permite de cuentas no registradas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le remboursement REEP n'est autorisé que depuis les comptes non enregistrés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("LLP-terugbetaling is alleen toegestaan vanuit een niet-geregistreerd account")); }

        // Actions
	};
}



