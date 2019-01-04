#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_future_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_future_effective_date() { }
		~CIFast_IFast_ifastcbo_err_rif_future_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_FUTURE_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date is future dated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective Date is future dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum liegt in der Zukunft.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia es futura.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur est postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum ligt in de toekomst")); }

        // Actions
	};
}



