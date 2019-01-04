#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_consol_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_consol_not_valid() { }
		~CIFast_IFast_ifastcbo_err_consol_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONSOL_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Consolidation Type can not be blank for the %PAYMENTFOR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de consolidation est requis pour le %PAYMENTFOR%.")); }

        // Actions
	};
}



