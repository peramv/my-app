#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_one_remainingflag_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_one_remainingflag_required() { }
		~CIFast_IFast_ifastcbo_err_one_remainingflag_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONE_REMAININGFLAG_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("One allocation record must have Remaining flag set to Yes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'un des enregistrements de répartition doit être indiqué comme Restant (signal activé).")); }

        // Actions
	};
}



