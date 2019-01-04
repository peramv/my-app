#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reset_entity_exceed_age_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reset_entity_exceed_age_limit() { }
		~CIFast_IFast_ifastcbo_err_reset_entity_exceed_age_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESET_ENTITY_EXCEED_AGE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account entity exceeds age limit of 79.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account entity exceeds age limit of 79.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account entity exceeds age limit of 79.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité du compte excède l'âge limite de 79 ans.")); }

        // Actions
	};
}



