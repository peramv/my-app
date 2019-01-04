#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_feemodel_code_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_feemodel_code_not_active() { }
		~CIFast_IFast_ifastcbo_err_feemodel_code_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEEMODEL_CODE_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FeeModelCode %FEEMODELCODE% is not active as of date %DATE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FeeModelCode %FEEMODELCODE% is not active as of date %DATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais  %FEEMODELCODE% est inactif en date du %DATE%.")); }

        // Actions
	};
}



