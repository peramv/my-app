#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pcg_inst_business_number_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pcg_inst_business_number_missing() { }
		~CIFast_IFast_ifastcbo_warn_pcg_inst_business_number_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PCG_INST_BUSINESS_NUMBER_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Business Number for PCG Instit. is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'entreprise de l'institution du responsable principal est manquant.")); }

        // Actions
	};
}



