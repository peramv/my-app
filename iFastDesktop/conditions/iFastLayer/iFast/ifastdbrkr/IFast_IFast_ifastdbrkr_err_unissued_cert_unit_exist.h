#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unissued_cert_unit_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unissued_cert_unit_exist() { }
		~CIFast_IFast_ifastdbrkr_err_unissued_cert_unit_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNISSUED_CERT_UNIT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unissued Certificate Units exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nicht gezeichnete Zertifikat-Anteile existieren")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existen unidades de certificado no emitidas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des unités de certificat non émises existent.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan niet-uitgegeven certificaateenheden")); }

        // Actions
	};
}



