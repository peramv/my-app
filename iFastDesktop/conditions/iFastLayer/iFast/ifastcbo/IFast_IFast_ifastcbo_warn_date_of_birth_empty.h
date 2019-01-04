#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_date_of_birth_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_date_of_birth_empty() { }
		~CIFast_IFast_ifastcbo_warn_date_of_birth_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DATE_OF_BIRTH_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date of birth not provided.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Date of birth is empty.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Date of birth is empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de naissance manquante")); }

        // Actions
	};
}



