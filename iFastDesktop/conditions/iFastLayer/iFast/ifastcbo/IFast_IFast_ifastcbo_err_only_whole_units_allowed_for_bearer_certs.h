#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_whole_units_allowed_for_bearer_certs : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_whole_units_allowed_for_bearer_certs() { }
		~CIFast_IFast_ifastcbo_err_only_whole_units_allowed_for_bearer_certs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only whole units are allowed for bearer certificates.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Inhaberzertifikate sind nur ganze Anteile erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permiten unidades enteras para certificados al portador")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seules les unités entières sont autorisées pour les certificats au porteur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen hele eenheden zijn toegestaan voor certificaten aan toonder")); }

        // Actions
	};
}



