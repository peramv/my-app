#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_country_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_country_is_blank() { }
		~CIFast_IFast_ifastcbo_err_country_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COUNTRY_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country is blank. Please enter a country.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du pays est vide. Veuillez entrer un pays.")); }

        // Actions
	};
}



