#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_close_fund_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_close_fund_redemption() { }
		~CIFast_IFast_ifastcbo_err_invalid_close_fund_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CLOSE_FUND_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Close fund redemption code is only allowed for unallocated, full redemption, transfer-out and exchange-out.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abschlusscode für Fonds-Tilgung ist nur für nicht zugewiesene, volle Tilgung, Transfer-Ausgänge und Devisen-Ausgänge erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de rescate con cierre del fondo sólo se permite para no asignado, rescate total, transferencias de salida y traspasos de salida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat de fermeture du compte n'est autorisé que pour un rachat non réparti, total, un transfert sortant et un échange sortant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode voor het sluiten van het fonds is alleen toegestaan voor niet-gealloceerd, volledig aflossen, overdracht-uit en ruilen-uit")); }

        // Actions
	};
}



