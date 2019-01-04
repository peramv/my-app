#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_annuitant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_annuitant() { }
		~CIFast_IFast_ifastcbo_err_multiple_annuitant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ANNUITANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Annuitant entities not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple Annuitant entities not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Objekte bei Rentenempfänger sind nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten entidades de titular de anualidad múltiples.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les entités crédirentières multiples ne sont pas autorisées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere eenheden voor lijfrentetrekker zijn niet toegestaan")); }

        // Actions
	};
}



