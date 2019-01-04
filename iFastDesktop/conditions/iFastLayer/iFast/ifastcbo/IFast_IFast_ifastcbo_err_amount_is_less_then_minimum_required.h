#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_is_less_then_minimum_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_is_less_then_minimum_required() { }
		~CIFast_IFast_ifastcbo_err_amount_is_less_then_minimum_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less then the minimum required of %min% units.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount is less then the minimum required of %min% units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur au minimum d'unités requises de %min%.")); }

        // Actions
	};
}



