#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_max_less_than_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_max_less_than_min() { }
		~CIFast_IFast_ifastcbo_err_max_less_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAX_LESS_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum value has to be greater than minimum value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maximum value has to be greater than minimum value.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Maximum value has to be greater than minimum value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur maximale doit être supérieure à la valeur minimale.")); }

        // Actions
	};
}



