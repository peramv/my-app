#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_consol_type_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_consol_type_mandatory() { }
		~CIFast_IFast_ifastcbo_consol_type_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CONSOL_TYPE_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Consolidation Type is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de consolidation est requis.")); }

        // Actions
	};
}



