#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_code_overlaped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_code_overlaped() { }
		~CIFast_IFast_ifastcbo_err_fee_code_overlaped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_CODE_OVERLAPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Parameter is overlapped for %CODE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisionsparameter überschneiden sich für %CODE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los parámetros de comisión se superponen para %CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paramètre de frais est chevauché pour le code %CODE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostenparameter wordt overlapt voor %CODE%")); }

        // Actions
	};
}



