#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_07_must_beused_rif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_07_must_beused_rif() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_07_must_beused_rif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_07_MUST_BEUSED_RIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type 07 must be used with RIF account only.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-Typ 07 darf nur mit einem RIF-Konto verwendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de depósito 07 debe utilizarse con la cuenta RIF únicamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt 07 ne doit être utilisé qu'avec un compte FRR.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Depositotype 07 moet alleen worden gebruikt bij een RIF-account")); }

        // Actions
	};
}



