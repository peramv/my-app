#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_other_entity_type_must_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_other_entity_type_must_be_setup() { }
		~CIFast_IFast_ifastcbo_err_other_entity_type_must_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OTHER_ENTITY_TYPE_MUST_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Type 'Other' is missing for Youth Portfolio account purpose account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entity Type 'Other' is missing for Youth Portfolio account purpose account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entity Type 'Other' is missing for Youth Portfolio account purpose account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité Autre est manquant pour le compte dont le but est un compte de portefeuille jeunesse.")); }

        // Actions
	};
}



