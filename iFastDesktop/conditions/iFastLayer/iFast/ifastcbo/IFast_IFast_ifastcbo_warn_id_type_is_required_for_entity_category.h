#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_id_type_is_required_for_entity_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_id_type_is_required_for_entity_category() { }
		~CIFast_IFast_ifastcbo_warn_id_type_is_required_for_entity_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ID_TYPE% is required for %ENT_CAT%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check ID of entity.")); }
	};
}



