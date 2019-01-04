#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amttype_for_full_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amttype_for_full_transfer() { }
		~CIFast_IFast_ifastcbo_err_invalid_amttype_for_full_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type must be Amount, All Free Units, Free and Non-Aged Units or Matured Units for full transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart für Vollen Transfer muss D, F oder T sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser D, F o T para transferencias totales")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour un transfert total, le type de montant doit être Montant, Toutes les unités sans frais, Unités sans frais et non maturesou Unités matures.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet 'D', 'F' of 'T' zijn voor volledige overdracht")); }

        // Actions
	};
}



