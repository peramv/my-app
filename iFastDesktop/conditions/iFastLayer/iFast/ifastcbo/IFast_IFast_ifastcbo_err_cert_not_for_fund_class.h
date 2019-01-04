#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cert_not_for_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cert_not_for_fund_class() { }
		~CIFast_IFast_ifastcbo_err_cert_not_for_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CERT_NOT_FOR_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Certificate is not applicable to %FUND% and %CLASS%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Certificate is not applicable to %FUND% and %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zertifikat ist nicht anwendbar auf  %FUND% und  %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El certificado no es aplicable a %FUND% y %CLASS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le certificat ne s'applique pas au %FUND% et à la %CLASS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Certificaat is niet van toepassing op %FUND% en %CLASS")); }

        // Actions
	};
}



