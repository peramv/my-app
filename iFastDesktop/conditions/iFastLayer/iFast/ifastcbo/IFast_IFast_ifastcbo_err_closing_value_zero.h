#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_closing_value_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_closing_value_zero() { }
		~CIFast_IFast_ifastcbo_err_closing_value_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLOSING_VALUE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Closing index value cannot be zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Closing index value cannot be zero.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Closing index value cannot be zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'index de fermeture ne peut être zéro.")); }

        // Actions
	};
}



