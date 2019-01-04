#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_between_min_max_age : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_between_min_max_age() { }
		~CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_between_min_max_age() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User Defined CMD should be within minimum and maximum age restriction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat définie par l'utilisateur doit être située entre les restrictions d'âges minimal et maximal.")); }

        // Actions
	};
}



