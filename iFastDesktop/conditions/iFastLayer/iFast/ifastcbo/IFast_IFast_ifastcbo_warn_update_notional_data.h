#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_update_notional_data : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_update_notional_data() { }
		~CIFast_IFast_ifastcbo_warn_update_notional_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UPDATE_NOTIONAL_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please update notional data.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez mettre à jour les données théoriques.")); }

        // Actions
	};
}



