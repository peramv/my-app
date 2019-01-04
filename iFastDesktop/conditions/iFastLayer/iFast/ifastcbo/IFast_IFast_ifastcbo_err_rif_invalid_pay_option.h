#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_pay_option : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_pay_option() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_pay_option() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_PAY_OPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay option must be either \"F\",\"M\",\"I\" or\" X\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pay option must be either \"F\",\"M\",\"I\" or\" X\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsoption muss \"F\",\"M\",\"I\" oder \"X\" sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La opción de pago debe ser \"F\",\"M\",\"I\" ó \" X\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option de paiement doit être F, M, I ou X.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsoptie moet 'F', 'M', 'I' of 'X' zijn")); }

        // Actions
	};
}



