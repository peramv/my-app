#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_effective_date_forward : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_effective_date_forward() { }
		~CIFast_IFast_ifastcbo_err_effective_date_forward() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFFECTIVE_DATE_FORWARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date  can not be changed forward for existing record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effective Date  can not be changed forward for existing record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur ne peut être devancée pour l'enregistrement existant.")); }

        // Actions
	};
}



