#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_not_allowed_during_settlmentphase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_not_allowed_during_settlmentphase() { }
		~CIFast_IFast_ifastdbrkr_err_trans_not_allowed_during_settlmentphase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction not allowed during settlement phase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction non autorisée pendant la phase de règlement")); }

        // Actions
	};
}



