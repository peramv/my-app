#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_spousal_contributor_entity_should_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_spousal_contributor_entity_should_be_setup() { }
		~CIFast_IFast_ifastcbo_err_spousal_contributor_entity_should_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spousal Entity contributor should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spousal Entity contributor should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehepartner-Objektanleger sollte erstellt und nur ein Eintrag ist zugelassen sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Aportante conyugal y sólo se permite una entrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint cotisant doit être créé; un seul conjoint cotisant est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijdrager echtelijke eenheid moet worden ingesteld en er is slechts één invoer toegestaan")); }

        // Actions
	};
}



