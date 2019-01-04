#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_settle_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_settle_redemption() { }
		~CIFast_IFast_ifastcbo_err_stop_settle_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_SETTLE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop redemption settlement flag is active on the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop redemption settlement flag is active on the account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de règlement de rachat est actif pour le compte.")); }

        // Actions
	};
}



