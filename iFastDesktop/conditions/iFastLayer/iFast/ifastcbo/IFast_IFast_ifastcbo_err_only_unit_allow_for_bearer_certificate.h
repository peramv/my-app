#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_unit_allow_for_bearer_certificate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_unit_allow_for_bearer_certificate() { }
		~CIFast_IFast_ifastcbo_err_only_unit_allow_for_bearer_certificate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_UNIT_ALLOW_FOR_BEARER_CERTIFICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only unit allowed for bearer certificate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur Anteil für Inhaberzertifikat erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo permitir unidad para el certificado al portador")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seule une unité est autorisée pour le certificat au porteur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen eenheid staat certificaat aan toonder toe")); }

        // Actions
	};
}



