#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_params_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_params_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_fee_params_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_PARAMS_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Parameters not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisions-Parameter nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay disponibles parámetros de comisiones")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les paramètres de frais ne sont pas disponibles.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostenparameters zijn niet beschikbaar")); }

        // Actions
	};
}



