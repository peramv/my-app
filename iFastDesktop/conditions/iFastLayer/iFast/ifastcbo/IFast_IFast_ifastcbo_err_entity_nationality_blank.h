#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_nationality_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_nationality_blank() { }
		~CIFast_IFast_ifastcbo_err_entity_nationality_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_NATIONALITY_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nationality is blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nationality is blank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Nationality is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la nationalité est vide.")); }

        // Actions
	};
}



