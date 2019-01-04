#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_effective_date_must_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_effective_date_must_be_entered() { }
		~CIFast_IFast_ifastcbo_err_effective_date_must_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFFECTIVE_DATE_MUST_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An Effective date must be set.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Une date d'effet doit être definie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Effektivdatum muss festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse una fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une date d'entrée en vigueur doit être réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een ingangsdatum zijn ingesteld")); }

        // Actions
	};
}



