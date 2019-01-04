#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_maturity_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_maturity_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_maturity_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_MATURITY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Maturity Date Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Maturity Date Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Fälligkeitsdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de fecha de vencimiento no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de date d'échéance invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig type vervaldatum")); }

        // Actions
	};
}



