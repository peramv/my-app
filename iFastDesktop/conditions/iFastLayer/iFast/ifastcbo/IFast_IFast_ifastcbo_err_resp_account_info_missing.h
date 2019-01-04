#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_account_info_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_account_info_missing() { }
		~CIFast_IFast_ifastcbo_err_resp_account_info_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_ACCOUNT_INFO_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Account Information does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le compte REEE est inexistante.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please first update this information in RESP Account Information screen.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez d'abord mettre à jour cette information dans l'écran d'information sur le compte REEE.")); }
	};
}



