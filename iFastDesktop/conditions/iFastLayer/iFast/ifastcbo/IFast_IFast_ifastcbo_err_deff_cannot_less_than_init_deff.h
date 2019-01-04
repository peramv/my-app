#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deff_cannot_less_than_init_deff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deff_cannot_less_than_init_deff() { }
		~CIFast_IFast_ifastcbo_err_deff_cannot_less_than_init_deff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEFF_CANNOT_LESS_THAN_INIT_DEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date cannot be less than Initial Effective Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'effet ne peut pas être antérieure à la date d'effet initiale.")); }

        // Actions
	};
}



