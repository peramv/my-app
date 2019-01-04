#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tax_id_number_not_provided : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tax_id_number_not_provided() { }
		~CIFast_IFast_ifastcbo_warn_tax_id_number_not_provided() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAX_ID_NUMBER_NOT_PROVIDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Id Number is not provided.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'identification de l'impôt est manquant.")); }

        // Actions
	};
}



