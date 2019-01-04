#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_stop_pw_flag_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_stop_pw_flag_active() { }
		~CIFast_IFast_ifastdbrkr_err_stop_pw_flag_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_PW_FLAG_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Redemption Flag active. No settlement allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop Redemption Flag active. No settlement allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rachat est actif. Aucun règlement n'est autorisé.")); }

        // Actions
	};
}



