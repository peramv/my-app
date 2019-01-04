#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_applicatble_for_tofund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_applicatble_for_tofund() { }
		~CIFast_IFast_ifastcbo_err_no_applicatble_for_tofund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_APPLICATBLE_FOR_TOFUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type is not applicable for this To Fund/Class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart ist für diese(n) Zu-Fonds/-Klasse nicht anwendbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto no es aplicable a este fondo/clase")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant n'est pas applicable pour ce champ Vers le fonds/Vers la classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype is niet van toepassing voor dit naar-fonds of deze naar-categorie")); }

        // Actions
	};
}



