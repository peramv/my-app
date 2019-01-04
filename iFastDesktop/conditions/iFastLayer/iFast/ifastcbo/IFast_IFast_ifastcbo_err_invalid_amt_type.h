#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amt_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amt_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_amt_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Amount Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Betragsart")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de monto no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig bedragtype")); }

        // Actions
	};
}



