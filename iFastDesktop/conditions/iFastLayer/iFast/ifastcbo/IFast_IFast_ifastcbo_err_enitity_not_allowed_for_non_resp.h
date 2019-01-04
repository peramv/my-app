#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_non_resp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_non_resp() { }
		~CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_non_resp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENITITY_NOT_ALLOWED_FOR_NON_RESP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ENTITY_TYPE% is not allowed for non%TAX_TYPE% account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité %ENTITY_TYPE% n'est pas autorisé pour les comptes non %TAX_TYPE%.")); }

        // Actions
	};
}



