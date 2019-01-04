#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_denominator_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_denominator_is_zero() { }
		~CIFast_IFast_ifastcbo_err_denominator_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DENOMINATOR_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The denominator cannot be zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Nenner darf nicht Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El denominador no puede ser cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dénominateur ne peut être zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De noemer kan niet nul zijn")); }

        // Actions
	};
}



