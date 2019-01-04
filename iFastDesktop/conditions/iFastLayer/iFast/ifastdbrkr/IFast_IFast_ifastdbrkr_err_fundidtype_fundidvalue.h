#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fundidtype_fundidvalue : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fundidtype_fundidvalue() { }
		~CIFast_IFast_ifastdbrkr_err_fundidtype_fundidvalue() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDIDTYPE_FUNDIDVALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundIdType and FundIdValue must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FundIdType and FundIdValue must be entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de code de fonds et la valeur de code de fonds sont requis.")); }

        // Actions
	};
}



