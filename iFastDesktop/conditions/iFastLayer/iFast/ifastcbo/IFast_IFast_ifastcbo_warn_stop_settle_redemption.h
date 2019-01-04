#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_stop_settle_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_stop_settle_redemption() { }
		~CIFast_IFast_ifastcbo_warn_stop_settle_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOP_SETTLE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop redemption settlement flag is active on some accounts selected.  Redemptions belongs to these accounts will be excluded from settlement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop redemption settlement flag is active on some accounts selected.  Redemptions belongs to these accounts will be excluded from settlement.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de règlement de rachat est actif certains des comptes sélectionnés. Les rachats rattachés à ces comptes seront exclus du règlement.")); }

        // Actions
	};
}



