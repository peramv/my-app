#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_parameter_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_parameter_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_fee_parameter_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_PARAMETER_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Parameter already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisionsparameter existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El parámetro de comisiones ya existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Paramètres de frais déjà existants")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostenparameter bestaat al")); }

        // Actions
	};
}



