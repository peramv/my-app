#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_foreign_fund_class_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_foreign_fund_class_required() { }
		~CIFast_IFast_ifastcbo_err_warn_foreign_fund_class_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_FOREIGN_FUND_CLASS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Foreign Fund/Class value are required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Foreign Fund/Class value are required.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Foreign Fund/Class value are required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du fonds étranger/de la classe étrangère est requise.")); }

        // Actions
	};
}



