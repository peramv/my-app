#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_intinvest_version_different : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_intinvest_version_different() { }
		~CIFast_IFast_ifastdbrkr_err_intinvest_version_different() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTINVEST_VERSION_DIFFERENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify IntInvest record, version numbers are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'enregistrement de l'investissement des intérêts; les numéros de version sont différents.")); }

        // Actions
	};
}



