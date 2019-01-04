#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_num_or_acct_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_num_or_acct_required() { }
		~CIFast_IFast_ifastdbrkr_err_trans_num_or_acct_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_NUM_OR_ACCT_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either Transfer Number or Account should be provided.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Either Transfer Number or Account should be provided.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Either Transfer Number or Account should be provided.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro ou le compte de transfert est requis.")); }

        // Actions
	};
}



