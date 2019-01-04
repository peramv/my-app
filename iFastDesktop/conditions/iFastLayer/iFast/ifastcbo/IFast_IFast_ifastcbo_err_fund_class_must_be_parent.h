#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_be_parent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_be_parent() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_be_parent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BE_PARENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund is not a parent fund class of AMS code %AMSCODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds ne fait pas partie des catégories de fonds parent du code de l’AMS %AMSCODE%.")); }

        // Actions
	};
}



