#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_resp_sibling_not_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_resp_sibling_not_yes() { }
		~CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_resp_sibling_not_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENITITY_NOT_ALLOWED_FOR_RESP_SIBLING_NOT_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ENTITY_TYPE% is not a valid entity for  this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité %ENTITY_TYPE% est invalide pour ce compte.")); }

        // Actions
	};
}



