#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_units_cannot_be_redeemed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_units_cannot_be_redeemed() { }
		~CIFast_IFast_ifastcbo_warn_units_cannot_be_redeemed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UNITS_CANNOT_BE_REDEEMED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Units cannot be redeemed due to holdback period.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Units cannot be redeemed due to holdback period.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Units cannot be redeemed due to holdback period.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les unités de peuvent être rachetées en raison de la période de retenue.")); }

        // Actions
	};
}



