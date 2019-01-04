#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_entity_setup_for_non_escrow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_entity_setup_for_non_escrow() { }
		~CIFast_IFast_ifastcbo_err_escrow_entity_setup_for_non_escrow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_ENTITY_SETUP_FOR_NON_ESCROW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow entity defined for non escrow account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhänder-Objekt definiert für ein Nicht-Escrow-(Ander-)konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entidad de custodia definida para cuenta no de custodia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le cessionnaire est défini pour un compte sans mise en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pandeenheid is gedefinieerd voor niet-pandaccount")); }

        // Actions
	};
}



