#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_as_pension_eligible : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_as_pension_eligible() { }
		~CIFast_IFast_ifastcbo_err_as_pension_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AS_PENSION_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not AS Pension eligible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds ist für AS-Renten nicht geeignet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este fondo no es apto para jubilación AS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas admissible x.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds komt niet in aanmerking voor AS-pensioen")); }

        // Actions
	};
}



