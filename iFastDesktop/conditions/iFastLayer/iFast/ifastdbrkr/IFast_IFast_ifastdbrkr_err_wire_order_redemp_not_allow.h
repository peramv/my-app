#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wire_order_redemp_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wire_order_redemp_not_allow() { }
		~CIFast_IFast_ifastdbrkr_err_wire_order_redemp_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WIRE_ORDER_REDEMP_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wire Order Redemption not allowed for Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Telegrafische-Bestellung-Tilgung nicht erlaubt für Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el rescate por orden de transferencia cablegráfica para el fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les rachats d'ordre électronique de sont pas autorisés pour le fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossing telegrafische order is niet toegestaan voor fonds")); }

        // Actions
	};
}



