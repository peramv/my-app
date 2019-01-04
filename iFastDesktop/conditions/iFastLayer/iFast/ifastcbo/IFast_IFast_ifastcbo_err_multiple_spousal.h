#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_spousal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_spousal() { }
		~CIFast_IFast_ifastcbo_err_multiple_spousal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_SPOUSAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Spousal contributor entities not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple Spousal contributor entities not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Objekte bei Ehelichem Beitragenden sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten entidades de aportante conyugal múltiples.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les entités conjointes cotisantes multiples ne sont pas autorisées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere eenheden voor echtelijke bijdrager zijn niet toegestaan")); }

        // Actions
	};
}



