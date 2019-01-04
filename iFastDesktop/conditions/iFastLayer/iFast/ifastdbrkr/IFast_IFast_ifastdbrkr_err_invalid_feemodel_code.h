#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_feemodel_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_feemodel_code() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_feemodel_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FEEMODEL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid FeeModel code")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid FeeModel code")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de modèle de frais invalide")); }

        // Actions
	};
}



