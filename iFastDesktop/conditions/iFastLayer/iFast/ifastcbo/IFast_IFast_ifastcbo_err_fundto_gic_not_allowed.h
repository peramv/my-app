#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundto_gic_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundto_gic_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_fundto_gic_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDTO_GIC_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundType is 'C' or 'S' for FundToCode is not allowed as GIC Fund only allowed on Allocation screen.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("FundType is 'C' or 'S' for FundToCode is not allowed as GIC Fund only allowed on Allocation screen.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondsart \"C\" oder \"S\" für FondsZuCode ist nicht erlaubt, da der GIC-Fonds nur auf dem Zuweisungsbildschirm zugelassen ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de fondo es 'C' o 'S' para Código de fondo de destino no se permite como Fondo GIC solamente permitido en la pantalla Asignación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de fonds C ou S pour le code Vers le fonds n'est pas autorisé puisque le fonds CPG n'est autorisé que sur l'écran de la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondstype is 'C' of 'S' voor FundToCode is niet toegestaan aangezien GIC-fonds alleen is toegestaan op allocatiescherm")); }

        // Actions
	};
}



