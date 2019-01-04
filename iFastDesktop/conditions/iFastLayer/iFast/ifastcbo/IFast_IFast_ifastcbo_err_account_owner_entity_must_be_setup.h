#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_owner_entity_must_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_owner_entity_must_be_setup() { }
		~CIFast_IFast_ifastcbo_err_account_owner_entity_must_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_OWNER_ENTITY_MUST_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Owner Entity must be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account Owner Entity must be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoinhaber-Objekt muss erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Propietario de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité titulaire du compte doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid accounthouder moet worden ingesteld")); }

        // Actions
	};
}



