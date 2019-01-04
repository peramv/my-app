#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_field_read_only : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_field_read_only() { }
		~CIFast_IFast_dicbocore_err_field_read_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_READ_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trustee may only be set up for Trust account types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Trustee may only be set up for Trust account types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhänder (13) kann nur für Treuhänder-Kontoarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fideicomisario (13) sólo puede configurarse para tipos de cuenta Fideicomiso.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un fiduciaire ne peut être réglé que pour un compte de type fiducie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Trustee (13) kan alleen worden ingesteld voor Trust accounttypes")); }

        // Actions
	};
}



