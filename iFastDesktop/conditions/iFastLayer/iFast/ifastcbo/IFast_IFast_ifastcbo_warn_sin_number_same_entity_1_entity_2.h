#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_sin_number_same_entity_1_entity_2 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_sin_number_same_entity_1_entity_2() { }
		~CIFast_IFast_ifastcbo_warn_sin_number_same_entity_1_entity_2() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ENTITY_1%'s sin is the same as %ENTITY_2%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS de l'entité %ENTITY_1% est le même que celui de l'entité %ENTITY_2%.")); }

        // Actions
	};
}



