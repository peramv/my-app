#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_payoptionmaximumnotallowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_payoptionmaximumnotallowed() { }
		~CIFast_IFast_ifastcbo_err_rrif_payoptionmaximumnotallowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_PayOptionMaximumNotAllowed")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay option Maximum is not allowed for RRIF accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Zahlungsoption \"Maximum\" ist für RRIF-Konten nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la opción de pago máximo para las cuentas RRIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le maximum d'option de paiement n'est pas autorisé pour les comptes FERR.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsoptie maximum is niet toegestaan voor RRIF-accounts")); }

        // Actions
	};
}



