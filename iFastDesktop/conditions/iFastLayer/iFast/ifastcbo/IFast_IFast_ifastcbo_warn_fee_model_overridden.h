#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fee_model_overridden : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fee_model_overridden() { }
		~CIFast_IFast_ifastcbo_warn_fee_model_overridden() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FEE_MODEL_OVERRIDDEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee model has been overridden to %acqoption%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee model has been overridden to %acqoption%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le modèle de frais a été modifié à %acqoption%.")); }

        // Actions
	};
}



