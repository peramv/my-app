#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reinvestment_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reinvestment_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_reinvestment_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REINVESTMENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reinvestment is not allowed for this fund/class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Réinvestissement non autorisé pour ce fonds/cette classe")); }

        // Actions
	};
}



