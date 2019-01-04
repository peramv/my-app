#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_unable_to_add_estate_of_deceased_to_non_estate_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_unable_to_add_estate_of_deceased_to_non_estate_account() { }
		~CIFast_IFast_ifastcbo_warn_unable_to_add_estate_of_deceased_to_non_estate_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Adding new entity as 'Estate of Deceased' with non-estate account, may not be allowed")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’ajout de la nouvelle entité en tant que « succession de feu » peut être interdit avec un compte non successoral.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check account category information.")); }
	};
}



