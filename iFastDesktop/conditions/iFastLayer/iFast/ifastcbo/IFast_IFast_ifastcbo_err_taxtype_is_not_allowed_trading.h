#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_taxtype_is_not_allowed_trading : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_taxtype_is_not_allowed_trading() { }
		~CIFast_IFast_ifastcbo_err_taxtype_is_not_allowed_trading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAXTYPE_IS_NOT_ALLOWED_TRADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type is not allowed for the trading.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart ist nicht für den Handel erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el tipo tributario para la operación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'imposition non autorisé pour l'opération")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype is niet toegestaan voor de handel")); }

        // Actions
	};
}



