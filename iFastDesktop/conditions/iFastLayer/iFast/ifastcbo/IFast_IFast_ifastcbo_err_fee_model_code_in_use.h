#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_code_in_use : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_code_in_use() { }
		~CIFast_IFast_ifastcbo_err_fee_model_code_in_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_CODE_IN_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Fee Model Code is currently used in the system, can not be deleted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The Fee Model Code is currently used in the system, can not be deleted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais est déjà utilisé dans le système et ne peut être supprimé.")); }

        // Actions
	};
}



