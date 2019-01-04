#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_combination_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_combination_fund_code() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_combination_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_COMBINATION_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund/Class is not available for the group of this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La combinaison Fonds/catégorie n'est pas disponible pour le groupe de ce compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds/Klasse für die Gruppe dieses Kontos nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo/clase no está disponible para el grupo de esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe n'est pas disponible pour le groupe de ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds/categorie is niet beschikbaar voor de groep van dit account")); }

        // Actions
	};
}



