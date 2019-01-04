#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_xfer_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_xfer_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_fund_class_xfer_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_XFER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange or Transfer From fund %FUND% class %CLASS% to fund %TO_FUND% class %TO_CLASS% is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Echange ou virement du fonds %FUND% catégorie %CLASS% au fonds %TO_FUND% catégorie %TO_CLASS% non autorisé.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechsel oder Transfer von Fonds %FUND% Klasse %CLASS% zu  Fonds %TO_FUND% Klasse %TO_CLASS% ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el traspaso o transferencia del fondo %FUND% clase %CLASS% al fondo %TO_FUND% clase %TO_CLASS%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un échange ou un transfert du fonds %FUND% et de la classe %CLASS% au fonds %TO_FUND% et à la classe %TO_CLASS% n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ruiltransactie of overdracht van fonds %FUND% categorie %CLASS% naar fonds %TO_FUND% categorie %TO_CLASS% is niet toegestaan")); }

        // Actions
	};
}



