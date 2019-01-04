#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_feecode_not_apply_to_modeloption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_feecode_not_apply_to_modeloption() { }
		~CIFast_IFast_ifastcbo_err_feecode_not_apply_to_modeloption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEECODE_NOT_APPLY_TO_MODELOPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Code: \"%FEECODE%\", cannot be applied to Model Option:\"%MODELOPTION%\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee Code: \"%FEECODE%\", cannot be applied to Model Option:\"%MODELOPTION%\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de frais %FEECODE% ne peut être appliqué à l'option de modèle %MODELOPTION%.")); }

        // Actions
	};
}



