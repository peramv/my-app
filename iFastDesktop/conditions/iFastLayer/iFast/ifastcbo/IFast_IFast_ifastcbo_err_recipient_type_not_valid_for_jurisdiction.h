#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_recipient_type_not_valid_for_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_recipient_type_not_valid_for_jurisdiction() { }
		~CIFast_IFast_ifastcbo_err_recipient_type_not_valid_for_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Recipient type: %REC% not valid for jurisdiction: %JURISD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de bénéficiaire %REC% est invalide pour la juridiction fiscale %JURISD%.")); }

        // Actions
	};
}



