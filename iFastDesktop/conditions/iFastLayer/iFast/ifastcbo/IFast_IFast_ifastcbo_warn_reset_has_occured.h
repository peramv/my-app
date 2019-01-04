#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_reset_has_occured : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_reset_has_occured() { }
		~CIFast_IFast_ifastcbo_warn_reset_has_occured() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESET_HAS_OCCURED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A reset has occured since the original trade")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une revalorisation a été effectuée depuis la transaction originale.")); }

        // Actions
	};
}



