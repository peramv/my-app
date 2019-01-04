#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unable_to_add_estate_of_deceased_to_non_estate_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unable_to_add_estate_of_deceased_to_non_estate_account() { }
		~CIFast_IFast_ifastcbo_err_unable_to_add_estate_of_deceased_to_non_estate_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to Add new entity as 'Estate of Deceased' with non-estate account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d’ajouter la nouvelle entité en tant que « succession de feu » avec un compte non successoral.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check account category information.")); }
	};
}



