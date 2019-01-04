#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_effective_date_validate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_effective_date_validate() { }
		~CIFast_IFast_ifastcbo_err_acct_effective_date_validate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_EFFECTIVE_DATE_VALIDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account effective must either be less than or equal to the first account effective date or greater than or equal to the latest effective date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account effective must either be less than or equal to the first account effective date or greater than or equal to the latest effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur du compte doit être inférieure ou identique à la première date d'entrée en vigueur du compte ou postérieure ou identique à la dernière date d'entrée en vigueur.")); }

        // Actions
	};
}



