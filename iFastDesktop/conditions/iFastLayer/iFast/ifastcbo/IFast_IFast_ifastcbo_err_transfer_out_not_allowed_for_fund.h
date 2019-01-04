#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_out_not_allowed_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_out_not_allowed_for_fund() { }
		~CIFast_IFast_ifastcbo_err_transfer_out_not_allowed_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer out not allowed for fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert sortant non autorisé pour le fonds")); }

        // Actions
	};
}



