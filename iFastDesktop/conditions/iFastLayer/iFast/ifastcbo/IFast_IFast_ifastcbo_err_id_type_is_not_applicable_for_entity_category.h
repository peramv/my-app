#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_id_type_is_not_applicable_for_entity_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_id_type_is_not_applicable_for_entity_category() { }
		~CIFast_IFast_ifastcbo_err_id_type_is_not_applicable_for_entity_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ID_TYPE% is not applicable for entity category %ENT_CAT%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%ID_TYPE% ne s’applique pas à la catégorie d’entités %ENT_CAT%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check ID of entity.")); }
	};
}



