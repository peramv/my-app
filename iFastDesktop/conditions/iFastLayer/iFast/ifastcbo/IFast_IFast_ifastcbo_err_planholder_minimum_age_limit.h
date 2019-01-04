#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_planholder_minimum_age_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_planholder_minimum_age_limit() { }
		~CIFast_IFast_ifastcbo_err_planholder_minimum_age_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLANHOLDER_MINIMUM_AGE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Planholder does not meet the minimum age requirements for this particular registered account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du régime ne remplit pas les conditions d'âge minimales pour ce compte enregistré particulier.")); }

        // Actions
	};
}



