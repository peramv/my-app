#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_not_allowed_for_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_not_allowed_for_redcode() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_not_allowed_for_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type must be %DEPOSITTYPE% for RedCode %REDCODE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt doit être %DEPOSITTYPE% pour le code de rachat %REDCODE%.")); }

        // Actions
	};
}



