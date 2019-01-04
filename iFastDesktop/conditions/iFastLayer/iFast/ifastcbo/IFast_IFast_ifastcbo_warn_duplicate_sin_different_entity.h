#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_duplicate_sin_different_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_duplicate_sin_different_entity() { }
		~CIFast_IFast_ifastcbo_warn_duplicate_sin_different_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DUPLICATE_SIN_DIFFERENT_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate SIN found in the entity list.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate SIN found in the entity list.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une copie du NAS a été trouvée dans la liste d'entités.")); }

        // Actions
	};
}



