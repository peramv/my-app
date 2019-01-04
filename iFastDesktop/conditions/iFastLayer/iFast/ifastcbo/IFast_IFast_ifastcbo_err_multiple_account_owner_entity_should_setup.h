#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_account_owner_entity_should_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_account_owner_entity_should_setup() { }
		~CIFast_IFast_ifastcbo_err_multiple_account_owner_entity_should_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ACCOUNT_OWNER_ENTITY_SHOULD_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Account Owner Entities should be setup for Joint Account Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple Account Owner Entities should be setup for Joint Account Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfach-Kontoinhaber-Objekt sollte für Gemeinsachtskontoart erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Propietarios de cuenta múltiples para el tipo de cuenta Conjunta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs titulaires du compte doivent être créés pour le type de compte Conjoint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een eenheid voor meerdere accounthouders worden ingesteld voor het type Gezamenlijke account")); }

        // Actions
	};
}



