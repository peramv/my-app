#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_one_parent_entity_is_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_one_parent_entity_is_allowed() { }
		~CIFast_IFast_ifastcbo_err_only_one_parent_entity_is_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Parent/Legal Guardian Entity is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only one Parent/Legal Guardian Entity is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein Eltern / Vormund-Objekt ist zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite una entidad Padre/Tutor legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une seule entité parent/tuteur légal est autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één eenheid Ouder/Wettelijke voogd toegestaan")); }

        // Actions
	};
}



