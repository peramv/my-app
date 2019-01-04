#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_be_parent_child : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_be_parent_child() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_be_parent_child() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BE_PARENT_CHILD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund is not a parent or child fund class of AMS code %AMSCODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n’entre pas dans les catégories de fonds parent ni child du code de l’AMS %AMSCODE%.")); }

        // Actions
	};
}



