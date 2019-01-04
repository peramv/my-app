#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group_or_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group_or_fund() { }
		~CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group_or_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Code must belong to a valid Comm Group or Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Code de modèle de frais doit appartenir à un Comm Group ou à un fonds valide.")); }

        // Actions
	};
}



