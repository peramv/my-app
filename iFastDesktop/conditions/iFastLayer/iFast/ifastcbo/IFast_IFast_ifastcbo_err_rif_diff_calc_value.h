#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_diff_calc_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_diff_calc_value() { }
		~CIFast_IFast_ifastcbo_err_rif_diff_calc_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_DIFF_CALC_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The calculated value for this field is %CALCULATED%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The calculated value for this field is %CALCULATED%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der errechnete Wert für dieses Feld ist %CALCULATED%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor calculado para este campo es %CALCULATED%..")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur calculée pour ce champ est %CALCULATED%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De berekende waarde voor dit veld is %CALCULATED%")); }

        // Actions
	};
}



