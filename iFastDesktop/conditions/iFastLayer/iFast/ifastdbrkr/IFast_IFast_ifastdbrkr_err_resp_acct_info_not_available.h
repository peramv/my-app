#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_acct_info_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_acct_info_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_resp_acct_info_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_ACCT_INFO_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Account information not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le compte REEE n'est pas disponible.")); }

        // Actions
	};
}



