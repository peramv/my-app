#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_defined_maturity_date_less_than_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_defined_maturity_date_less_than_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_user_defined_maturity_date_less_than_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User defined CMD cannot be greater than legal contract maturity date")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat définie par l'utilisateur ne doit pas être supérieure à la date d'échéance du contrat légal.")); }

        // Actions
	};
}



