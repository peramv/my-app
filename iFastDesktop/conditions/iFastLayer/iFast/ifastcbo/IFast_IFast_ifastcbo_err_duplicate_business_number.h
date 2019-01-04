#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_business_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_business_number() { }
		~CIFast_IFast_ifastcbo_err_duplicate_business_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_BUSINESS_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Business Number already exists in the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'entreprise existe déjà dans le système.")); }

        // Actions
	};
}