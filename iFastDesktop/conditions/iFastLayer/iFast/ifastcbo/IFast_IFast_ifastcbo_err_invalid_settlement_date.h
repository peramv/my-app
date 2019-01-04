#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_settlement_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_settlement_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_settlement_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLEMENT_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Settlement Date. Next valid settlement date is %SETTLEDATE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date de reglement invalide. La date de reglement valide suivante est %SETTLEDATE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Abrechnungsdatum. Nächstes gültiges Abrechnungsdatum ist %SETTLEDATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de liquidación no válida. La siguiente fecha de liquidación válida es %SETTLEDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de règlement invalide. La prochaine date de règlement valide est le %SETTLEDATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige betalingsdatum. Volgende geldige betalingsdatum is %SETTLEDATE%")); }

        // Actions
	};
}



