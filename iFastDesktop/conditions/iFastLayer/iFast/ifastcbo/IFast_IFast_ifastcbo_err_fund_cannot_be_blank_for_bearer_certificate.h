#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_cannot_be_blank_for_bearer_certificate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_cannot_be_blank_for_bearer_certificate() { }
		~CIFast_IFast_ifastcbo_err_fund_cannot_be_blank_for_bearer_certificate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CANNOT_BE_BLANK_FOR_BEARER_CERTIFICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund cannot be blank for bearer certificate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds für Inhaberzertifikat darf nicht leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo  no puede estar en blanco para el certificado al portador")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds est requis pour un certificat au porteur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds mag niet leeg zijn voor certificaat aan toonder")); }

        // Actions
	};
}



