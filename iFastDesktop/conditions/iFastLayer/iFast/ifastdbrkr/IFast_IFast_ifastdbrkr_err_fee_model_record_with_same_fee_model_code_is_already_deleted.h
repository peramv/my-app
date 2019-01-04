#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_model_record_with_same_fee_model_code_is_already_deleted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_model_record_with_same_fee_model_code_is_already_deleted() { }
		~CIFast_IFast_ifastdbrkr_err_fee_model_record_with_same_fee_model_code_is_already_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_RECORD_WITH_SAME_FEE_MODEL_CODE_IS_ALREADY_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model record with same Fee Model code is already deleted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’enregistrement du modèle de frais sous le même code de modèle de frais a déjà été supprimé.")); }

        // Actions
	};
}



