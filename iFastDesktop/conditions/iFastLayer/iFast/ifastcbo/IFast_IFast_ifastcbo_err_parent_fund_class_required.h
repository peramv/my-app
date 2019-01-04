#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_parent_fund_class_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_parent_fund_class_required() { }
		~CIFast_IFast_ifastcbo_err_parent_fund_class_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PARENT_FUND_CLASS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A parent fund class is required when Trade via Parent Fund is 'Yes'.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Catégorie fonds parent requise lorsque le champ Transaction par Fonds parent est « Oui ».")); }

        // Actions
	};
}



