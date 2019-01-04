#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_to_pension_jurisdiction_not_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_to_pension_jurisdiction_not_same() { }
		~CIFast_IFast_ifastcbo_err_transfer_to_pension_jurisdiction_not_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TO_PENSION_JURISDICTION_NOT_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pension Jurisdiction must be the same.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Renten-Rechtssprechung muss die gleiche sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La jurisdicción de jubilación debe ser la misma.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction de retraite doit être la même.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pensioenrechtsgebied moet hetzelfde zijn")); }

        // Actions
	};
}



