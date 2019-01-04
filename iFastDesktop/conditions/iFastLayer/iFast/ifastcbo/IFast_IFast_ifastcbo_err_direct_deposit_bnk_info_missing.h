#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_direct_deposit_bnk_info_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_direct_deposit_bnk_info_missing() { }
		~CIFast_IFast_ifastcbo_err_direct_deposit_bnk_info_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRECT_DEPOSIT_BNK_INFO_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to find matching Direcrt Deposit Banking for Investor Authorization information on  %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'information bancaire correspondante du TEF par dépôt direct pour l'information sur l'autorisation de l'investisseur pour le %DATE%.")); }

        // Actions
	};
}



