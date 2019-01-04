#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_multiple_national_id_not_allowed_for_an_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_multiple_national_id_not_allowed_for_an_entity() { }
		~CIFast_IFast_ifastcbo_warn_multiple_national_id_not_allowed_for_an_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MULTIPLE_NATIONAL_ID_NOT_ALLOWED_FOR_AN_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("National ID for %COUNTRY% already exists within the same period.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Numéro d'identification national pour %COUNTRY% existe déjà pour la même période.")); }

        // Actions
	};
}



