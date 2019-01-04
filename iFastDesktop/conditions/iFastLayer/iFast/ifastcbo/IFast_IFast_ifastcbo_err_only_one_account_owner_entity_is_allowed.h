#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_one_account_owner_entity_is_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_one_account_owner_entity_is_allowed() { }
		~CIFast_IFast_ifastcbo_err_only_one_account_owner_entity_is_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_ACCOUNT_OWNER_ENTITY_IS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Account Owner Entity is allowed for this account type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only one Account Owner Entity is allowed for this account type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein Rentenempfänger-Objekt ist zugelassen für diese Steuerart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite una entidad Propietario de la cuenta  para este tipo de cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une seule entité titulaire du compte est autorisée pour ce type de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één eenheid voor accounthouder toegestaan voor dit accounttype")); }

        // Actions
	};
}



