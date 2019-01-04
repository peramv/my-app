#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_may_used_by_other_places : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_may_used_by_other_places() { }
		~CIFast_IFast_ifastcbo_err_entity_may_used_by_other_places() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_MAY_USED_BY_OTHER_PLACES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You are changing the name of an entity that is used by another account or fund broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("You are changing the name of an entity that is used by another account or fund broker.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous êtes en train de changer le nom d'une entité qui est utilisée par un autre compte ou courtier en fonds.")); }

        // Actions
	};
}



