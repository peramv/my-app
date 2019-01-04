#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_entity_category_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_entity_category_is_required() { }
		~CIFast_IFast_ifastcbo_warn_entity_category_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ENTITY_CATEGORY_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User may need to supply entity category.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’utilisateur devra peut-être fournir la catégorie d’entité.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check employee class.")); }
	};
}



