#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_occupation_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_occupation_empty() { }
		~CIFast_IFast_ifastcbo_warn_occupation_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_OCCUPATION_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Occupation is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Occupation is empty.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Occupation is empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de l'emploi est vide.")); }

        // Actions
	};
}



