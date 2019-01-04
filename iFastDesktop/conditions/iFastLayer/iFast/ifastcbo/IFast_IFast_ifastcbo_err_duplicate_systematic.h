#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_systematic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_systematic() { }
		~CIFast_IFast_ifastcbo_err_duplicate_systematic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_SYSTEMATIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Systematic of the same fund/class and effective date already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Systematic of the same fund/class and effective date already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der %TRANSTYPE%– Eintrag für den selben %FUNDNAME%  %CLASSNAME%und Effektivdatum %EFFECDATE% existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un plan sistemático del mismo fondo/clase y fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La systématique du même fonds/de la même classe et la date d'entrée en vigueur existent déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Systeemplan van hetzelfde fonds of dezelfde categorie en ingangsdatum bestaat al")); }

        // Actions
	};
}



