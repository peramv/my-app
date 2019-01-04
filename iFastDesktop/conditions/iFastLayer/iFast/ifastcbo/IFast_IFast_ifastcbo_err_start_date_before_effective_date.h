#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_before_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_before_effective_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_before_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_BEFORE_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date must be after the Effective Date of PAC/Savings Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum muss größer sein als das Effektivdatum des PAC/Spar-Plans")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia debe ser posterior a la fecha de entrada en vigencia del PAC/plan de ahorro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la date d'entrée en vigueur du PAC/régime d'épargne.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum moet later zijn dan ingangsdatum van het VGC/Savings Plan")); }

        // Actions
	};
}



