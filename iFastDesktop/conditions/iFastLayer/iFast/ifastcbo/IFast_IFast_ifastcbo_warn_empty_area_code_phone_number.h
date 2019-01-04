#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_empty_area_code_phone_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_empty_area_code_phone_number() { }
		~CIFast_IFast_ifastcbo_warn_empty_area_code_phone_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EMPTY_AREA_CODE_PHONE_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either area code or fax/phone number is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de l'indicatif régional ou des numéros de téléphone/télécopieur est vide.")); }

        // Actions
	};
}



