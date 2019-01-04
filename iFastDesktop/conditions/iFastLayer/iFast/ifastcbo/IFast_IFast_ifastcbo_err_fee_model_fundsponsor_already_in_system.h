#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_fundsponsor_already_in_system : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_fundsponsor_already_in_system() { }
		~CIFast_IFast_ifastcbo_err_fee_model_fundsponsor_already_in_system() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_FUNDSPONSOR_ALREADY_IN_SYSTEM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Code and Fund Sponsor already exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee Model Code and Fund Sponsor already exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais et le promoteur de fonds existent déjà.")); }

        // Actions
	};
}



