#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bonus_interrest_rate_setup_only_for_dif_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bonus_interrest_rate_setup_only_for_dif_fund() { }
		~CIFast_IFast_ifastcbo_err_bonus_interrest_rate_setup_only_for_dif_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bonus Interest Rate can be setup only for DIF fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'intérêt de la prime ne peut être fixé que pour le FIJ.")); }

	};
}