#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_remainingflags_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_remainingflags_found() { }
		~CIFast_IFast_ifastcbo_err_multiple_remainingflags_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_REMAININGFLAGS_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one allocation record can have Remaining flag set to Yes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement de répartition peut être indiqué comme Restant (signal activé).")); }

        // Actions
	};
}



