#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_Red_Fund_class_grossnetdefault_value_overidden : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_Red_Fund_class_grossnetdefault_value_overidden() { }
		~CIFast_IFast_ifastcbo_err_Red_Fund_class_grossnetdefault_value_overidden() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You are overriding the fund class Red. GrossNet value of %FUND_CLASS_DEFAULT% .")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("You are overriding the fund class Red. GrossNet value of %FUND_CLASS_DEFAULT% .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("You are overriding the fund class Red. GrossNet value of %FUND_CLASS_DEFAULT% .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous écrasez le rachat de la catégorie de fonds valeur nette/brute de la %FUND_CLASS_DEFAULT% .")); }

        // Actions
	};
}



