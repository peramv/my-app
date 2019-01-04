#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_kv_num_must_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_kv_num_must_be_entered() { }
		~CIFast_IFast_ifastdbrkr_err_kv_num_must_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_KV_NUM_MUST_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Broker KV Number must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Broker KV Number must be entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro VC du courtier en fonds est requis.")); }

        // Actions
	};
}



