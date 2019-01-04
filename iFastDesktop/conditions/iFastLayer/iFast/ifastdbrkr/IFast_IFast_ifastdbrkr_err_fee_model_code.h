#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_model_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_model_code() { }
		~CIFast_IFast_ifastdbrkr_err_fee_model_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Code must belong to valid Comm Group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee Model Code must belong to valid Comm Group.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de fonds doit appartenir à un groupe de commission valide.")); }

        // Actions
	};
}



