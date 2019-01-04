#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_interest_on_close_fund_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_interest_on_close_fund_redemption() { }
		~CIFast_IFast_ifastcbo_err_invalid_interest_on_close_fund_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Close fund redemption code is not allowed as selected fund does not pay interest.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abschlusscode für Fonds-Tilgung ist nicht erlaubt, da der ausgewählte Fonds keine Zinsen abwirft")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de rescate con cierre del fondo no se permite ya que el fondo seleccionado no paga intereses")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat de fermeture du compte n'est pas autorisé puisque le fonds sélectionné ne nécessite pas de paiement d'intérêt.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode voor het sluiten van het fonds is niet toegestaan omdat het geselecteerde fonds geen rente uitkeert")); }

        // Actions
	};
}



