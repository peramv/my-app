#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tup_calculation_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tup_calculation_error() { }
		~CIFast_IFast_ifastcbo_err_tup_calculation_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TUP_CALCULATION_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Traded unit calculation error. Please call system support.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de calcul d'unité échangée. Veuillez communiquer avec le soutien informatique.")); }

        // Actions
	};
}



