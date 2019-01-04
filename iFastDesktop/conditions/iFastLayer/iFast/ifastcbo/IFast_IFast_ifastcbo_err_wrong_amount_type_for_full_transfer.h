#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wrong_amount_type_for_full_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wrong_amount_type_for_full_transfer() { }
		~CIFast_IFast_ifastcbo_err_wrong_amount_type_for_full_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_AMOUNT_TYPE_FOR_FULL_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type must be 'D', 'F' or 'T' for full transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart für einen vollen Transfer muss 'D', 'F' oder 'T' sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser 'D', 'F' o 'T' para transferencias totales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être D, F ou T pour un transfert total.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet 'D', 'F' of 'T' zijn volledige overdracht")); }

        // Actions
	};
}



