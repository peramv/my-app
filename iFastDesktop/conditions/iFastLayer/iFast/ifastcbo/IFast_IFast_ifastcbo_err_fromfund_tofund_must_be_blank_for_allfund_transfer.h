#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fromfund_tofund_must_be_blank_for_allfund_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fromfund_tofund_must_be_blank_for_allfund_transfer() { }
		~CIFast_IFast_ifastcbo_err_fromfund_tofund_must_be_blank_for_allfund_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROMFUND_TOFUND_MUST_BE_BLANK_FOR_ALLFUND_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Both from fund and to fund must be blank for all fund transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sowohl Von-Fonds als auch Zu-Fonds müssen für Gesamtfonds-Transfer leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo de origen y el fondo de destino deben estar en blanco para transferencia de todo el fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs des fonds source et cible doivent être vides pour le transfert de tous les fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Zowel van-fonds als naar-fonds moet leeg zijn voor overdracht van alle fondsen")); }

        // Actions
	};
}



