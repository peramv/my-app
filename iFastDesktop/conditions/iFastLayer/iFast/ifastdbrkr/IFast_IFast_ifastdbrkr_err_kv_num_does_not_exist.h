﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_kv_num_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_kv_num_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_kv_num_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_KV_NUM_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Broker KV Number does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Broker KV Number does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro VC du courtier en fonds est inexistant.")); }

        // Actions
	};
}



