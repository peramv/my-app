#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fundto_classto_cannot_blank_for_transfers : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fundto_classto_cannot_blank_for_transfers() { }
		~CIFast_IFast_ifastdbrkr_err_fundto_classto_cannot_blank_for_transfers() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDTO_CLASSTO_CANNOT_BLANK_FOR_TRANSFERS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund To/Class To cannot be blank for Transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FondsZu/KlasseZu kann für Transfers nicht leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los campos de fondo de destino/clase de destino no pueden dejarse en blanco para transferencias")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la cible du fonds/de la classe ne peut être vide pour les transferts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds-naar/Categorie-naar mag niet leeg zijn voor overdrachten")); }

        // Actions
	};
}



