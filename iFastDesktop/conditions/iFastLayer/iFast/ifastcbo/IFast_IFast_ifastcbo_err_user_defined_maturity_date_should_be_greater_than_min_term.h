#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_greater_than_min_term : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_greater_than_min_term() { }
		~CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_greater_than_min_term() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User Defined CMD should be at least greater than minimum term")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat définie par l'utilisateur doit être au moins supérieure au terme minimal.")); }

        // Actions
	};
}



