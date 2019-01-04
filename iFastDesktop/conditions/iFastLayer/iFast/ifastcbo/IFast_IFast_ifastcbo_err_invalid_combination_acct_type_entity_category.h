#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_combination_acct_type_entity_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_combination_acct_type_entity_category() { }
		~CIFast_IFast_ifastcbo_err_invalid_combination_acct_type_entity_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid combination of account type and entity category.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison invalide de type de compte et de catégorie d’entité.")); }

        // Actions
	};
}



