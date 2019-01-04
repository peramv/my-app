#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_parent_fund_class_with_another_active_ams_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_parent_fund_class_with_another_active_ams_model() { }
		~CIFast_IFast_ifastcbo_err_duplicate_parent_fund_class_with_another_active_ams_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_PARENT_FUND_CLASS_WITH_ANOTHER_ACTIVE_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The parent fund class already exists with another AMS Global Model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de fonds parent existe déjà pour un autre Modèle mondial AMS.")); }

        // Actions
	};
}



