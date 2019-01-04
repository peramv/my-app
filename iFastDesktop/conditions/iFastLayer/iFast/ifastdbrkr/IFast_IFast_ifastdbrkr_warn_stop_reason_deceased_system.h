#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_warn_stop_reason_deceased_system : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_warn_stop_reason_deceased_system() { }
		~CIFast_IFast_ifastdbrkr_warn_stop_reason_deceased_system() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOP_REASON_DECEASED_SYSTEM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Stop Reason set ot Deceased (System).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La raison d'arrêt du compte est réglée à Décédé (système).")); }

        // Actions
	};
}



