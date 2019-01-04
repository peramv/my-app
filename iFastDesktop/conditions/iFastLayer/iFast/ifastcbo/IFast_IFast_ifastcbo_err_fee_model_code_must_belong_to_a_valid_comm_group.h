#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group() { }
		~CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Code must belong to a valid Comm Group.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Code de modèle de frais doit appartenir à un Comm Group valide.")); }

        // Actions
	};
}



